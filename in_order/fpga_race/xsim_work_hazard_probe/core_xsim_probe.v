// 2-wide in-order RV32IM core, 5 stages: IF -> IQ/ISSUE -> EX -> MEM -> WB
// slot0: full pipe (mem / branch / jump / muldiv / alu)
// slot1: simple ALU ops only (OP / OP-IMM / LUI / AUIPC)
// Fetch: 64-bit pair per cycle through a 4-entry instruction queue.
module core (
    input  wire        clk,
    input  wire        rst,
    // instruction pair port (sync read, 1-cycle latency)
    output wire [31:0] imem_addr,    // pair address (may be 4-byte aligned only)
    input  wire [31:0] imem_rdata0,  // instr at imem_addr
    input  wire [31:0] imem_rdata1,  // instr at imem_addr + 4
    // data port (slot0: full read/write)
    output wire [31:0] dmem_addr,
    output wire        dmem_ren,
    output wire [3:0]  dmem_wen,
    output wire [31:0] dmem_wdata,
    input  wire [31:0] dmem_rdata,
    // data port 1 (slot1: loads + word stores, statically safe base by issue rule)
    output wire [31:0] dmem1_addr,
    output wire        dmem1_ren,
    output wire [3:0]  dmem1_wen,
    output wire [31:0] dmem1_wdata,
    input  wire [31:0] dmem1_rdata,
    // dual commit (slot0 older)
    output wire        commit0_valid,
    output wire [31:0] commit0_pc,
    output wire [31:0] commit0_instr,
    output wire        commit0_rd_wen,
    output wire [4:0]  commit0_rd,
    output wire [31:0] commit0_rd_wdata,
    output wire        commit1_valid,
    output wire [31:0] commit1_pc,
    output wire [31:0] commit1_instr,
    output wire        commit1_rd_wen,
    output wire [4:0]  commit1_rd,
    output wire [31:0] commit1_rd_wdata
);
    localparam RESET_PC = 32'h8000_0000;

    wire        ex_redir;        // EX mispredict / jalr / fence.i (combinational)
    wire [31:0] ex_redir_pc;
    reg         redirect;        // registered: applied to pc/queue one cycle later
    reg  [31:0] redirect_pc;
    wire        id_redirect;     // issue-time cold prediction (JAL / BTFN)
    wire [31:0] id_redirect_pc;
    wire        mstall;          // muldiv busy in EX0

    // ================= IF =================
    reg [31:0] pc_f;             // pc of the pair arriving THIS cycle

    // ---- BTB: 128-entry direct-mapped, static targets, dual lookup ----
    // Looked up with pc_next (one cycle EARLY) and registered: the fetch-side
    // pc mux sees only FF outputs, keeping LUTRAM read + 23-bit tag compare
    // off the pc -> BRAM address path.
    // 64KB code space (pc[31:16] fixed at 0x8000): 7-bit tag, 14-bit target
    reg         btb_valid [0:127];
    reg [6:0]   btb_tag   [0:127];
    reg [13:0]  btb_tgt   [0:127];

    wire btb_wr, btb_clr, btb_flush;
    wire [6:0]  btb_widx;
    wire [6:0]  btb_wtag;
    wire [13:0] btb_wtgt;
    integer bi;
    always @(posedge clk) begin
        if (rst || btb_flush) begin
            for (bi = 0; bi < 128; bi = bi + 1) btb_valid[bi] <= 1'b0;
        end else if (btb_wr) begin
            btb_valid[btb_widx] <= 1'b1;
            btb_tag[btb_widx]   <= btb_wtag;
            btb_tgt[btb_widx]   <= btb_wtgt;
        end else if (btb_clr) begin
            btb_valid[btb_widx] <= 1'b0;
        end
    end

    // registered dual lookup: query with pc_next, results align with pc_f
    // (16-bit pc arithmetic: code never crosses the 64KB boundary)
    wire [31:0] pc_next;
    wire [15:0] pcn_p4 = pc_next[15:0] + 16'd4;
    reg         bhit0, bhit1;
    reg  [31:0] btgt0, btgt1;
    always @(posedge clk) begin
        if (rst) begin
            bhit0 <= 1'b0;
            bhit1 <= 1'b0;
        end else begin
            bhit0 <= btb_valid[pc_next[8:2]] && (btb_tag[pc_next[8:2]] == pc_next[15:9]);
            bhit1 <= btb_valid[pcn_p4[8:2]]  && (btb_tag[pcn_p4[8:2]]  == pcn_p4[15:9]);
            btgt0 <= {16'h8000, btb_tgt[pc_next[8:2]], 2'b00};
            btgt1 <= {16'h8000, btb_tgt[pcn_p4[8:2]], 2'b00};
        end
    end
    wire [31:0] pcp4 = pc_f + 32'd4;

    // ================ fetch queue (4 entries) ================
    reg [31:0] q_pc    [0:3];
    reg [31:0] q_instr [0:3];
    reg        q_pred  [0:3];
    reg [2:0]  q_cnt;

    wire [1:0] pops;
    wire [2:0] cnt_after_pop = q_cnt - {1'b0, pops};
    // conservative space check (registered count only) keeps the pc mux select
    // chain short; wrong-path pushes are blocked by the redirect gates
    wire       accept = !rst && !redirect && !id_redirect && !idr_r && (q_cnt <= 3'd2);
    wire       push1only = bhit0;   // predicted-taken at slot0: drop pair's 2nd instr

    // pc-mux select for cold prediction: REGISTERED (issue-time redirects
    // apply one cycle later). Keeps the decoder/hazard/PHT/RAS chain out of
    // the pc mux -> BRAM address path. Cold redirect costs 2 bubbles.
    wire id_sel_pc;
    reg         idr_r;
    reg  [31:0] idr_pc_r;

    wire [31:0] pc_next_w = redirect         ? redirect_pc :
                            idr_r            ? idr_pc_r :
                            (q_cnt > 3'd2)   ? pc_f :
                            bhit0            ? btgt0 :
                            bhit1            ? btgt1 :
                            pc_f + 32'd8;
    assign pc_next = pc_next_w;
    always @(posedge clk) begin
        if (rst) begin
            pc_f     <= RESET_PC;
            redirect <= 1'b0;
            idr_r    <= 1'b0;
        end else begin
            pc_f        <= pc_next;
            redirect    <= ex_redir;
            redirect_pc <= ex_redir_pc;
            idr_r       <= id_redirect;    // overlap with ex_redir is harmless:
                                           // redirect wins the pc mux next cycle
                                           // and idr_r expires after one cycle
            idr_pc_r    <= id_redirect_pc;
        end
    end
    assign imem_addr = rst ? RESET_PC : pc_next;

    integer k;
    always @(posedge clk) begin
        if (rst || redirect || id_redirect) begin
            q_cnt <= 3'd0;
        end else begin
            // shift out popped entries
            for (k = 0; k < 4; k = k + 1) begin
                if (k + {30'b0, pops} < {29'b0, q_cnt}) begin
                    q_pc[k]    <= q_pc[k + {30'b0, pops}];
                    q_instr[k] <= q_instr[k + {30'b0, pops}];
                    q_pred[k]  <= q_pred[k + {30'b0, pops}];
                end
            end
            if (accept) begin
                q_pc   [cnt_after_pop[1:0]] <= pc_f;
                q_instr[cnt_after_pop[1:0]] <= imem_rdata0;
                q_pred [cnt_after_pop[1:0]] <= bhit0;
                if (!push1only) begin
                    q_pc   [cnt_after_pop[1:0] + 2'd1] <= pcp4;
                    q_instr[cnt_after_pop[1:0] + 2'd1] <= imem_rdata1;
                    q_pred [cnt_after_pop[1:0] + 2'd1] <= bhit1;
                end
                q_cnt <= cnt_after_pop + (push1only ? 3'd1 : 3'd2);
            end else begin
                q_cnt <= cnt_after_pop;
            end
        end
    end

    // ================ ISSUE (ID) ================
    wire v0 = (q_cnt >= 3'd1);
    wire v1 = (q_cnt >= 3'd2);
    wire [31:0] pc_0 = q_pc[0],    pc_1 = q_pc[1];
    wire [31:0] in_0 = q_instr[0], in_1 = q_instr[1];

    // decoder slot0
    wire [4:0]  rs1_0, rs2_0, rd_0;
    wire [31:0] imm_0;
    wire [3:0]  alu_op_0;
    wire [1:0]  alu_a_sel_0;
    wire        alu_b_sel_0;
    wire        is_branch_0, is_jal_0, is_jalr_0, is_fencei_0;
    wire [2:0]  branch_op_0, mem_funct3_0;
    wire        mem_read_0, mem_write_0, rd_wen_0;
    wire [1:0]  wb_sel_0;
    wire        uses_rs1_0, uses_rs2_0, is_muldiv_0;
    wire        is_csr_0, is_ecall_0, is_mret_0;
    decoder u_dec0 (
        .instr(in_0),
        .rs1(rs1_0), .rs2(rs2_0), .rd(rd_0), .imm(imm_0),
        .alu_op(alu_op_0), .alu_a_sel(alu_a_sel_0), .alu_b_sel(alu_b_sel_0),
        .is_branch(is_branch_0), .branch_op(branch_op_0),
        .is_jal(is_jal_0), .is_jalr(is_jalr_0), .is_fencei(is_fencei_0),
        .mem_read(mem_read_0), .mem_write(mem_write_0), .mem_funct3(mem_funct3_0),
        .rd_wen(rd_wen_0), .wb_sel(wb_sel_0),
        .uses_rs1(uses_rs1_0), .uses_rs2(uses_rs2_0), .is_muldiv(is_muldiv_0),
        .is_csr(is_csr_0), .is_ecall(is_ecall_0), .is_mret(is_mret_0)
    );

    // decoder slot1
    wire [4:0]  rs1_1, rs2_1, rd_1;
    wire [31:0] imm_1;
    wire [3:0]  alu_op_1;
    wire [1:0]  alu_a_sel_1;
    wire        alu_b_sel_1;
    wire        is_branch_1, is_jal_1, is_jalr_1, is_fencei_1;
    wire [2:0]  branch_op_1, mem_funct3_1;
    wire        mem_read_1, mem_write_1, rd_wen_1;
    wire [1:0]  wb_sel_1;
    wire        uses_rs1_1, uses_rs2_1, is_muldiv_1;
    wire        is_csr_1, is_ecall_1, is_mret_1;
    decoder u_dec1 (
        .instr(in_1),
        .rs1(rs1_1), .rs2(rs2_1), .rd(rd_1), .imm(imm_1),
        .alu_op(alu_op_1), .alu_a_sel(alu_a_sel_1), .alu_b_sel(alu_b_sel_1),
        .is_branch(is_branch_1), .branch_op(branch_op_1),
        .is_jal(is_jal_1), .is_jalr(is_jalr_1), .is_fencei(is_fencei_1),
        .mem_read(mem_read_1), .mem_write(mem_write_1), .mem_funct3(mem_funct3_1),
        .rd_wen(rd_wen_1), .wb_sel(wb_sel_1),
        .uses_rs1(uses_rs1_1), .uses_rs2(uses_rs2_1), .is_muldiv(is_muldiv_1),
        .is_csr(is_csr_1), .is_ecall(is_ecall_1), .is_mret(is_mret_1)
    );

    // register file (4R2W)
    wire        wb_wen0, wb_wen1;
    wire [4:0]  wb_rd0, wb_rd1;
    wire [31:0] wb_wdata0, wb_wdata1;
    wire [31:0] rs1_data_0, rs2_data_0, rs1_data_1, rs2_data_1;
    regfile_2w u_rf (
        .clk(clk),
        .rs1a(rs1_0), .rs2a(rs2_0), .rs1b(rs1_1), .rs2b(rs2_1),
        .rs1a_data(rs1_data_0), .rs2a_data(rs2_data_0),
        .rs1b_data(rs1_data_1), .rs2b_data(rs2_data_1),
        .wena(wb_wen0), .rda(wb_rd0), .wdataa(wb_wdata0),
        .wenb(wb_wen1), .rdb(wb_rd1), .wdatab(wb_wdata1)
    );

    // load-use hazard: block while the load/mul is in EX or M1 (result ready
    // at WB, issue distance 3). A distance-2 raw-BRAM forward was tried and
    // reverted: DRAM(64xBRAM) douta -> fwd -> ALU is ~7.1ns on K7 (route-bound),
    // uncloseable at 200MHz.
    wire       ld_e_v, ld_m_v, ld_e1_v, ld_m1_v;
    wire [4:0] ld_e_rd, ld_m_rd, ld_e1_rd, ld_m1_rd;
    // XSim probe only: make every hazard dependency explicit on the continuous
    // assignment RHS, instead of referring to ld_* signals from inside a
    // function whose formal arguments stay constant while the issue queue stalls.
    wire hz0_rs1 = uses_rs1_0 && (rs1_0 != 5'd0) &&
                   ((ld_e_v  && (ld_e_rd  == rs1_0)) || (ld_m_v  && (ld_m_rd  == rs1_0)) ||
                    (ld_e1_v && (ld_e1_rd == rs1_0)) || (ld_m1_v && (ld_m1_rd == rs1_0)));
    wire hz0_rs2 = uses_rs2_0 && (rs2_0 != 5'd0) &&
                   ((ld_e_v  && (ld_e_rd  == rs2_0)) || (ld_m_v  && (ld_m_rd  == rs2_0)) ||
                    (ld_e1_v && (ld_e1_rd == rs2_0)) || (ld_m1_v && (ld_m1_rd == rs2_0)));
    wire hz1_rs1 = uses_rs1_1 && (rs1_1 != 5'd0) &&
                   ((ld_e_v  && (ld_e_rd  == rs1_1)) || (ld_m_v  && (ld_m_rd  == rs1_1)) ||
                    (ld_e1_v && (ld_e1_rd == rs1_1)) || (ld_m1_v && (ld_m1_rd == rs1_1)));
    wire hz1_rs2 = uses_rs2_1 && (rs2_1 != 5'd0) &&
                   ((ld_e_v  && (ld_e_rd  == rs2_1)) || (ld_m_v  && (ld_m_rd  == rs2_1)) ||
                    (ld_e1_v && (ld_e1_rd == rs2_1)) || (ld_m1_v && (ld_m1_rd == rs2_1)));
    wire hz0 = hz0_rs1 | hz0_rs2;
    wire hz1 = hz1_rs1 | hz1_rs2;

    // NOTE: ex_redir deliberately NOT in the issue gate (it drags the EX
    // branch-compare chain into the queue-CE path). A wrong-path instruction
    // may issue during the ex_redir cycle; the registered `redirect` kills it
    // in ID/EX one cycle later before it produces side effects.
    wire issue0 = v0 && !hz0 && !mstall && !redirect;

    wire i1_alu = !is_branch_1 && !is_jal_1 && !is_jalr_1 && !is_fencei_1 &&
                  !mem_read_1 && !mem_write_1 && !is_muldiv_1 &&
                  !is_csr_1 && !is_ecall_1 && !is_mret_1;
    // slot1 load: second (read-only) memory port. Allowed only when the base
    // register value is architecturally final at issue (no forward pending)
    // and statically points at DRAM (0x801xxxxx) or IROM (0x8000xxxx), so an
    // MMIO access can never ride port 1. Same-group older store is excluded
    // (port1 read would race port0's write of the same cycle).
    // Timing: the segment of every register value is PRE-DECODED at writeback
    // into 32x1 hint tables (plus a same-cycle WB bypass on the 1-bit hints),
    // so the issue gate reads a flop-sourced bit instead of comparing the
    // 32-bit regfile read data (which dragged lvt->data->cmp into the
    // issue->queue CE cone). fsel_rs1_1==0 guarantees the base has no
    // in-flight producer, so table+WB-bypass covers exactly the same sources
    // the regfile read would return.
    reg  [31:0] seg_dram_tbl, seg_flat_tbl;
    wire wb0_dram = (wb_wdata0[31:20] == 12'h801);
    wire wb0_flat = (wb_wdata0[31:16] == 16'h8000);
    wire wb1_dram = (wb_wdata1[31:20] == 12'h801);
    wire wb1_flat = (wb_wdata1[31:16] == 16'h8000);
    always @(posedge clk) begin
        if (rst) begin
            seg_dram_tbl <= 32'b0;
            seg_flat_tbl <= 32'b0;
        end else begin
            if (wb_wen0 && wb_rd0 != 5'd0) begin
                seg_dram_tbl[wb_rd0] <= wb0_dram;
                seg_flat_tbl[wb_rd0] <= wb0_flat;
            end
            if (wb_wen1 && wb_rd1 != 5'd0) begin
                seg_dram_tbl[wb_rd1] <= wb1_dram;
                seg_flat_tbl[wb_rd1] <= wb1_flat;
            end
        end
    end
    wire i1_wb1_hit = wb_wen1 && (wb_rd1 == rs1_1) && (rs1_1 != 5'd0);
    wire i1_wb0_hit = wb_wen0 && (wb_rd0 == rs1_1) && (rs1_1 != 5'd0);
    wire i1_base_dram = i1_wb1_hit ? wb1_dram :
                        i1_wb0_hit ? wb0_dram : seg_dram_tbl[rs1_1];
    wire i1_base_flat = i1_wb1_hit ? wb1_flat :
                        i1_wb0_hit ? wb0_flat : seg_flat_tbl[rs1_1];
    wire i1_base_safe = i1_base_dram || i1_base_flat;
    wire i1_ld = mem_read_1 && (mem_funct3_1 == 3'b010) && i1_base_safe &&
                 (fsel_rs1_1 == 6'd0) && !mem_write_0;   // lw only: port1 needs no align net
    // slot1 word store: same flop-sourced AGU, port-1 write side. Excluded:
    //  - slot0 has any memory op (same-edge port collisions on one address)
    //  - slot0 is a branch (a same-group mispredict cannot squash a store
    //    side effect without dragging ex_redir back into the M-stage gates)
    // Store data (rs2) may still be forwarded normally in EX.
    wire i1_st = mem_write_1 && (mem_funct3_1 == 3'b010) && i1_base_safe &&
                 (fsel_rs1_1 == 6'd0) &&
                 !mem_read_0 && !mem_write_0 && !is_branch_0;
    wire i1_simple = i1_alu || i1_ld || i1_st;
    // slot0 pairing rules:
    //  - branch predicted not-taken     : q[1] is fall-through (predicted path) -> pair OK
    //  - branch/jal BTB-predicted taken : fetch dropped fall-through (push1only),
    //                                     q[1] is the TARGET instr (predicted path) -> pair OK
    //  - cold JAL / cold BTFN-taken     : id_redirect clears queue, q[1] is wrong path -> block
    //  - jalr / fence.i                 : always redirect in EX, q[1] always dies -> block
    //  - muldiv                         : mstall would hold slot1 in EX while its
    //                                     issue-time fwd selects go stale -> block
    wire btfn_taken_0 = is_branch_0 && imm_0[31];
    wire i0_cold_jmp;   // this cycle issue-redirects: q[1] is wrong path
    // csr/ecall/mret are rare serialize-ish ops: keep them single-issue
    // (ecall/mret always redirect in EX -> q[1] would die anyway; csr keeps
    // its side effect isolated from same-group slot1 kill corner cases)
    wire i0_sys    = is_csr_0 || is_ecall_0 || is_mret_0;
    // MULs are fully pipelined (EX->M1->M2->WB alongside the ALU pipe) and can
    // pair with slot1; only DIV/REM still occupies EX multi-cycle via mstall.
    wire is_div_0  = is_muldiv_0 && mem_funct3_0[2];
    wire i0_ctrl   = is_jalr_0 || is_fencei_0 || is_div_0 || i0_cold_jmp || i0_sys;
    wire raw01 = rd_wen_0 && (rd_0 != 5'd0) &&
                 ((uses_rs1_1 && rs1_1 == rd_0) || (uses_rs2_1 && rs2_1 == rd_0));
    wire waw01 = rd_wen_0 && rd_wen_1 && (rd_0 == rd_1) && (rd_0 != 5'd0);
    // NOTE: ALU-cascade pairing (slot1 operand chained from alu_y0 to relax
    // raw01) was tried and REVERTED: two chained ALUs blow EX timing at
    // Default (-1.49) and the eligible ALU-ALU pairs are rare in -O0 anyway
    // (dep:alu only -0.011; the hot dependent pattern is `alu -> sw data`,
    // handled below by the store-DATA cascade instead).

    // ---- store-data cascade ----
    // `alu; sw rd_of_alu, off(base)` may dual-issue: the store DATA (rs2)
    // comes straight from alu_y0 into the dmem1_wdata_r flop -- same depth
    // as the existing alu_y0 -> alu_m0 latch, no second ALU in series.
    // Base (rs1) dependence on slot0 stays forbidden (AGU1 is flop-fed).
    wire i0_casc_src = rd_wen_0 && (rd_0 != 5'd0) &&
                       !mem_read_0 && !mem_write_0 && !is_muldiv_0 &&
                       !is_jal_0 && !is_jalr_0 && !is_branch_0 &&
                       !is_csr_0 && !is_ecall_0 && !is_mret_0 && !is_fencei_0;
    wire dep_rs1_01 = rd_wen_0 && (rd_0 != 5'd0) && uses_rs1_1 && (rs1_1 == rd_0);
    wire dep_rs2_01 = rd_wen_0 && (rd_0 != 5'd0) && uses_rs2_1 && (rs2_1 == rd_0);
    wire casc_st_1  = i1_st && i0_casc_src && dep_rs2_01 && !dep_rs1_01;

    wire issue1 = issue0 && v1 && i1_simple && !i0_ctrl &&
                  (!raw01 || casc_st_1) && !waw01 && !hz1;

    assign pops = issue1 ? 2'd2 : (issue0 ? 2'd1 : 2'd0);

    // ---- RAS: 8-deep return address stack ----
    // push at EX (call: jal/jalr with rd in {ra,t0}); pop+predict at issue
    // (ret: jalr x0, ra/t0). In-order + issue-gating means issued == committed,
    // so no checkpoint/repair is ever needed.
    reg [31:0] ras [0:7];
    reg [2:0]  ras_sp;   // top of stack
    reg [3:0]  ras_cnt;  // 0..8 saturating
    wire        ras_push;
    wire [31:0] ras_push_val;
    wire [31:0] ras_top = ras[ras_sp];

    wire is_ret_0  = is_jalr_0 && (rd_0 == 5'd0) && (rs1_0 == 5'd1);
    wire ras_ret_0 = is_ret_0 && (ras_cnt != 4'd0);

    // ---- agree-gshare direction predictor ----
    // PHT counter semantics: [1]=agree with the static BTFN hint.
    // init = 2'b10 (weakly agree) => cold behaviour identical to plain BTFN.
    // Predicts at issue (off the fetch path); updated at EX with the outcome.
    reg [1:0] pht [0:255];
    reg [7:0] ghr;
    integer pi;
    initial begin
        for (pi = 0; pi < 256; pi = pi + 1) pht[pi] = 2'b10;
    end

    wire [7:0] pht_idx_0  = pc_0[9:2] ^ ghr;
    wire [1:0] pht_ctr_0  = pht[pht_idx_0];
    wire       dir_pred_0 = pht_ctr_0[1] ? btfn_taken_0 : !btfn_taken_0;
    // overriding a BTB fetch-redirect costs 1 cycle (plus 3 if wrong): require
    // a saturated counter; weak states follow the BTB (taken, 0-bubble)
    wire       pht_strong_0 = (pht_ctr_0 == 2'b00) || (pht_ctr_0 == 2'b11);

    // issue-time redirects:
    //  jal_cold     : JAL not covered by BTB -> jump to target
    //  br_take_cold : branch predicted taken, BTB missed -> jump to target
    //  br_override  : BTB fetch-redirected to target but PHT says not-taken
    //                 -> pull fetch back to fall-through
    wire jal_cold     = is_jal_0 && !q_pred[0];
    wire br_take_cold = is_branch_0 && dir_pred_0 && !q_pred[0];
    wire br_override  = is_branch_0 && !dir_pred_0 && pht_strong_0 && q_pred[0];
    assign i0_cold_jmp = jal_cold || br_take_cold || br_override;

    // final direction actually predicted for a branch this cycle:
    // BTB-redirected path is followed (taken) unless overridden
    wire br_final_taken_0 = is_branch_0 && (q_pred[0] ? !br_override : dir_pred_0);

    assign id_sel_pc   = v0 && !hz0 && !mstall &&
                         (jal_cold || br_take_cold || br_override || ras_ret_0);
    // id_redirect must not wait on ex_redir (queue-CE path); a spurious cold
    // redirect during the ex_redir cycle is harmless: the queue is dead either
    // way and idr_r/ras_pop are separately gated below.
    assign id_redirect = id_sel_pc && !redirect;
    assign id_redirect_pc = ras_ret_0   ? ras_top :
                            br_override ? (pc_0 + 32'd4) :
                            (pc_0 + imm_0);

    // pop is applied one cycle late (registered): removes the fwd->ex_redir
    // arc from the RAS flop enables; consecutive rets are >=2 cycles apart so
    // the deferred pop is always visible to the next RAS read
    reg ras_pop_r;
    always @(posedge clk) begin
        if (rst) ras_pop_r <= 1'b0;
        else     ras_pop_r <= id_redirect && ras_ret_0 && !ex_redir;
    end
    wire ras_pop = ras_pop_r;
    always @(posedge clk) begin
        if (rst) begin
            ras_sp  <= 3'd0;
            ras_cnt <= 4'd0;
        end else if (ras_push) begin
            ras_sp      <= ras_sp + 3'd1;
            ras[ras_sp + 3'd1] <= ras_push_val;
            if (ras_cnt != 4'd8) ras_cnt <= ras_cnt + 4'd1;
        end else if (ras_pop) begin
            ras_sp  <= ras_sp - 3'd1;
            ras_cnt <= ras_cnt - 4'd1;
        end
    end

    // ---- forwarding selects, precomputed at issue (off the EX critical path) ----
    // pipeline is 6-stage (IF IS EX M1 M2 WB); producer advances one stage per
    // consumer EX cycle:
    //   producer in EX now -> in M1 when consumer executes
    //   producer in M1 now -> in M2 when consumer executes
    //   producer in M2 now -> in WB when consumer executes (loads: aligned data)
    // priority: younger first (e1 > e0 > m1 > m0 > x1 > x0)
    wire       pe1_v, pe0_v, pm1_v, pm0_v, px1_v, px0_v;
    wire [4:0] pe1_rd, pe0_rd, pm1_rd, pm0_rd, px1_rd, px0_rd;

    function [5:0] fwd_sel; // [5]=M1_1 [4]=M1_0 [3]=M2_1 [2]=M2_0 [1]=WB1 [0]=WB0
        input       uses;
        input [4:0] rs;
        reg s5, s4, s3, s2, s1, s0;
        begin
            s5 = uses && rs != 5'd0 && pe1_v && (pe1_rd == rs);
            s4 = !s5 && uses && rs != 5'd0 && pe0_v && (pe0_rd == rs);
            s3 = !s5 && !s4 && uses && rs != 5'd0 && pm1_v && (pm1_rd == rs);
            s2 = !s5 && !s4 && !s3 && uses && rs != 5'd0 && pm0_v && (pm0_rd == rs);
            s1 = !s5 && !s4 && !s3 && !s2 && uses && rs != 5'd0 && px1_v && (px1_rd == rs);
            s0 = !s5 && !s4 && !s3 && !s2 && !s1 && uses && rs != 5'd0 && px0_v && (px0_rd == rs);
            fwd_sel = {s5, s4, s3, s2, s1, s0};
        end
    endfunction

    wire [5:0] fsel_rs1_0 = fwd_sel(uses_rs1_0, rs1_0);
    wire [5:0] fsel_rs2_0 = fwd_sel(uses_rs2_0, rs2_0);
    wire [5:0] fsel_rs1_1 = fwd_sel(uses_rs1_1, rs1_1);
    wire [5:0] fsel_rs2_1 = fwd_sel(uses_rs2_1, rs2_1);

    // ================ ID/EX ================
    // slot0
    reg        valid_e0;
    reg [31:0] pc_e0, instr_e0, imm_e0, rs1_data_e0, rs2_data_e0;
    reg [4:0]  rs1_e0, rs2_e0, rd_e0;
    reg [3:0]  alu_op_e0;
    reg [1:0]  alu_a_sel_e0;
    reg        alu_b_sel_e0;
    reg        is_branch_e0, is_jal_e0, is_jalr_e0, is_fencei_e0;
    reg [2:0]  branch_op_e0, mem_funct3_e0;
    reg        mem_read_e0, mem_write_e0, rd_wen_e0;
    reg [1:0]  wb_sel_e0;
    reg        is_m_e0, pred_taken_e0;
    reg        is_csr_e0, is_ecall_e0, is_mret_e0;
    reg        pred_jalr_e0;
    reg [31:0] pred_tgt_e0;
    reg [7:0]  pht_idx_e0;
    reg        btfn_e0;
    // slot1
    reg        valid_e1;
    reg [31:0] pc_e1, instr_e1, imm_e1, rs1_data_e1, rs2_data_e1;
    reg [4:0]  rs1_e1, rs2_e1, rd_e1;
    reg [3:0]  alu_op_e1;
    reg [1:0]  alu_a_sel_e1;
    reg        alu_b_sel_e1;
    reg        rd_wen_e1;
    reg        mem_read_e1;
    reg        mem_write_e1;
    reg        casc_st_e1;   // slot1 store data comes from alu_y0 (cascade)
    reg        is_dram_e1;   // slot1 mem-op base statically in DRAM (L0-eligible)
    reg [5:0]  fs_rs1_e0, fs_rs2_e0, fs_rs1_e1, fs_rs2_e1;

    always @(posedge clk) begin
        if (rst || redirect) begin
            valid_e0 <= 1'b0; valid_e1 <= 1'b0;
            is_branch_e0 <= 1'b0; is_jal_e0 <= 1'b0; is_jalr_e0 <= 1'b0; is_fencei_e0 <= 1'b0;
            mem_read_e0 <= 1'b0; mem_write_e0 <= 1'b0; rd_wen_e0 <= 1'b0;
            is_m_e0 <= 1'b0; pred_taken_e0 <= 1'b0; pred_jalr_e0 <= 1'b0;
            is_csr_e0 <= 1'b0; is_ecall_e0 <= 1'b0; is_mret_e0 <= 1'b0;
            rd_e0 <= 5'd0; rd_wen_e1 <= 1'b0; rd_e1 <= 5'd0;
            mem_read_e1 <= 1'b0; is_dram_e1 <= 1'b0; mem_write_e1 <= 1'b0;
            casc_st_e1 <= 1'b0;
        end else if (!mstall) begin
            valid_e0    <= issue0;
            pc_e0       <= pc_0;
            instr_e0    <= in_0;
            imm_e0      <= imm_0;
            rs1_data_e0 <= rs1_data_0;
            rs2_data_e0 <= rs2_data_0;
            rs1_e0      <= rs1_0;
            rs2_e0      <= rs2_0;
            rd_e0       <= rd_0;
            alu_op_e0   <= alu_op_0;
            alu_a_sel_e0<= alu_a_sel_0;
            alu_b_sel_e0<= alu_b_sel_0;
            is_branch_e0<= is_branch_0 & issue0;
            branch_op_e0<= branch_op_0;
            is_jal_e0   <= is_jal_0 & issue0;
            is_jalr_e0  <= is_jalr_0 & issue0;
            is_fencei_e0<= is_fencei_0 & issue0;
            mem_read_e0 <= mem_read_0 & issue0;
            mem_write_e0<= mem_write_0 & issue0;
            mem_funct3_e0 <= mem_funct3_0;
            rd_wen_e0   <= rd_wen_0 & issue0;
            wb_sel_e0   <= wb_sel_0;
            is_m_e0     <= is_muldiv_0 & issue0;
            is_csr_e0   <= is_csr_0 & issue0;
            is_ecall_e0 <= is_ecall_0 & issue0;
            is_mret_e0  <= is_mret_0 & issue0;
            pred_taken_e0 <= br_final_taken_0 & issue0;
            pred_jalr_e0  <= ras_ret_0 & issue0;
            pred_tgt_e0   <= ras_top;
            pht_idx_e0    <= pht_idx_0;
            btfn_e0       <= btfn_taken_0;

            valid_e1    <= issue1;
            pc_e1       <= pc_1;
            instr_e1    <= in_1;
            imm_e1      <= imm_1;
            rs1_data_e1 <= rs1_data_1;
            rs2_data_e1 <= rs2_data_1;
            rs1_e1      <= rs1_1;
            rs2_e1      <= rs2_1;
            rd_e1       <= rd_1;
            alu_op_e1   <= alu_op_1;
            alu_a_sel_e1<= alu_a_sel_1;
            alu_b_sel_e1<= alu_b_sel_1;
            rd_wen_e1   <= rd_wen_1 & issue1;
            mem_read_e1 <= mem_read_1 & issue1;
            mem_write_e1<= mem_write_1 & issue1;
            casc_st_e1  <= casc_st_1 & issue1;
            is_dram_e1  <= i1_base_dram & issue1;
            fs_rs1_e0   <= fsel_rs1_0;
            fs_rs2_e0   <= fsel_rs2_0;
            fs_rs1_e1   <= fsel_rs1_1;
            fs_rs2_e1   <= fsel_rs2_1;
        end
    end

    assign pe1_v  = rd_wen_e1;              // already gated by valid at ID/EX load
    assign pe1_rd = rd_e1;
    assign pe0_v  = rd_wen_e0;
    assign pe0_rd = rd_e0;
    assign pm1_v  = rd_wen_m1;
    assign pm1_rd = rd_m1;
    assign pm0_v  = rd_wen_m0;
    assign pm0_rd = rd_m0;
    assign px1_v  = rd_wen_x1;
    assign px1_rd = rd_x1;
    assign px0_v  = rd_wen_x0;
    assign px0_rd = rd_x0;

    // ================= EX =================
    // forwarding: one-hot selects were registered at issue; sources are all regs
    function [31:0] fwd_mux;
        input [5:0]  sel;
        input [31:0] regval;
        begin
            fwd_mux = ({32{sel[5]}} & alu_m1) |
                      ({32{sel[4]}} & alu_m0) |
                      ({32{sel[3]}} & alu_x1) |
                      ({32{sel[2]}} & alu_x0) |
                      ({32{sel[1]}} & wb_wdata1) |
                      ({32{sel[0]}} & wb_wdata0) |
                      ({32{~|sel}} & regval);
        end
    endfunction

    wire [31:0] rs1_fwd0 = fwd_mux(fs_rs1_e0, rs1_data_e0);
    wire [31:0] rs2_fwd0 = fwd_mux(fs_rs2_e0, rs2_data_e0);
    wire [31:0] rs1_fwd1 = fwd_mux(fs_rs1_e1, rs1_data_e1);
    wire [31:0] rs2_fwd1 = fwd_mux(fs_rs2_e1, rs2_data_e1);

    // ---- pipe0 ALU ----
    wire [31:0] alu_a0 = (alu_a_sel_e0 == 2'd1) ? pc_e0 :
                         (alu_a_sel_e0 == 2'd2) ? 32'h0 : rs1_fwd0;
    wire [31:0] alu_b0 = alu_b_sel_e0 ? imm_e0 : rs2_fwd0;
    wire [31:0] alu_y0;
    alu u_alu0 (.op(alu_op_e0), .a(alu_a0), .b(alu_b0), .y(alu_y0));

    // ---- pipe1 ALU ----
    wire [31:0] alu_a1 = (alu_a_sel_e1 == 2'd1) ? pc_e1 :
                         (alu_a_sel_e1 == 2'd2) ? 32'h0 : rs1_fwd1;
    wire [31:0] alu_b1 = alu_b_sel_e1 ? imm_e1 : rs2_fwd1;
    wire [31:0] alu_y1;
    alu u_alu1 (.op(alu_op_e1), .a(alu_a1), .b(alu_b1), .y(alu_y1));

    // ---- branch resolve (pipe0) ----
    reg br_taken;
    always @(*) begin
        case (branch_op_e0)
            3'b000: br_taken = (rs1_fwd0 == rs2_fwd0);
            3'b001: br_taken = (rs1_fwd0 != rs2_fwd0);
            3'b100: br_taken = ($signed(rs1_fwd0) < $signed(rs2_fwd0));
            3'b101: br_taken = ($signed(rs1_fwd0) >= $signed(rs2_fwd0));
            3'b110: br_taken = (rs1_fwd0 < rs2_fwd0);
            3'b111: br_taken = (rs1_fwd0 >= rs2_fwd0);
            default: br_taken = 1'b0;
        endcase
    end

    wire mispredict = is_branch_e0 && (br_taken != pred_taken_e0);
    // jalr: no redirect when the RAS prediction matches the actual target
    wire [31:0] jalr_tgt = (rs1_fwd0 + imm_e0) & ~32'h1;
    wire jalr_mispred = is_jalr_e0 && !(pred_jalr_e0 && (jalr_tgt == pred_tgt_e0));

    // ---- Zicsr + M-mode trap (machine-only): mtvec/mepc/mcause/mscratch ----
    // csr/ecall/mret issue slot0-only with no slot1, one cycle in EX, and are
    // never wrong-path there (ID/EX is flushed on redirect), so side effects
    // commit exactly once.
    reg [31:0] csr_mtvec, csr_mepc, csr_mcause, csr_mscratch;
    wire [11:0] csr_addr  = instr_e0[31:20];
    wire [31:0] csr_rdata = (csr_addr == 12'h305) ? csr_mtvec    :
                            (csr_addr == 12'h341) ? csr_mepc     :
                            (csr_addr == 12'h342) ? csr_mcause   :
                            (csr_addr == 12'h340) ? csr_mscratch : 32'h0;
    // csrrw/csrrwi always write; csrrs/c[i] skip the write when rs1/uimm field is 0
    wire [31:0] csr_src   = mem_funct3_e0[2] ? imm_e0 : rs1_fwd0;
    wire [31:0] csr_wval  = (mem_funct3_e0[1:0] == 2'b01) ? csr_src :
                            (mem_funct3_e0[1:0] == 2'b10) ? (csr_rdata | csr_src) :
                                                            (csr_rdata & ~csr_src);
    wire csr_wr   = valid_e0 && is_csr_e0 && !redirect &&
                    !(mem_funct3_e0[1] && (instr_e0[19:15] == 5'd0));
    wire trap_ex  = valid_e0 && is_ecall_e0 && !redirect;
    always @(posedge clk) begin
        if (rst) begin
            csr_mtvec    <= 32'h0;
            csr_mepc     <= 32'h0;
            csr_mcause   <= 32'h0;
            csr_mscratch <= 32'h0;
        end else if (trap_ex) begin
            csr_mepc   <= pc_e0;
            csr_mcause <= instr_e0[20] ? 32'd3 : 32'd11; // ebreak / ecall-M
        end else if (csr_wr) begin
            case (csr_addr)
                12'h305: csr_mtvec    <= csr_wval;
                12'h341: csr_mepc     <= csr_wval;
                12'h342: csr_mcause   <= csr_wval;
                12'h340: csr_mscratch <= csr_wval;
                default: ;                       // unimplemented: write ignored
            endcase
        end
    end

    // !redirect: a wrong-path instr that issued during the ex_redir cycle sits
    // in EX now; it must not fire a second (bogus) redirect
    assign ex_redir = valid_e0 && !redirect &&
                      (jalr_mispred || is_fencei_e0 || mispredict ||
                       is_ecall_e0 || is_mret_e0);
    assign ex_redir_pc = is_ecall_e0  ? {csr_mtvec[31:2], 2'b00} :
                         is_mret_e0   ? csr_mepc :
                         is_jalr_e0   ? jalr_tgt :
                         is_fencei_e0 ? (pc_e0 + 32'd4) :
                         br_taken     ? (pc_e0 + imm_e0) :
                         (pc_e0 + 32'd4);

    // RAS push at EX: call = jal/jalr with rd in {ra, t0}
    assign ras_push     = valid_e0 && !redirect && (is_jal_e0 || is_jalr_e0) &&
                          (rd_e0 == 5'd1 || rd_e0 == 5'd5);
    assign ras_push_val = pc_e0 + 32'd4;

    // ---- predictor update pipeline register (EX result captured, applied
    // one cycle later). Keeps br_taken (forwarding-dependent) out of every
    // LUTRAM write-enable: a write-enable on a distributed RAM couples into
    // its ASYNC read port (write-through timing arc), which would drag the
    // fwd->compare chain into the issue/queue paths.
    wire [31:0] br_tgt_e0 = pc_e0 + imm_e0;
    reg        upd_br_r, upd_jal_r, upd_taken_r, upd_ptaken_r;
    reg        upd_btfn_r;
    reg [7:0]  upd_idx_r;
    reg [6:0]  upd_widx_r;
    reg [6:0]  upd_wtag_r;
    reg [13:0] upd_wtgt_r;
    always @(posedge clk) begin
        if (rst) begin
            upd_br_r <= 1'b0; upd_jal_r <= 1'b0;
        end else begin
            upd_br_r     <= valid_e0 && is_branch_e0 && !redirect;
            upd_jal_r    <= valid_e0 && is_jal_e0 && !redirect;

            upd_taken_r  <= br_taken;
            upd_ptaken_r <= pred_taken_e0;
            upd_btfn_r   <= btfn_e0;
            upd_idx_r    <= pht_idx_e0;
            upd_widx_r   <= pc_e0[8:2];
            upd_wtag_r   <= pc_e0[15:9];
            upd_wtgt_r   <= br_tgt_e0[15:2];
        end
    end

    assign btb_wr    = (upd_br_r && upd_taken_r) || upd_jal_r;
    assign btb_clr   = upd_br_r && !upd_taken_r && upd_ptaken_r;
    assign btb_widx  = upd_widx_r;
    assign btb_wtag  = upd_wtag_r;
    assign btb_wtgt  = upd_wtgt_r;
    // flush stays combinational: it must hit the BTB before the post-fence.i
    // refetch queries it (is_fencei_e0 is a FF; no forwarding dependence)
    assign btb_flush = valid_e0 && !redirect && is_fencei_e0;

    // gshare update: outcome vs static hint (agree encoding), GHR shift
    wire pht_agreed = (upd_taken_r == upd_btfn_r);
    always @(posedge clk) begin
        if (rst) begin
            ghr <= 8'd0;
        end else if (upd_br_r) begin
            ghr <= {ghr[6:0], upd_taken_r};
            if (pht_agreed && pht[upd_idx_r] != 2'b11)
                pht[upd_idx_r] <= pht[upd_idx_r] + 2'd1;
            else if (!pht_agreed && pht[upd_idx_r] != 2'b00)
                pht[upd_idx_r] <= pht[upd_idx_r] - 2'd1;
        end
    end

    // ---- divider (pipe0, multi-cycle via mstall) ----
    wire is_div_e0 = is_m_e0 && mem_funct3_e0[2];
    reg  m_started;
    wire md_done;
    wire [31:0] md_result;
    wire md_start = valid_e0 && is_div_e0 && !m_started && !redirect;
    muldiv u_md (
        .clk(clk), .rst(rst),
        .start(md_start), .funct3(mem_funct3_e0),
        .a(rs1_fwd0), .b(rs2_fwd0),
        .done(md_done), .result(md_result)
    );
    always @(posedge clk) begin
        if (rst)           m_started <= 1'b0;
        else if (md_done)  m_started <= 1'b0;
        else if (md_start) m_started <= 1'b1;
    end
    assign mstall = valid_e0 && is_div_e0 && !md_done && !redirect;

    // ---- pipelined multiplier (pipe0: EX -> M1 -> M2, result at WB) ----
    // EX: sign-extend operands (33x33); EX/M1 regs are the DSP input stage.
    // M1: multiply, product registered at M1/M2 (DSP output stage).
    // M2: hi/lo select, merged into result_w0 at the M2/WB boundary.
    // Consumers are blocked by ld_hazard while the MUL sits in EX or M1
    // (distance 3, same as sub-word loads), then forward from WB.
    wire is_mul_e0 = is_m_e0 && !mem_funct3_e0[2];
    wire mul_a_sgn = (mem_funct3_e0[1:0] != 2'b11);          // MUL/MULH/MULHSU
    wire mul_b_sgn = (mem_funct3_e0[1] == 1'b0);             // MUL/MULH
    reg                mul_v_m0, mul_hi_m0;
    reg  signed [32:0] mul_a_m0, mul_b_m0;
    reg                mul_v_x0, mul_hi_x0;
    reg  signed [65:0] mul_prod_x0;
    always @(posedge clk) begin
        if (rst) begin
            mul_v_m0 <= 1'b0;
            mul_v_x0 <= 1'b0;
        end else begin
            mul_v_m0  <= valid_e0 && is_mul_e0 && !redirect;
            mul_a_m0  <= {mul_a_sgn & rs1_fwd0[31], rs1_fwd0};
            mul_b_m0  <= {mul_b_sgn & rs2_fwd0[31], rs2_fwd0};
            mul_hi_m0 <= (mem_funct3_e0[1:0] != 2'b00);
            mul_v_x0    <= mul_v_m0;
            mul_hi_x0   <= mul_hi_m0;
            mul_prod_x0 <= mul_a_m0 * mul_b_m0;
        end
    end
    wire [31:0] mul_res_x0 = mul_hi_x0 ? mul_prod_x0[63:32] : mul_prod_x0[31:0];

    // ---- AGU + store lanes (pipe0) ----
    // Full 32-bit AGU: dmem commands to perip_bridge carry the complete address.
    wire [31:0] agu_addr = rs1_fwd0 + imm_e0;   // full address for dmem/bridge

    reg [3:0]  wstrb;
    reg [31:0] wdata_sh;
    always @(*) begin
        wstrb    = 4'b0;
        wdata_sh = rs2_fwd0;
        case (mem_funct3_e0[1:0])
            2'b00: begin
                wstrb    = 4'b0001 << agu_addr[1:0];
                wdata_sh = rs2_fwd0 << {agu_addr[1:0], 3'b000};
            end
            2'b01: begin
                wstrb    = agu_addr[1] ? 4'b1100 : 4'b0011;
                wdata_sh = agu_addr[1] ? {rs2_fwd0[15:0], 16'b0} : rs2_fwd0;
            end
            default: begin
                wstrb    = 4'b1111;
                wdata_sh = rs2_fwd0;
            end
        endcase
    end

    assign ld_e_v  = valid_e0 && (mem_read_e0 || is_mul_e0) && (rd_e0 != 5'd0);
    assign ld_e_rd = rd_e0;
    assign ld_e1_v  = valid_e1 && mem_read_e1 && (rd_e1 != 5'd0);
    assign ld_e1_rd = rd_e1;

    // ---- store-to-load forward buffer (4-entry, word-granular, DRAM only) ----
    // -O0 competition code re-reads freshly written stack slots constantly
    // (~49% of loads match one of the last 4 stores). EX-stage sw deposits
    // (word addr, data) round-robin; EX-stage lw CAM-matches combinationally
    // (newest-first priority, duplicates allowed), the hit is REGISTERED at
    // EX/M1: the load then behaves like an ALU op (data rides alu_m0 ->
    // alu_x0) and ld_m_v releases the consumer one cycle early (distance
    // 3 -> 2). Write-side enables depend only on rs1 high bits + funct3
    // (no AGU/CAM arc into the CEs). sb/sh to DRAM flush the buffer;
    // MMIO/IROM never enters (segment check on the BASE register: DRAM
    // bases always sit in 0x801xxxxx, MMIO in 0x802xxxxx, imm offsets
    // never cross segments in practice).
    reg [17:0] sf_addr [0:3];
    reg [31:0] sf_data [0:3];
    reg [3:0]  sf_v;
    reg [1:0]  sf_wp;

    wire ex_mem_ok = valid_e0 && !redirect;
    // ---- sf write side moved to M1 ----
    // Every write operand is a pipeline flop (dmem*_r command registers), so
    // no fwd/AGU arc reaches the sf array D/CE pins any more. The one-cycle
    // visibility gap (a store sitting in M1 has not written the arrays yet)
    // is closed by the read-side M1 bypass below. Wrong-path protection is
    // inherited from the dmem command registers (redirect-gated).
    wire sf_seg0   = (dmem_addr_r[31:20] == 12'h801) ||
                     (dmem_addr_r[31:16] == 16'h8000);
    wire sf_w0     = (dmem_wen_r == 4'hF) && sf_seg0;      // slot0 word store in M1
    wire sf_w1     = (dmem1_wen_r == 4'hF);                // slot1 store (word/seg by issue rule)
    wire sf_kill_m = (dmem_wen_r != 4'b0) && (dmem_wen_r != 4'hF) && sf_seg0;
    wire [17:0] sf_waddr = sf_w1 ? dmem1_addr_r[19:2] : dmem_addr_r[19:2];
    wire [31:0] sf_wdata = sf_w1 ? dmem1_wdata_r      : dmem_wdata_r;
    genvar sfi;
    // duplicate-address invalidation rides the sf_v D-path (all flop sources)
    wire [3:0] sf_dup;
    generate
        for (sfi = 0; sfi < 4; sfi = sfi + 1) begin : g_sfd
            assign sf_dup[sfi] = (sf_addr[sfi] == sf_waddr);
        end
    endgenerate
    always @(posedge clk) begin
        if (rst || (valid_e0 && is_fencei_e0) || sf_kill_m) begin
            sf_v  <= 4'b0;
            sf_wp <= 2'd0;
        end else if (sf_w0 || sf_w1) begin
            sf_addr[sf_wp] <= sf_waddr;
            sf_data[sf_wp] <= sf_wdata;
            sf_v           <= (sf_v & ~sf_dup) | (4'b0001 << sf_wp);
            sf_wp <= sf_wp + 2'd1;
        end
    end

    // read side: sum-addressed compare. Matching (rs1+imm)[19:2]==sf_addr
    // without the AGU adder on the path: candidates sf_addr-imm[19:2] (and
    // the +1-carry variant) are precomputed from FFs in parallel; the fwd
    // output then faces only a flat 18-bit equality compare. Carry into
    // bit2 comes from the 2-bit low add.
    wire sf_cy2 = (rs1_fwd0[1] & imm_e0[1]) |
                  ((rs1_fwd0[1] ^ imm_e0[1]) & (rs1_fwd0[0] & imm_e0[0]));
    wire [3:0] sf_m;
    generate
        for (sfi = 0; sfi < 4; sfi = sfi + 1) begin : g_sf
            wire [17:0] cand0 = sf_addr[sfi] - imm_e0[19:2];
            wire [17:0] cand1 = cand0 - 18'd1;
            assign sf_m[sfi] = sf_v[sfi] &&
                               (sf_cy2 ? (rs1_fwd0[19:2] == cand1)
                                       : (rs1_fwd0[19:2] == cand0));
        end
    endgenerate
    wire        sf_hit = |sf_m;
    wire [31:0] sf_rdata_arr = ({32{sf_m[0]}} & sf_data[0]) |
                               ({32{sf_m[1]}} & sf_data[1]) |
                               ({32{sf_m[2]}} & sf_data[2]) |
                               ({32{sf_m[3]}} & sf_data[3]);

    // M1 in-flight store bypass: the store one stage ahead has not written
    // the arrays yet; match it with the same sum-addressed trick (its address
    // registers are flops). A word match supplies the newest data; a
    // sub-word match suppresses the hit for this word instead.
    wire [17:0] byp0_c0 = dmem_addr_r[19:2] - imm_e0[19:2];
    wire [17:0] byp0_c1 = byp0_c0 - 18'd1;
    wire sf_byp0_m = sf_cy2 ? (rs1_fwd0[19:2] == byp0_c1)
                            : (rs1_fwd0[19:2] == byp0_c0);
    wire [17:0] byp1_c0 = dmem1_addr_r[19:2] - imm_e0[19:2];
    wire [17:0] byp1_c1 = byp1_c0 - 18'd1;
    wire sf_byp1_m = sf_cy2 ? (rs1_fwd0[19:2] == byp1_c1)
                            : (rs1_fwd0[19:2] == byp1_c0);
    wire sf_byp_w0   = sf_byp0_m && sf_w0;
    wire sf_byp_w1   = sf_byp1_m && sf_w1;
    wire sf_byp_kill = sf_byp0_m && sf_kill_m;

    wire [31:0] sf_rdata = sf_byp_w0 ? dmem_wdata_r  :
                           sf_byp_w1 ? dmem1_wdata_r : sf_rdata_arr;

    // read-side page qualifier (query side keeps its own base-reg check)
    wire sf_dram = (rs1_fwd0[31:20] == 12'h801) ||
                   (rs1_fwd0[31:16] == 16'h8000);

    // lw hit this EX cycle: data enters the ALU result path at EX/M1
    wire sf_ld_hit = ex_mem_ok && mem_read_e0 && (mem_funct3_e0 == 3'b010) &&
                     (sf_hit || sf_byp_w0 || sf_byp_w1) && !sf_byp_kill &&
                     sf_dram;

    // staged hit: data joins alu_x0 at M1/M2 (keeps sf arcs off alu_m0's mux)
    reg        sf_hit_m;
    reg [31:0] sf_rdata_r;
    always @(posedge clk) begin
        if (rst) sf_hit_m <= 1'b0;
        else     sf_hit_m <= sf_ld_hit && valid_e0 && !mstall && !redirect;
        sf_rdata_r <= sf_rdata;
    end

    // ---- L0 data cache (4KB direct-mapped, word lines, DRAM mirror) ----
    // Catches the lw traffic the sf buffer misses (~91% of it on -O0 code:
    // hot stack frame + array rows). Pure DRAM mirror, write-through with
    // store-allocate, so contents are correct by construction and never
    // need flushing. Lookup: EX computes agu_addr -> async LUTRAM tag read
    // + compare => l0_ld_hit, REGISTERED at EX/M1. The data BRAM port A is
    // addressed in EX and delivers in M1; at M1/M2 the hit data replaces
    // alu_x0 and mem_read_x0 is cleared, so the load finishes as an ALU op
    // (consumer forward from M2 slot, distance 3 -> 2 like an sf hit, and
    // ld_m_v releases the consumer one cycle early via registered l0_hit_m).
    // Write port B (single, arbitrated store-over-fill):
    //   M1 word store  -> write data + allocate tag
    //   M1 sub-word st -> invalidate line (rare in -O0; keeps RMW out)
    //   M2 load fill   -> write dmem_rdata + allocate (dropped if a store
    //                     wants the port this cycle)
    // Same-edge read/write races (port-B write lands while EX looks up the
    // same line with a stale tag view) are excluded from the hit term.
    reg [31:0] l0_mem [0:1023];          // 1 RAMB36, true dual port
    reg [7:0]  l0_tag [0:1023];          // LUTRAM, async read
    reg        l0_varr [0:1023];
    integer li;
    initial begin
        for (li = 0; li < 1024; li = li + 1) begin
            l0_varr[li] = 1'b0;
            l0_tag[li]  = 8'h00;
        end
    end

    wire [9:0] l0_idx  = l0_spec_addr[11:2];   // speculative (flop-sourced) index
    wire [7:0] l0_rtag = l0_tag[l0_idx];
    wire       l0_rv   = l0_varr[l0_idx];

    // write side (all operands registered: M1 dmem command / M2 fill regs)
    wire        l0_st_m1   = (dmem_wen_r != 4'b0) && (dmem_addr_r[31:20] == 12'h801);
    wire        l1_st_m1   = (dmem1_wen_r != 4'b0) && (dmem1_addr_r[31:20] == 12'h801);
    wire        l0_st_word = (dmem_wen_r == 4'hF);
    reg         l0_fill_v;
    reg  [9:0]  l0_fill_idx;
    reg  [7:0]  l0_fill_tag;

    // same-edge race exclusion for the EX lookup
    wire l0_race = (l0_st_m1   && dmem_addr_r[11:2]  == l0_idx) ||
                   (l1_st_m1   && dmem1_addr_r[11:2] == l0_idx) ||
                   (l0_fill_vd && l0_fill_idxd      == l0_idx) ||
                   (l1_fill_vd && l1_fill_idxd      == l0_idx);

    // Speculative lookup off the ID/EX flops: address/tag/segment are formed
    // from rs1_data_e0 (+imm), valid only when the base has no forward
    // pending (fs_rs1_e0==0, a shallow 6-bit NOR). A forwarded base simply
    // misses L0 and takes the normal distance-3 DRAM path -- rare in -O0
    // (bases are long-lived s0/sp). This removes the fwd-mux level from the
    // tag arc. (A 3:1 flop-mux base incl. WB-forward legs was tried: zero
    // gain -- forwarded bases are almost always M1/M2-stage producers.)
    // The sf exclusion is gone too: an sf hit implies the L0 line
    // (store-allocated by the same store) holds the identical value, so a
    // double hit is benign.
    wire [31:0] l0_spec_addr = rs1_data_e0 + imm_e0;
    wire        l0_spec_ok   = (fs_rs1_e0 == 6'd0);
    wire l0_dram_e = (rs1_data_e0[31:20] == 12'h801);
    wire l0_ld_hit = mem_read_e0 && (mem_funct3_e0 == 3'b010) && l0_dram_e &&
                     l0_spec_ok &&
                     l0_rv && (l0_rtag == l0_spec_addr[19:12]) && !l0_race;

    reg        l0_hit_m;
    reg [31:0] l0_douta;
    always @(posedge clk) begin
        if (rst) l0_hit_m <= 1'b0;
        else     l0_hit_m <= l0_ld_hit && valid_e0 && !mstall && !redirect;
        l0_douta <= l0_mem[l0_idx];                       // port A read
    end

    // ---- slot1 lookup: shadow copy of the data array (BRAM has only two
    // ports; the shadow is written in lockstep) + duplicated LUTRAM tag read.
    // A slot1 L0 hit turns the dmem1 load into distance 2, same shape as
    // slot0: hit registered at EX/M1, data replaces alu_x1 at M1/M2,
    // ld_m1_v releases the consumer via the registered bit.
    reg [31:0] l0_mem2 [0:1023];
    // slot1 loads issue only with fsel_rs1_1==0 (no forward pending), so the
    // forwarded base equals the ID/EX-registered regfile value: feed the AGU
    // straight from the flop and skip the forward mux level entirely.
    wire [31:0] agu_addr1 = rs1_data_e1 + imm_e1;
    wire [9:0] l0_idx1  = agu_addr1[11:2];
    wire [7:0] l0_rtag1 = l0_tag[l0_idx1];
    wire       l0_rv1   = l0_varr[l0_idx1];
    wire l0_race1 = (l0_st_m1   && dmem_addr_r[11:2]  == l0_idx1) ||
                    (l1_st_m1   && dmem1_addr_r[11:2] == l0_idx1) ||
                    (l0_fill_vd && l0_fill_idxd      == l0_idx1) ||
                    (l1_fill_vd && l1_fill_idxd      == l0_idx1);
    wire l0_ld_hit1 = valid_e1 && mem_read_e1 && is_dram_e1 &&
                      (instr_e1[14:12] == 3'b010) &&
                      l0_rv1 && (l0_rtag1 == agu_addr1[19:12]) && !l0_race1;
    reg        l0_hit1_m;
    reg [31:0] l0_douta1;
    always @(posedge clk) begin
        if (rst) l0_hit1_m <= 1'b0;
        else     l0_hit1_m <= l0_ld_hit1 && !mstall && !redirect;
        l0_douta1 <= l0_mem2[l0_idx1];
        if (l0_dw_en) l0_mem2[l0_dw_idx] <= l0_dw_data;   // lockstep write
    end

    // fill request: any DRAM load that still reads the big BRAM this M1
    always @(posedge clk) begin
        if (rst) l0_fill_v <= 1'b0;
        else begin
            l0_fill_v   <= valid_m0 && mem_read_m0 && !l0_hit_m &&
                           (dmem_addr_r[31:20] == 12'h801);
            l0_fill_idx <= dmem_addr_r[11:2];
            l0_fill_tag <= dmem_addr_r[19:12];
        end
    end

    // fill staged one more cycle: dmem_rdata is registered before touching
    // the L0 write ports (keeps the DRAM douta fanout on a single arc)
    reg         l0_fill_vd;
    reg  [9:0]  l0_fill_idxd;
    reg  [7:0]  l0_fill_tagd;
    reg  [31:0] l0_fill_data;
    always @(posedge clk) begin
        if (rst) l0_fill_vd <= 1'b0;
        else     l0_fill_vd <= l0_fill_v;
        l0_fill_idxd <= l0_fill_idx;
        l0_fill_tagd <= l0_fill_tag;
        l0_fill_data <= dmem_rdata;
    end

    // fill #2: slot1 dmem1 loads (lowest write-port priority, DRAM only)
    reg         l1_fill_v, l1_fill_vd;
    reg  [9:0]  l1_fill_idx,  l1_fill_idxd;
    reg  [7:0]  l1_fill_tag,  l1_fill_tagd;
    reg  [31:0] l1_fill_data;
    always @(posedge clk) begin
        if (rst) begin
            l1_fill_v <= 1'b0; l1_fill_vd <= 1'b0;
        end else begin
            l1_fill_v   <= valid_m1 && mem_read_m1 && !l0_hit1_m &&
                           (dmem1_addr_r[31:20] == 12'h801);
            l1_fill_vd  <= l1_fill_v;
        end
        l1_fill_idx  <= dmem1_addr_r[11:2];
        l1_fill_tag  <= dmem1_addr_r[19:12];
        l1_fill_idxd <= l1_fill_idx;
        l1_fill_tagd <= l1_fill_tag;
        l1_fill_data <= dmem1_rdata;
    end

    // port B write + tag write (priority: store0 > store1 > fill0 > fill1;
    // the two stores are mutually exclusive by issue rule, fills may drop)
    wire        l0_dw_en   = (l0_st_m1 && l0_st_word) || l1_st_m1 ||
                             (!l0_st_m1 && (l0_fill_vd || l1_fill_vd));
    wire [9:0]  l0_dw_idx  = l0_st_m1   ? dmem_addr_r[11:2]  :
                             l1_st_m1   ? dmem1_addr_r[11:2] :
                             l0_fill_vd ? l0_fill_idxd       : l1_fill_idxd;
    wire [31:0] l0_dw_data = l0_st_m1   ? dmem_wdata_r       :
                             l1_st_m1   ? dmem1_wdata_r      :
                             l0_fill_vd ? l0_fill_data       : l1_fill_data;
    wire        l0_tw_en   = l0_st_m1 || l1_st_m1 || l0_fill_vd || l1_fill_vd;
    wire [9:0]  l0_tw_idx  = l0_st_m1   ? dmem_addr_r[11:2]   :
                             l1_st_m1   ? dmem1_addr_r[11:2]  :
                             l0_fill_vd ? l0_fill_idxd        : l1_fill_idxd;
    wire [7:0]  l0_tw_tag  = l0_st_m1   ? dmem_addr_r[19:12]  :
                             l1_st_m1   ? dmem1_addr_r[19:12] :
                             l0_fill_vd ? l0_fill_tagd        : l1_fill_tagd;
    wire        l0_tw_v    = l0_st_m1 ? l0_st_word : 1'b1;    // store1 is always a word
    always @(posedge clk) begin
        if (l0_dw_en) l0_mem[l0_dw_idx] <= l0_dw_data;    // port B write
    end
    always @(posedge clk) begin
        if (l0_tw_en) begin
            l0_tag[l0_tw_idx]  <= l0_tw_tag;
            l0_varr[l0_tw_idx] <= l0_tw_v;
        end
    end

    // ================ EX/M1 ================
    reg        valid_m0, valid_m1;
    reg [31:0] pc_m0, instr_m0, alu_m0;
    reg [31:0] pc_m1, instr_m1, alu_m1;
    reg [4:0]  rd_m0, rd_m1;
    reg        mem_read_m0, rd_wen_m0, rd_wen_m1;
    reg        mem_read_m1;
    reg [2:0]  mem_funct3_m0;
    reg [31:0] dmem_addr_r, dmem_wdata_r;
    reg [3:0]  dmem_wen_r;
    reg        dmem_ren_r;
    reg [31:0] dmem1_addr_r;
    reg        dmem1_ren_r;
    reg [3:0]  dmem1_wen_r;
    reg [31:0] dmem1_wdata_r;
    always @(posedge clk) begin
        if (rst) begin
            valid_m0 <= 1'b0; valid_m1 <= 1'b0;
            mem_read_m0 <= 1'b0; rd_wen_m0 <= 1'b0; rd_wen_m1 <= 1'b0;
            mem_read_m1 <= 1'b0;
            rd_m0 <= 5'd0; rd_m1 <= 5'd0;
            dmem_wen_r <= 4'b0; dmem_ren_r <= 1'b0; dmem1_ren_r <= 1'b0;
            dmem1_wen_r <= 4'b0;
        end else begin
            valid_m0      <= valid_e0 && !mstall && !redirect;
            pc_m0         <= pc_e0;
            instr_m0      <= instr_e0;
            // sf-hit data does NOT enter alu_m0 (keeps the deep sf_rdata /
            // sf_ld_hit arcs off the EX-critical 32-bit mux): it is staged in
            // sf_rdata_r and joins the ALU path at M1/M2 like an L0 hit.
            // Safe: a consumer can never source an sf-hit load from the M1
            // slot (it was ld_e_v-blocked while the load sat in EX).
            alu_m0        <= is_div_e0 ? md_result :
                             is_csr_e0 ? csr_rdata :
                             (wb_sel_e0 == 2'd2) ? (pc_e0 + 32'd4) : alu_y0;
            rd_m0         <= rd_e0;
            // a forwarded lw becomes an ALU op from M1 on: data rides
            // alu_m0/alu_x0, consumers release one cycle early via ld_m_v
            mem_read_m0   <= mem_read_e0 & valid_e0 & ~sf_ld_hit;
            mem_funct3_m0 <= mem_funct3_e0;
            rd_wen_m0     <= rd_wen_e0 & valid_e0 & ~mstall & ~redirect;

            dmem_addr_r  <= {agu_addr[31:2], 2'b00};
            dmem_wdata_r <= wdata_sh;
            dmem_wen_r   <= (valid_e0 && mem_write_e0 && !redirect) ? wstrb : 4'b0;
            dmem_ren_r   <= valid_e0 && mem_read_e0 && !redirect;

            // wrong-path group (issued during the ex_redir cycle) dies here
            // via the registered redirect; the same-group slot1 of the
            // redirecting instruction is killed one stage later at M1/M2
            valid_m1  <= valid_e1 && !mstall && !redirect;
            pc_m1     <= pc_e1;
            instr_m1  <= instr_e1;
            alu_m1    <= alu_y1;
            rd_m1     <= rd_e1;
            rd_wen_m1 <= rd_wen_e1 & valid_e1 & ~mstall & ~redirect;

            // slot1 load command (port 1, read-only)
            mem_read_m1  <= mem_read_e1 & valid_e1 & ~mstall & ~redirect;
            dmem1_addr_r <= {agu_addr1[31:2], 2'b00};
            dmem1_ren_r  <= mem_read_e1 & valid_e1 & ~mstall & ~redirect;
            // slot1 word store: issue rule guarantees no same-group slot0
            // mem op / branch, so no ex_redir term is needed here (wrong-path
            // groups are killed by the registered redirect before EX).
            dmem1_wen_r  <= (mem_write_e1 & valid_e1 & ~mstall & ~redirect) ? 4'hF : 4'b0;
            dmem1_wdata_r<= casc_st_e1 ? alu_y0 : rs2_fwd1;
        end
    end

    // ================= M1 =================
    // dmem command drives the BRAM from FFs; BRAM latches at the M1/M2 edge
    assign dmem_addr  = dmem_addr_r;
    assign dmem_ren   = dmem_ren_r;
    assign dmem_wen   = dmem_wen_r;
    assign dmem_wdata = dmem_wdata_r;
    assign dmem1_addr  = dmem1_addr_r;
    assign dmem1_ren   = dmem1_ren_r;
    assign dmem1_wen   = dmem1_wen_r;
    assign dmem1_wdata = dmem1_wdata_r;

    // l0_hit_m releases the consumer one cycle early (registered bit, no
    // BRAM/tag arc enters this issue-side gate)
    assign ld_m_v  = valid_m0 && ((mem_read_m0 && !l0_hit_m) || mul_v_m0) && (rd_m0 != 5'd0);
    assign ld_m_rd = rd_m0;
    assign ld_m1_v  = valid_m1 && mem_read_m1 && !l0_hit1_m && (rd_m1 != 5'd0);
    assign ld_m1_rd = rd_m1;

    // ================ M1/M2 ================
    reg        valid_x0, valid_x1;
    reg [31:0] pc_x0, instr_x0, alu_x0;
    reg [31:0] pc_x1, instr_x1, alu_x1;
    reg [4:0]  rd_x0, rd_x1;
    reg        mem_read_x0, rd_wen_x0, rd_wen_x1;
    reg        mem_read_x1;
    reg [2:0]  mem_funct3_x0, mem_funct3_x1;
    // pre-decoded load-align controls: everything the M2 align network needs
    // is a flop output, so dmem_rdata faces only rotate+mask (3 LUT levels)
    reg [1:0]  ld_rot_x0;
    reg        ld_b_x0, ld_h_x0, ld_sgn_x0;
    always @(posedge clk) begin
        if (rst) begin
            valid_x0 <= 1'b0; valid_x1 <= 1'b0;
            mem_read_x0 <= 1'b0; rd_wen_x0 <= 1'b0; rd_wen_x1 <= 1'b0;
            mem_read_x1 <= 1'b0;
            rd_x0 <= 5'd0; rd_x1 <= 5'd0;
        end else begin
            valid_x0      <= valid_m0;
            pc_x0         <= pc_m0;
            instr_x0      <= instr_m0;
            alu_x0        <= l0_hit_m ? l0_douta :
                             sf_hit_m ? sf_rdata_r : alu_m0;   // hit data joins the ALU path here
            rd_x0         <= rd_m0;
            mem_read_x0   <= mem_read_m0 & ~l0_hit_m;
            mem_funct3_x0 <= mem_funct3_m0;
            ld_rot_x0 <= (mem_funct3_m0[1:0] == 2'b00) ? alu_m0[1:0] :
                         (mem_funct3_m0[1:0] == 2'b01) ? {alu_m0[1], 1'b0} : 2'b00;
            ld_b_x0   <= (mem_funct3_m0[1:0] == 2'b00);
            ld_h_x0   <= (mem_funct3_m0[1:0] == 2'b01);
            ld_sgn_x0 <= ~mem_funct3_m0[2];
            rd_wen_x0     <= rd_wen_m0 & valid_m0;

            // when redirect==1, M1 holds the group whose slot0 redirected in
            // EX last cycle: its slot1 is younger wrong-path work -> kill
            valid_x1  <= valid_m1 && !redirect;
            pc_x1     <= pc_m1;
            instr_x1  <= instr_m1;
            alu_x1    <= l0_hit1_m ? l0_douta1 : alu_m1;
            rd_x1     <= rd_m1;
            rd_wen_x1 <= rd_wen_m1 & valid_m1 & ~redirect;
            mem_read_x1   <= mem_read_m1 & valid_m1 & ~redirect & ~l0_hit1_m;
            mem_funct3_x1 <= instr_m1[14:12];
        end
    end

    // ================= M2 =================
    // dmem_rdata valid this cycle; align controls are all pre-decoded flops:
    // data path = 4:1 rotate (1 LUT) // parallel sign pick, then segment mask.
    wire [31:0] ld_rot0 =
        (ld_rot_x0 == 2'd0) ? dmem_rdata :
        (ld_rot_x0 == 2'd1) ? {dmem_rdata[7:0],  dmem_rdata[31:8]}  :
        (ld_rot_x0 == 2'd2) ? {dmem_rdata[15:0], dmem_rdata[31:16]} :
                              {dmem_rdata[23:0], dmem_rdata[31:24]};
    wire ld_sb0 = ld_sgn_x0 & ((ld_rot_x0 == 2'd0) ? dmem_rdata[7]  :
                               (ld_rot_x0 == 2'd1) ? dmem_rdata[15] :
                               (ld_rot_x0 == 2'd2) ? dmem_rdata[23] : dmem_rdata[31]);
    wire ld_sh0 = ld_sgn_x0 & (ld_rot_x0[1] ? dmem_rdata[31] : dmem_rdata[15]);
    reg [31:0] load_data;
    always @(*) begin
        load_data[7:0]   = ld_rot0[7:0];
        load_data[15:8]  = ld_b_x0 ? {8{ld_sb0}} : ld_rot0[15:8];
        load_data[31:16] = ld_b_x0 ? {16{ld_sb0}} :
                           ld_h_x0 ? {16{ld_sh0}} : ld_rot0[31:16];
    end

    // slot1 loads are lw-only (issue rule): dmem1_rdata goes straight through
    wire [31:0] load_data1 = dmem1_rdata;

    // ================ M2/WB ================
    reg        valid_w0, valid_w1;
    reg [31:0] pc_w0, instr_w0, result_w0;
    reg [31:0] pc_w1, instr_w1, result_w1;
    reg [4:0]  rd_w0, rd_w1;
    reg        rd_wen_w0, rd_wen_w1;
    always @(posedge clk) begin
        if (rst) begin
            valid_w0 <= 1'b0; valid_w1 <= 1'b0;
            rd_wen_w0 <= 1'b0; rd_wen_w1 <= 1'b0;
            rd_w0 <= 5'd0; rd_w1 <= 5'd0;
        end else begin
            valid_w0  <= valid_x0;
            pc_w0     <= pc_x0;
            instr_w0  <= instr_x0;
            result_w0 <= mem_read_x0 ? load_data :
                         mul_v_x0    ? mul_res_x0 : alu_x0;
            rd_w0     <= rd_x0;
            rd_wen_w0 <= rd_wen_x0 & valid_x0;

            valid_w1  <= valid_x1;
            pc_w1     <= pc_x1;
            instr_w1  <= instr_x1;
            result_w1 <= mem_read_x1 ? load_data1 : alu_x1;
            rd_w1     <= rd_x1;
            rd_wen_w1 <= rd_wen_x1 & valid_x1;
        end
    end

    // ================= WB =================
    assign wb_wen0   = rd_wen_w0;
    assign wb_rd0    = rd_w0;
    assign wb_wdata0 = result_w0;
    assign wb_wen1   = rd_wen_w1;
    assign wb_rd1    = rd_w1;
    assign wb_wdata1 = result_w1;

    assign commit0_valid    = valid_w0;
    assign commit0_pc       = pc_w0;
    assign commit0_instr    = instr_w0;
    assign commit0_rd_wen   = rd_wen_w0;
    assign commit0_rd       = rd_w0;
    assign commit0_rd_wdata = result_w0;

    assign commit1_valid    = valid_w1;
    assign commit1_pc       = pc_w1;
    assign commit1_instr    = instr_w1;
    assign commit1_rd_wen   = rd_wen_w1;
    assign commit1_rd       = rd_w1;
    assign commit1_rd_wdata = result_w1;

`ifdef VERILATOR
    // ---- perf attribution probe (simulation only, excluded from synthesis) ----
    wire [15:0] perf_probe /* verilator public_flat_rd */ = {
        mem_read_1 | mem_write_1,   // 15 slot1 candidate is a load/store
        raw01 | waw01,              // 14 slot1 blocked: RAW/WAW on slot0
        i0_ctrl,                    // 13 slot1 blocked: slot0 is ctrl/muldiv
        i1_simple,                  // 12 slot1 candidate is simple ALU
        id_redirect,                // 11 cold JAL/BTFN redirect at issue
        valid_e0 & is_fencei_e0,    // 10 ex redirect: fence.i
        valid_e0 & is_jalr_e0,      // 9  ex redirect: jalr
        valid_e0 & mispredict,      // 8  ex redirect: branch mispredict
        redirect,                   // 7  registered redirect (flush cycle)
        mstall,                     // 6  muldiv stall
        hz1,                        // 5  slot1 load-use hazard
        hz0,                        // 4  slot0 load-use hazard
        v1,                         // 3  queue has >=2 entries
        v0,                         // 2  queue has >=1 entry
        issue1,                     // 1
        issue0                      // 0
    };
    wire [3:0] perf_probe2 /* verilator public_flat_rd */ = {
        mem_read_0,                             // 3 slot0 is a load
        mem_read_1,                             // 2 slot1 candidate is a load
        is_muldiv_1,                            // 1 slot1 candidate is mul/div
        rd_wen_0 & mem_read_0 & (rd_0 != 5'd0) &
        ((uses_rs1_1 & (rs1_1 == rd_0)) | (uses_rs2_1 & (rs2_1 == rd_0)))
                                                // 0 raw01 where slot0 is a load
    };
    // stats probe for optimization sizing (see fpga_race/sim/tb_stats.cpp).
    // Findings on irom-v2: ret issued 140x / lui+addi pairs 64x (both dead
    // ends), mul-blocked cycles 0.102 CPI (store-data exemption tried: zero
    // gain; general M2 mul-forward leg: timing-rejected by the DSP P-reg arc)
    wire [7:0] perf_probe3 /* verilator public_flat_rd */ = {
        ras_ret_0 && v0,                                    // 7 ret at queue head
        v0 && v1 && (in_0[6:0] == 7'b0110111) &&            // 6 lui+addi fusable pair
            (in_1[6:0] == 7'b0010011) && (in_1[14:12] == 3'b000) &&
            (in_1[19:15] == in_0[11:7]) && (in_1[11:7] == in_0[11:7]),
        hz0 && mul_v_m0 && is_muldiv_0,                     // 5 mul@M1 blocking a muldiv consumer (E1-recoverable)
        hz0 && valid_m0 && mem_read_m0 && !l0_hit_m,        // 4 blocked by M1 load miss
        hz0 && valid_e0 && mem_read_e0,                     // 3 blocked by EX load
        hz0 && ((valid_e0 && is_mul_e0) || mul_v_m0),       // 2 blocked by mul in flight
        idr_r,                                              // 1 issue-redirect bubble cycle
        ras_ret_0 && issue0                                 // 0 ret issued
    };
`endif
endmodule
