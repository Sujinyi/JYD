`timescale 1ps/1ps

module tb_xsim;
    localparam logic [31:0] SEG_ADDR = 32'h8020_0020;
    localparam logic [31:0] LED_ADDR = 32'h8020_0040;
    localparam logic [31:0] CNT_ADDR = 32'h8020_0050;

    logic        w_cpu_clk   = 1'b0;
    logic        w_clk_50Mhz = 1'b0;
    logic        w_clk_rst   = 1'b1;
    logic [7:0]  virtual_key = 8'h00;
    logic [63:0] virtual_sw  = 64'h0;
    wire  [31:0] virtual_led;
    wire  [39:0] virtual_seg;

    // Current PLL setting is 220 MHz. 4546 ps is close enough for RTL
    // functional simulation; there are no cell delays in this simulation.
    always #2273  w_cpu_clk   = ~w_cpu_clk;
    always #10000 w_clk_50Mhz = ~w_clk_50Mhz;

    student_top dut (
        .w_cpu_clk    (w_cpu_clk),
        .w_clk_50Mhz  (w_clk_50Mhz),
        .w_clk_rst    (w_clk_rst),
        .virtual_key  (virtual_key),
        .virtual_sw   (virtual_sw),
        .virtual_led  (virtual_led),
        .virtual_seg  (virtual_seg)
    );

    longint unsigned cycles = 0;
    longint unsigned max_cycles = 5_000_000;
    logic [31:0] last_pc  = 32'h0;
    logic [31:0] last_seg = 32'h0;
    logic [31:0] last_led = 32'h0;
    int unsigned same_pc_cycles = 0;
    bit cnt_start_seen = 0;
    bit cnt_stop_seen  = 0;
    bit seg_pass_seen  = 0;
    bit pc_oob_seen    = 0;
    bit x_seen         = 0;

    initial begin
        void'($value$plusargs("MAX_CYCLES=%d", max_cycles));

        repeat (40) @(posedge w_cpu_clk);
        @(negedge w_cpu_clk);
        w_clk_rst = 1'b0;
        $display("XSIM_INFO: reset released; MAX_CYCLES=%0d", max_cycles);

        forever begin
            @(negedge w_cpu_clk);
            cycles++;

            if (cycles <= 100)
                $display("XSIM_TRACE: c=%0d pc_f=%08x imem_addr=%08x i0=%08x i1=%08x qcnt=%0d q0pc=%08x q0=%08x pop=%0d iss=%0d/%0d hz0=%0d mstall=%0d redir=%0d idr=%0d/%0d e0v=%0d div=%0d md=%0d/%0d",
                         cycles, dut.u_core.pc_f, dut.imem_addr,
                         dut.imem_rdata0, dut.imem_rdata1,
                         dut.u_core.q_cnt, dut.u_core.pc_0, dut.u_core.in_0,
                         dut.u_core.pops, dut.u_core.issue0, dut.u_core.issue1,
                         dut.u_core.hz0, dut.u_core.mstall, dut.u_core.redirect,
                         dut.u_core.id_redirect, dut.u_core.idr_r,
                         dut.u_core.valid_e0, dut.u_core.is_div_e0,
                         dut.u_core.md_start, dut.u_core.md_done);
            if ((cycles >= 20) && (cycles <= 35))
                $display("XSIM_HAZ: c=%0d rs=%0d/%0d use=%0d/%0d ld_e=%0d:r%0d ld_m=%0d:r%0d ld_e1=%0d:r%0d ld_m1=%0d:r%0d vm=%0d/%0d vx=%0d/%0d vw=%0d/%0d wb=%0d:r%0d:%08x",
                         cycles, dut.u_core.rs1_0, dut.u_core.rs2_0,
                         dut.u_core.uses_rs1_0, dut.u_core.uses_rs2_0,
                         dut.u_core.ld_e_v, dut.u_core.ld_e_rd,
                         dut.u_core.ld_m_v, dut.u_core.ld_m_rd,
                         dut.u_core.ld_e1_v, dut.u_core.ld_e1_rd,
                         dut.u_core.ld_m1_v, dut.u_core.ld_m1_rd,
                         dut.u_core.valid_m0, dut.u_core.valid_m1,
                         dut.u_core.valid_x0, dut.u_core.valid_x1,
                         dut.u_core.valid_w0, dut.u_core.valid_w1,
                         dut.u_core.wb_wen0, dut.u_core.wb_rd0,
                         dut.u_core.wb_wdata0);

            if ($isunknown(dut.imem_addr) ||
                $isunknown(dut.imem_rdata0) ||
                $isunknown(dut.dmem_addr) ||
                $isunknown(dut.dmem_wen)) begin
                if (!x_seen)
                    $display("XSIM_X: cycle=%0d pc=%08x imem=%08x/%08x daddr=%08x wen=%x",
                             cycles, dut.u_core.pc_f, dut.imem_addr,
                             dut.imem_rdata0, dut.dmem_addr, dut.dmem_wen);
                x_seen = 1'b1;
            end

            if ((dut.u_core.pc_f[31:14] != 18'h20000) && !pc_oob_seen) begin
                pc_oob_seen = 1'b1;
                $display("XSIM_PC_OOB: cycle=%0d pc=%08x", cycles, dut.u_core.pc_f);
            end

            if (dut.u_core.pc_f == last_pc)
                same_pc_cycles++;
            else begin
                same_pc_cycles = 0;
                last_pc = dut.u_core.pc_f;
            end

            if (|dut.dmem_wen) begin
                case (dut.dmem_addr)
                    CNT_ADDR: begin
                        $display("XSIM_CNT_WRITE: cycle=%0d data=%08x", cycles, dut.dmem_wdata);
                        if (dut.dmem_wdata == 32'h8000_0000) cnt_start_seen = 1'b1;
                        if (dut.dmem_wdata == 32'hffff_ffff) cnt_stop_seen  = 1'b1;
                    end
                    SEG_ADDR: begin
                        last_seg = dut.dmem_wdata;
                        $display("XSIM_SEG_WRITE: cycle=%0d data=%08x", cycles, dut.dmem_wdata);
                        if ((dut.dmem_wdata & 32'hfff0_0000) == 32'h3780_0000)
                            seg_pass_seen = 1'b1;
                    end
                    LED_ADDR: begin
                        last_led = dut.dmem_wdata;
                        $display("XSIM_LED_WRITE: cycle=%0d data=%08x", cycles, dut.dmem_wdata);
                    end
                    default: begin
                        if (dut.dmem_addr[31:8] == 24'h802000)
                            $display("XSIM_MMIO_WRITE: cycle=%0d addr=%08x data=%08x wen=%x",
                                     cycles, dut.dmem_addr, dut.dmem_wdata, dut.dmem_wen);
                    end
                endcase
            end

            if (seg_pass_seen) begin
                repeat (20) @(negedge w_cpu_clk);
                $display("XSIM_RESULT: PASS cycles=%0d seg=%08x led=%08x cnt_start=%0d cnt_stop=%0d pc=%08x x_seen=%0d pc_oob=%0d",
                         cycles, last_seg, last_led, cnt_start_seen, cnt_stop_seen,
                         dut.u_core.pc_f, x_seen, pc_oob_seen);
                $finish;
            end

            if ((cycles % 1_000_000) == 0)
                $display("XSIM_PROGRESS: cycle=%0d pc=%08x same_pc=%0d seg=%08x led=%08x cnt_start=%0d cnt_stop=%0d",
                         cycles, dut.u_core.pc_f, same_pc_cycles, last_seg,
                         last_led, cnt_start_seen, cnt_stop_seen);

            if (cycles >= max_cycles) begin
                $display("XSIM_RESULT: TIMEOUT cycles=%0d seg=%08x led=%08x cnt_start=%0d cnt_stop=%0d pc=%08x same_pc=%0d x_seen=%0d pc_oob=%0d",
                         cycles, last_seg, last_led, cnt_start_seen, cnt_stop_seen,
                         dut.u_core.pc_f, same_pc_cycles, x_seen, pc_oob_seen);
                $finish;
            end
        end
    end
endmodule
