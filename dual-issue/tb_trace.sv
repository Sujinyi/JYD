`timescale 1ns / 100ps
`define TRACE_REF_FILE "../../../my_trace.txt"

module tb_trace;
    localparam bit          ENABLE_END_PC_STOP = 1'b1;
    localparam logic [31:0] END_PC0 = 32'h8000_0010;
    localparam logic [31:0] END_PC1 = 32'h0000_0010;

    reg clk;

    top uut (
        .i_sys_clk_p(clk),
        .i_sys_clk_n(~clk),
        .i_uart_rx(1'b1),
        .o_uart_tx(),
        .virtual_led(),
        .virtual_seg()
    );

    initial begin
        clk = 1'b0;
        forever #2.5 clk = ~clk;
    end

    wire        debug0_have_inst;
    wire [31:0] debug0_pc;
    wire        debug0_wen;
    wire [4:0]  debug0_wnum;
    wire [31:0] debug0_wdata;

    wire        debug1_have_inst;
    wire [31:0] debug1_pc;
    wire        debug1_wen;
    wire [4:0]  debug1_wnum;
    wire [31:0] debug1_wdata;

    assign debug0_have_inst = uut.student_top_inst.RISCV_Core.debug_wb_have_inst;
    assign debug0_pc = uut.student_top_inst.RISCV_Core.debug_wb_pc;
    assign debug0_wen = uut.student_top_inst.RISCV_Core.debug_wb_ena;
    assign debug0_wnum = uut.student_top_inst.RISCV_Core.debug_wb_reg;
    assign debug0_wdata = uut.student_top_inst.RISCV_Core.debug_wb_value;

    assign debug1_have_inst = uut.student_top_inst.RISCV_Core.debug_wb_have_inst_1;
    assign debug1_pc = uut.student_top_inst.RISCV_Core.debug_wb_pc_1;
    assign debug1_wen = uut.student_top_inst.RISCV_Core.debug_wb_ena_1;
    assign debug1_wnum = uut.student_top_inst.RISCV_Core.debug_wb_reg_1;
    assign debug1_wdata = uut.student_top_inst.RISCV_Core.debug_wb_value_1;

    integer trace_ref;
    integer trace_line_count;
    integer trace_dbg;

    task automatic write_trace(
        input logic        have_inst,
        input logic [31:0] pc,
        input logic        wen,
        input logic [4:0]  wnum,
        input logic [31:0] wdata
    );
        if (have_inst && wen && (wnum != 5'd0)) begin
            trace_line_count = trace_line_count + 1;
            $fwrite(
                trace_ref,
                "PC: %08x, WEN: %b, WNUM: %02d, WDATA: %08x\n",
                pc,
                wen,
                wnum,
                wdata
            );
        end
    endtask

    function automatic logic is_end_pc(input logic [31:0] pc);
        is_end_pc = (pc == END_PC0) || (pc == END_PC1);
    endfunction

    initial begin
        trace_line_count = 0;
        trace_ref = $fopen(`TRACE_REF_FILE, "w");
        trace_dbg = $fopen("trace_debug_window.txt", "w");
        if (!trace_ref) begin
            $display("Failed to open my_trace.txt!");
            $finish;
        end
    end

    function automatic logic in_debug_window(input logic [31:0] pc);
        in_debug_window =
            ((pc >= 32'h8000_0540) && (pc <= 32'h8000_05b0)) ||
            ((pc >= 32'h8000_05b0) && (pc <= 32'h8000_0760));
    endfunction

    task automatic dump_debug_window(input string edge_name);
        if (
            in_debug_window(debug0_pc) ||
            in_debug_window(debug1_pc) ||
            in_debug_window(uut.student_top_inst.RISCV_Core.op0_pc) ||
            in_debug_window(uut.student_top_inst.RISCV_Core.op1_pc) ||
            in_debug_window(uut.student_top_inst.RISCV_Core.slot0_pc_q) ||
            in_debug_window(uut.student_top_inst.RISCV_Core.slot1_pc_q)
        ) begin
            $fwrite(
                trace_dbg,
                "%0t %s dbg0(h=%0b pc=%08x we=%0b rd=%02d val=%08x) dbg1(h=%0b pc=%08x we=%0b rd=%02d val=%08x) front(f0v=%0b f0pc=%08x f0inst=%08x f1v=%0b f1pc=%08x f1inst=%08x) slot0(exec=%0b lsu=%0b pc=%08x) slot1(exec=%0b pc=%08x) op0(v=%0b pc=%08x inst=%08x) op1(v=%0b pc=%08x inst=%08x) br(req=%0b target=%08x) f(acc0=%0b acc1=%0b)\n",
                $time,
                edge_name,
                debug0_have_inst,
                debug0_pc,
                debug0_wen,
                debug0_wnum,
                debug0_wdata,
                debug1_have_inst,
                debug1_pc,
                debug1_wen,
                debug1_wnum,
                debug1_wdata,
                uut.student_top_inst.RISCV_Core.f0_valid,
                uut.student_top_inst.RISCV_Core.f0_pc,
                uut.student_top_inst.RISCV_Core.f0_inst,
                uut.student_top_inst.RISCV_Core.f1_valid,
                uut.student_top_inst.RISCV_Core.f1_pc,
                uut.student_top_inst.RISCV_Core.f1_inst,
                uut.student_top_inst.RISCV_Core.slot0_exec_q,
                uut.student_top_inst.RISCV_Core.slot0_lsu_q,
                uut.student_top_inst.RISCV_Core.slot0_pc_q,
                uut.student_top_inst.RISCV_Core.slot1_exec_q,
                uut.student_top_inst.RISCV_Core.slot1_pc_q,
                uut.student_top_inst.RISCV_Core.ex0_valid,
                uut.student_top_inst.RISCV_Core.op0_pc,
                uut.student_top_inst.RISCV_Core.op0_inst,
                uut.student_top_inst.RISCV_Core.ex1_valid,
                uut.student_top_inst.RISCV_Core.op1_pc,
                uut.student_top_inst.RISCV_Core.op1_inst,
                uut.student_top_inst.RISCV_Core.br_req,
                uut.student_top_inst.RISCV_Core.br_target,
                uut.student_top_inst.RISCV_Core.f0_accept,
                uut.student_top_inst.RISCV_Core.f1_accept
            );
        end
    endtask

    always @(posedge uut.cpu_clk) begin
        if (uut.w_clk_rst) begin
            dump_debug_window("pos");
        end
    end

    always @(negedge uut.cpu_clk) begin
        if (!uut.w_clk_rst) begin
            // Wait until PLL is locked and the CPU reset is released.
        end else begin
            dump_debug_window("neg");
            // slot0 is always older than slot1, so keep this order in the trace.
            write_trace(debug0_have_inst, debug0_pc, debug0_wen, debug0_wnum, debug0_wdata);
            write_trace(debug1_have_inst, debug1_pc, debug1_wen, debug1_wnum, debug1_wdata);

            if (ENABLE_END_PC_STOP &&
                ((debug0_have_inst && is_end_pc(debug0_pc)) ||
                 (debug1_have_inst && is_end_pc(debug1_pc)))) begin
                $display("Hit termination condition: PC == %08x or %08x", END_PC0, END_PC1);
                $display("Trace lines written: %0d", trace_line_count);
                $fclose(trace_ref);
                $fclose(trace_dbg);
                $finish;
            end
        end
    end

    initial begin
        #500000000;
        $display("Simulation Timeout");
        $display("Trace lines written: %0d", trace_line_count);
        $fclose(trace_ref);
        $fclose(trace_dbg);
        $finish;
    end

endmodule
