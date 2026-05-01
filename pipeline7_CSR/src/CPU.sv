`include "config.sv"
module CPU#(
    parameter PC_RESET_VALUE = 32'h00000000
)(
    input  logic         cpu_rst,
    input  logic         cpu_clk,

    // Interface to IROM, you need add some signals
    input logic [31:0]   irom_rdata,
    output logic         irom_en,
    output logic         irom_rst,
    output logic [31:0]  irom_addr,//输出内部的pc作为地址
    
    // Interface to DRAM, you need add some signals
    input  logic [31:0]  bus_rdata,
    output logic [31:0]  bus_addr,
    output logic [31:0]  bus_wdata,
    output logic [ 3:0]  bus_wen,

    output logic         debug_wb_have_inst,
    output logic [31:0]  debug_wb_pc,
    output logic         debug_wb_ena,
    output logic [ 4:0]  debug_wb_reg,
    output logic [31:0]  debug_wb_value
);
    /* IF1 stage */
    logic [0:0]     predict_taken_if1, predict_taken_if2, predict_taken_id, predict_taken_ex;
    logic [31:0]    pc_to_take_if1, pc_to_take_if2, pc_to_take_id, pc_to_take_ex;
    logic [31:0]    pc_if1, pc_if2, pc_id, pc_ex, pc_ls1, pc_ls2, pc_wb;
    logic [31:0]    inst_if2, inst_id, inst_ex, inst_ls1,inst_ls2, inst_wb;
    logic [31:0]    pc_target, next_pc;
    logic [31:0]    imm_id, imm_ex;
    logic [31:0]    rf_wdata_wb;
    logic [31:0]    rf_rdata1_id, rf_rdata1_ex;
    logic [31:0]    rf_rdata2_id, rf_rdata2_ex;
    logic [31:0]    forward1_data, forward2_data;
    logic [31:0]    alu_rf_data1, alu_rf_data2;
    logic [31:0]    alu_rs1, alu_rs2;
    logic [31:0]    alu_result_ex, alu_result_ls1,alu_result_ls2, alu_result_wb;
    logic [31:0]    jump_target;
    logic [31:0]    mem_wdata_ex;
    logic [31:0]    mem_rdata_ls2, mem_rdata_wb; 
    logic [31:0]    dcache_rdata_ls1;
    logic [ 4:0]    alu_op_id, alu_op_ex;
    logic [ 4:0]    mem_access_id, mem_access_ex, mem_access_ls1,mem_access_ls2, mem_access_wb;
    logic [ 4:0]    br_type_id, br_type_ex;
    logic [ 1:0]    alu_rs1_sel_id, alu_rs1_sel_ex;
    logic [ 1:0]    alu_rs2_sel_id, alu_rs2_sel_ex;
    logic [ 0:0]    wb_rf_sel_id, wb_rf_sel_ex, wb_rf_sel_ls1, wb_rf_sel_ls2, wb_rf_sel_wb;
    logic [ 0:0]    rf_we_id, rf_we_ex, rf_we_ls1, rf_we_ls2, rf_we_wb;

    logic [ 0:0]    forward1_en, forward2_en;
    logic [ 0:0]    jump;
    logic [ 0:0]    pc_set, pc_stall;
    logic [ 0:0]    IF1_IF2_stall, IF1_IF2_flush;
    logic [ 0:0]    IF2_ID_stall, IF2_ID_flush;
    logic [ 0:0]    ID_EX_flush,ID_EX_stall;
    logic [ 0:0]    EX_LS1_flush;
    logic [ 0:0]    LS1_LS2_flush;
    logic [ 0:0]    LS2_WB_flush;

    logic [ 0:0]    have_inst_id, have_inst_ex, have_inst_ls1, have_inst_ls2, have_inst_wb;

    wire is_ctrl_ex = have_inst_ex && br_type_ex[4];
    wire is_jal_ex = is_ctrl_ex && br_type_ex[3] && br_type_ex[2];
    wire is_jalr_ex = is_ctrl_ex && br_type_ex[3] && !br_type_ex[2];
    wire is_cond_branch_ex = is_ctrl_ex && !br_type_ex[3];
    wire writes_link_ex = (inst_ex[11:7] == 5'd1) || (inst_ex[11:7] == 5'd5);
    wire is_call_ex = is_ctrl_ex && writes_link_ex;
    wire is_ret_ex = is_jalr_ex && (inst_ex[19:15] == 5'd1) && (inst_ex[11:7] == 5'd0) && (imm_ex == 32'd0);
    wire bpu_update_en = is_ctrl_ex;
    wire ras_push_ex = have_inst_ex && jump && is_call_ex;
    wire ras_pop_ex = have_inst_ex && jump && is_ret_ex;
    wire [31:0] ras_push_addr_ex = pc_ex + 32'd4;

    //CSR related
    logic [ 2:0]    priv_vec_id, priv_vec_ex, priv_vec_ls1, priv_vec_ls2, priv_vec_wb;
    logic [31:0]    csr_rdata_id, csr_rdata_ex;//Read CSR at ID, process it at EX
    logic [31:0]    csr_wdata_ex, csr_wdata_ls1, csr_wdata_ls2, csr_wdata_wb;// write back to GPR at WB, but write to CSR at EX
    logic [31:0]    mepc_global, mtvec_global, mcause_global;


    BPU BPU_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .pc_if1         (pc_if1),
        .predict_taken  (predict_taken_if1),
        .pc_to_take     (pc_to_take_if1),
        .btb_hit        (btb_hit_if1),

        .update_en      (bpu_update_en),
        .update_pc      (bpu_update_pc),
        .actual_taken   (bpu_actual_taken),
        .actual_target  (bpu_actual_target),
        .update_is_ret  (bpu_update_is_ret),
        .ras_push       (bpu_ras_push),
        .ras_pop        (bpu_ras_pop),
        .ras_push_addr  (bpu_ras_push_addr)
    );

    NPC_Mux  NPC_Mux_inst (
        .pc             (pc_if1),
        .pc_set         (pc_set),
        .branch_taken   (predict_taken_if1),
        .predict_target (pc_to_take_if1),
        .pc_target      (pc_target),
        .next_pc        (next_pc)
    );

    PC#(
        .RESET_VALUE(PC_RESET_VALUE)
    ) PC_inst (
        .clk        (cpu_clk),
        .rst        (cpu_rst),
        .stall      (pc_stall),
        .next_pc    (next_pc),
        .pc         (pc_if1)
    );


    /* IF1-IF2 segreg */
    SegReg_IF1_IF2 # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_IF1_IF2_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .stall              (IF1_IF2_stall),
        .flush              (IF1_IF2_flush),
        .pc_if1             (pc_if1),
        .predict_taken_if1  (predict_taken_if1),
        .predict_target_if1 (pc_to_take_if1),
        .pc_if2             (pc_if2),
        .predict_taken_if2  (predict_taken_if2),
        .predict_target_if2 (pc_to_take_if2)
    );

    assign irom_addr = pc_if1;
    assign inst_if2  = irom_rdata;
    assign irom_en   = ~IF1_IF2_stall;
    assign irom_rst  = IF1_IF2_flush;

    /* IF2 stage */
    /* IF2-ID segreg */
    SegReg_IF2_ID # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_IF2_ID_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .stall              (IF2_ID_stall),
        .flush              (IF2_ID_flush),
        .pc_if2             (pc_if2),
        .inst_if2           (inst_if2),
        .predict_taken_if2  (predict_taken_if2),
        .predict_target_if2 (pc_to_take_if2),
        .pc_id              (pc_id),
        .inst_id            (inst_id),
        .predict_taken_id   (predict_taken_id),
        .predict_target_id  (pc_to_take_id)
    );

    /* ID stage */
    logic [0:0] branch_taken_id; // Still used locally in ID for BTFN status, but doesn't affect NPC anymore
    Decode  Decode_inst (
        .inst           (inst_id),
        .have_inst      (have_inst_id),
        .alu_op         (alu_op_id),
        .mem_access     (mem_access_id),
        .imm            (imm_id),
        .rf_we          (rf_we_id),
        .alu_rs1_sel    (alu_rs1_sel_id),
        .alu_rs2_sel    (alu_rs2_sel_id),
        .wb_rf_sel      (wb_rf_sel_id),
        .br_type        (br_type_id),
        .priv_vec      (priv_vec_id),
        .branch_taken   (branch_taken_id)
    );
    Regfile  Regfile_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .raddr1         (inst_id[19:15]),
        .raddr2         (inst_id[24:20]),
        .waddr          (inst_wb[11:7]),
        .wdata          (rf_wdata_wb),
        .we             (rf_we_wb),
        .rdata1         (rf_rdata1_id),
        .rdata2         (rf_rdata2_id)
    );
    CSR  CSR_inst (
        .clk            (cpu_clk),
        .rst           (cpu_rst),
        .raddr          (inst_id[31:20]),//csr addr
        .waddr          (inst_wb[31:20]),//csr addr
        .we             (priv_vec_wb[`CSR_RW]), 
        .wdata          (csr_wdata_wb),
        .rdata          (csr_rdata_id),

        .mepc_out       (mepc_global),
        .pc_wb          (pc_wb),
        .mtvec_out      (mtvec_global),
        .mcause_in      (mcause_global),
        .priv_vec_wb    (priv_vec_wb)
    );

    /* ID-EX segreg */
    SegReg_ID_EX # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_ID_EX_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .stall          (ID_EX_stall),
        .flush          (ID_EX_flush),
        .pc_id          (pc_id),
        .inst_id        (inst_id),
        .rdata1_id      (rf_rdata1_id),
        .rdata2_id      (rf_rdata2_id),
        .imm_id         (imm_id),
        .mem_access_id  (mem_access_id),
        .alu_op_id          (alu_op_id),
        .br_type_id     (br_type_id),
        .wb_rf_sel_id   (wb_rf_sel_id),
        .alu_rs1_sel_id (alu_rs1_sel_id),
        .alu_rs2_sel_id (alu_rs2_sel_id),
        .rf_we_id       (rf_we_id),
        .predict_taken_id(predict_taken_id),
        .predict_target_id(pc_to_take_id),
        //.tage_meta_id   (tage_meta_id),
        .predict_taken_ex(predict_taken_ex),
        .predict_target_ex(pc_to_take_ex),
        //.tage_meta_ex   (tage_meta_ex),
        .pc_ex          (pc_ex),
        .inst_ex        (inst_ex),
        .rdata1_ex      (rf_rdata1_ex),
        .rdata2_ex      (rf_rdata2_ex),
        .imm_ex         (imm_ex),
        .mem_access_ex  (mem_access_ex),
        .alu_op_ex          (alu_op_ex),
        .br_type_ex     (br_type_ex),
        .wb_rf_sel_ex   (wb_rf_sel_ex),
        .alu_rs1_sel_ex (alu_rs1_sel_ex),
        .alu_rs2_sel_ex (alu_rs2_sel_ex),
        .rf_we_ex       (rf_we_ex),
        .csr_rdata_id      (csr_rdata_id),
        .csr_rdata_ex    (csr_rdata_ex),
        .priv_vec_id      (priv_vec_id),
        .priv_vec_ex      (priv_vec_ex),
        .have_inst_id   (have_inst_id),
        .have_inst_ex   (have_inst_ex)
    );


    /* EX stage */
    Mux2_1 # (
        .WIDTH(32)
    )   ALU_rf_data1_mux (
        .din1           (rf_rdata1_ex),//0
        .din2           (forward1_data),//1
        .sel            (forward1_en),
        .dout           (alu_rf_data1)
    );
    Mux2_1 # (
        .WIDTH(32)
    )   ALU_rf_data2_mux (
        .din1           (rf_rdata2_ex),//0
        .din2           (forward2_data),//1
        .sel            (forward2_en),
        .dout           (alu_rf_data2)
    );
    Mux4_1 # (
        .WIDTH(32)
    )   ALU_rs1_mux (
        .din1           (alu_rf_data1),
        .din2           (pc_ex),
        .din3           (32'h0),
        .din4           (32'h0),
        .sel            (alu_rs1_sel_ex),
        .dout           (alu_rs1)
    );
    Mux4_1 # (
        .WIDTH(32)
    )   ALU_rs2_mux (
        .din1           (alu_rf_data2),
        .din2           (imm_ex),
        .din3           (32'h4),
        .din4           (csr_rdata_ex),
        .sel            (alu_rs2_sel_ex),
        .dout           (alu_rs2)
    );

    ALU  ALU_inst (
        .sr1            (alu_rs1),
        .sr2            (alu_rs2),
        .alu_op         (alu_op_ex),
        .result         (alu_result_ex)
    );

    Priv  Priv_inst (
        .csr_op         (inst_ex[14:12]),
        .csr_rdata      (csr_rdata_ex),
        .rf_rdata1      (alu_rf_data1),
        .zimm           ({27'b0, inst_ex[19:15]}),
        .csr_wdata      (csr_wdata_ex)
    );

    Branch  Branch_inst (
        .br_type        (br_type_ex),
        .sr1            (alu_rf_data1),
        .sr2            (alu_rf_data2),
        .pc             (pc_ex),
        .imm            (imm_ex),
        .jump           (jump),
        .jump_target    (jump_target)
    );



    logic [31:0] mem_wdata_ls1;
    /* EX-LS1 segreg */
    SegReg_EX_LS1 # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_EX_LS1_inst (
        .clk            (cpu_clk),
        .rst            (cpu_rst),
        .flush          (EX_LS1_flush),
        .pc_ex          (pc_ex),
        .inst_ex        (inst_ex),
        .alu_result_ex  (alu_result_ex),
        .mem_access_ex  (mem_access_ex),
        .wb_rf_sel_ex   (wb_rf_sel_ex),
        .rf_we_ex       (rf_we_ex),
        .mem_wdata_ex   (alu_rf_data2),
        .mem_wdata_ls1  (mem_wdata_ls1),
        .pc_ls1         (pc_ls1),
        .inst_ls1       (inst_ls1),
        .alu_result_ls1 (alu_result_ls1),
        .mem_access_ls1 (mem_access_ls1),
        .wb_rf_sel_ls1  (wb_rf_sel_ls1),
        .rf_we_ls1      (rf_we_ls1),
        .csr_wdata_ex    (csr_wdata_ex),
        .csr_wdata_ls1    (csr_wdata_ls1),
        .priv_vec_ex      (priv_vec_ex),
        .priv_vec_ls1      (priv_vec_ls1),
        .have_inst_ex   (have_inst_ex),
        .have_inst_ls1  (have_inst_ls1)
    );

    logic [31:0] d_wdata;
    logic [3:0] d_wstrb;

    /* LS1 stage */
     Write_Ctrl  Write_Ctrl_inst (
        .mem_wdata      (mem_wdata_ls1),
        .alu_result     (alu_result_ls1[1:0]),
        .mem_access     (mem_access_ls1),
        .wdata          (d_wdata),
        .d_wstrb        (d_wstrb)
    );

    assign bus_addr = alu_result_ls1;
    assign bus_wdata = d_wdata;
    assign bus_wen = d_wstrb;

    /* LS1-LS2 segreg */
    SegReg_LS1_LS2 # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_LS1_LS2_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .flush              (LS1_LS2_flush),
        .pc_ls1             (pc_ls1),
        .inst_ls1           (inst_ls1),
        .alu_result_ls1     (alu_result_ls1),
        .mem_access_ls1     (mem_access_ls1),
        .wb_rf_sel_ls1      (wb_rf_sel_ls1),
        .rf_we_ls1          (rf_we_ls1),
        .pc_ls2             (pc_ls2),
        .inst_ls2           (inst_ls2),
        .alu_result_ls2     (alu_result_ls2),
        .mem_access_ls2     (mem_access_ls2),
        .wb_rf_sel_ls2      (wb_rf_sel_ls2),
        .rf_we_ls2          (rf_we_ls2),
        .csr_wdata_ls1      (csr_wdata_ls1),
        .csr_wdata_ls2      (csr_wdata_ls2),
        .priv_vec_ls1      (priv_vec_ls1),
        .priv_vec_ls2      (priv_vec_ls2),
        .have_inst_ls1      (have_inst_ls1),
        .have_inst_ls2      (have_inst_ls2)
    );

    /* LS2 stage */
    logic [31:0] d_rdata_ls2;
    assign d_rdata_ls2 = bus_rdata;
    Read_Ctrl  Read_Ctrl_inst (
        .mem_rdata      (d_rdata_ls2),
        .mem_raddr      (alu_result_ls2[1:0]),
        .mem_access     (mem_access_ls2),
        .rdata          (mem_rdata_ls2)
    );

    SegReg_LS2_WB # (
        .PC_RESET_VAL(PC_RESET_VALUE)
    ) SegReg_LS2_WB_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .flush              (LS2_WB_flush),
        .pc_ls2             (pc_ls2),
        .inst_ls2           (inst_ls2),
        .alu_result_ls2     (alu_result_ls2),
        .mem_access_ls2     (mem_access_ls2),
        .mem_rdata_ls2      (mem_rdata_ls2),
        .wb_rf_sel_ls2      (wb_rf_sel_ls2),
        .rf_we_ls2          (rf_we_ls2),
        .mem_rdata_wb       (mem_rdata_wb),
        .pc_wb              (pc_wb),
        .inst_wb            (inst_wb),
        .alu_result_wb      (alu_result_wb),
        .mem_access_wb      (mem_access_wb),
        .wb_rf_sel_wb       (wb_rf_sel_wb),
        .rf_we_wb           (rf_we_wb),
        .csr_wdata_ls2      (csr_wdata_ls2),
        .csr_wdata_wb      (csr_wdata_wb),
        .priv_vec_ls2      (priv_vec_ls2),
        .priv_vec_wb      (priv_vec_wb),
        .have_inst_ls2      (have_inst_ls2),
        .have_inst_wb       (have_inst_wb)
    );
    /* WB stage */

    Mux2_1 # (
        .WIDTH(32)
    )   WB_rf_wdata_mux (
        .din1           (alu_result_wb),//0
        .din2           (mem_rdata_wb),//1
        .sel            (wb_rf_sel_wb),
        .dout           (rf_wdata_wb)
    );

    Exp_Commit  Exp_Commit_inst (
        .priv_vec(priv_vec_wb),
        .exp_code(mcause_global)
    );

    /* Hazard */
    Hazard  Hazard_inst (
        .clk                (cpu_clk),
        .rst                (cpu_rst),
        .rf_rd_ls1           (inst_ls1[11:7]),
        .rf_rd_ls2           (inst_ls2[11:7]),
        .rf_rd_wb           (inst_wb[11:7]),
        .rf_we_ls1           (rf_we_ls1),
        .rf_we_ls2           (rf_we_ls2),
        .rf_we_wb            (rf_we_wb),
        .rf_rs1_ex          (inst_ex[19:15]),
        .rf_rs2_ex          (inst_ex[24:20]),
        .rf_wdata_ls1       (alu_result_ls1),
        .rf_wdata_ls2       (alu_result_ls2),
        .rf_wdata_wb        (rf_wdata_wb),
        .forward1_en        (forward1_en),
        .forward2_en        (forward2_en),
        .forward1_data      (forward1_data),
        .forward2_data      (forward2_data),

        .mem_access_ex      (mem_access_ex),
        .rf_rd_ex           (inst_ex[11:7]),
        .rf_rs1_if2         (inst_if2[19:15]),
        .rf_rs2_if2         (inst_if2[24:20]),
        .rf_rs1_id          (inst_id[19:15]),
        .rf_rs2_id          (inst_id[24:20]),
        .jump               (jump),
        .jump_target        (jump_target),
        .priv_vec_ex        (priv_vec_ex),
        .pc_ex              (pc_ex),
        .priv_vec_wb        (priv_vec_wb),
        .pc_wb              (pc_wb),
        .mepc_global        (mepc_global),
        .mtvec_global       (mtvec_global),
        .mcause_global      (mcause_global),

        .predict_taken_if1  (predict_taken_if1),
        .predict_taken_ex   (predict_taken_ex),
        .predict_target_ex  (pc_to_take_ex),
        .pc_set             (pc_set),
        .IF1_IF2_flush      (IF1_IF2_flush),
        .IF2_ID_flush       (IF2_ID_flush),
        .ID_EX_flush        (ID_EX_flush),
        .EX_LS1_flush       (EX_LS1_flush),
        .LS1_LS2_flush      (LS1_LS2_flush),
        .LS2_WB_flush       (LS2_WB_flush),
        .pc_stall           (pc_stall),
        .IF1_IF2_stall      (IF1_IF2_stall),
        .IF2_ID_stall       (IF2_ID_stall),
        .ID_EX_stall        (ID_EX_stall),
        .pc_set_target      (pc_target)
    );
    
    assign debug_wb_have_inst = have_inst_wb; 
    assign debug_wb_pc        = pc_wb;    
    assign debug_wb_ena       = rf_we_wb;
    assign debug_wb_reg       = inst_wb[11:7];
    assign debug_wb_value     = rf_wdata_wb;
endmodule