`include "config.sv"

module tb_muldiv_latency;
    logic        clk = 1'b0;
    logic        rst;
    logic        valid;
    logic        start;
    logic [2:0]  op;
    logic [31:0] a;
    logic [31:0] b;
    logic        busy;
    logic        done;
    logic [31:0] result;

    always #5 clk = ~clk;

    MulDiv dut (
        .clk    (clk),
        .rst    (rst),
        .valid  (valid),
        .start  (start),
        .op     (op),
        .a      (a),
        .b      (b),
        .busy   (busy),
        .done   (done),
        .result (result)
    );

    task automatic step;
        @(posedge clk);
        #1;
    endtask

    initial begin
        rst   = 1'b1;
        valid = 1'b0;
        start = 1'b0;
        op    = `MUL;
        a     = 32'd0;
        b     = 32'd0;

        repeat (2) step();
        rst = 1'b0;
        step();

        valid = 1'b1;
        start = 1'b1;
        op    = `MUL;
        a     = 32'd7;
        b     = 32'd9;
        step();

        start = 1'b0;
        a     = 32'd1234;
        b     = 32'd5678;
        step();
        if (done) begin
            $fatal(1, "MUL done asserted before the registered operand pipeline stage completed");
        end

        step();
        if (!done || result != 32'd63) begin
            $fatal(1, "MUL result mismatch or missing done: done=%0b result=%0d", done, result);
        end

        step();
        if (done) begin
            $fatal(1, "MUL done should be a one-cycle pulse");
        end

        $finish;
    end
endmodule
