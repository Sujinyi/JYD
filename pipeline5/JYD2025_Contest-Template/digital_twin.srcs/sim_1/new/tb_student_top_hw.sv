`timescale 1ns / 1ps

module tb_student_top_hw;

    // 1. Clock and Reset Generation
    logic clk_50Mhz;
    logic cpu_clk;
    logic rst;

    initial begin
        clk_50Mhz = 0;
        forever #10 clk_50Mhz = ~clk_50Mhz; // 50MHz: 20ns period
    end

    // Use the same clock for cpu_clk in simulation 
    assign cpu_clk = clk_50Mhz;

    initial begin
        rst = 1;      // Assert reset
        #100;
        rst = 0;      // De-assert reset
    end

    // 2. Virtual Inputs
    logic [7:0]  virtual_key = 8'd0;
    logic [63:0] virtual_sw  = 64'd0;

    // 3. Virtual Outputs
    logic [31:0] virtual_led;
    logic [39:0] virtual_seg;

    // 4. Instantiate Top-Level Module (student_top)
    student_top dut (
        .w_cpu_clk      (cpu_clk),
        .w_clk_50Mhz    (clk_50Mhz),
        .w_clk_rst      (rst),
        .virtual_key    (virtual_key),
        .virtual_sw     (virtual_sw),
        .virtual_led    (virtual_led),
        .virtual_seg    (virtual_seg)
    );

    // 5. Monitor Output (Optional but helpful)
    reg [39:0] prev_seg;
    always_ff @(posedge cpu_clk) begin
        if (!rst) begin
            if (virtual_seg !== prev_seg) begin
                $display("[%0t] SEG DISPLAY UPDATED: 0x%010x", $time, virtual_seg);
                prev_seg <= virtual_seg;
            end
        end
    end

    // Timeout mechanism to prevent infinite loop
    initial begin
        #1000000000; // 5ms maximum simulation time
        $display("[%0t] ERROR: Simulation Timeout!", $time);
        $finish;
    end

endmodule
