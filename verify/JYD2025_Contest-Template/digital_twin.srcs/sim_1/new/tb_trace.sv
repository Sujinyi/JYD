`timescale 1ns / 100ps
`define TRACE_REF_FILE "../../../my_trace.txt"

module tb_trace;
    reg clk;

    top uut (
        .i_sys_clk_p(clk),
        .i_sys_clk_n(~clk),
        .i_uart_rx(1'b1),
        .o_uart_tx(),
        .virtual_led(),  
        .virtual_seg()
    );

    //  clock 50MHz=2.5 20ns
    initial begin
        clk = 0;
        forever #2.5 clk = ~clk;
    end

wire [31:0] debug_wb_pc;
wire [0 :0] debug_wb_rf_wen;
wire [4 :0] debug_wb_rf_wnum;
wire [31:0] debug_wb_rf_wdata;

assign debug_wb_pc = uut.student_top_inst.Core_cpu.debug_wb_pc;
assign debug_wb_rf_wen = uut.student_top_inst.Core_cpu.debug_wb_rf_wen;
assign debug_wb_rf_wnum = uut.student_top_inst.Core_cpu.debug_wb_rf_wnum;
assign debug_wb_rf_wdata = uut.student_top_inst.Core_cpu.debug_wb_rf_wdata;


// open the trace file;
integer trace_ref;
initial begin
    trace_ref = $fopen(`TRACE_REF_FILE, "w");
    if (!trace_ref) begin
            $display("Failed to open debug_wb_log.txt!");
            $finish;
    end
end

// 每个时钟上升沿记录 WB 阶段的信息
always_ff @(posedge clk) begin
        // 只在写使能有效时记录
        if (debug_wb_rf_wen && debug_wb_rf_wnum!=5'd0) begin
            $fwrite(trace_ref, "PC: %08x, WEN: %b, WNUM: %02d, WDATA: %08x\n",
                    debug_wb_pc, debug_wb_rf_wen, debug_wb_rf_wnum, debug_wb_rf_wdata);
        end
        // 检测到测评结束 (PC=0x80000010对应 j 0 自身的终点死循环指令)
        if (debug_wb_pc == 32'h80000010) begin
            $display("Hit termination condition: PC == 80000010");
            $fclose(trace_ref);
            $finish;
        end
    end

    // 仿真时间限制与结束(备用超时机制)
    initial begin
        #150000; // 仿真最大时长（或用 `wait` 等待某条件）
        $display("Simulation Timeout");
        $fclose(trace_ref);
        $finish;
    end

endmodule
