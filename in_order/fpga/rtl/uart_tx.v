// UART transmitter, 8N1
module uart_tx #(
    parameter CLK_FREQ = 50_000_000,
    parameter BAUD     = 115200
) (
    input  wire       clk,
    input  wire       rst,
    input  wire       start,
    input  wire [7:0] data,
    output reg        txd,
    output wire       busy
);
    localparam DIV = CLK_FREQ / BAUD;

    reg [15:0] baud_cnt;
    reg [3:0]  bit_cnt;   // 0 idle, 1..10 = start,8 data,stop
    reg [9:0]  shifter;

    assign busy = (bit_cnt != 4'd0);

    always @(posedge clk) begin
        if (rst) begin
            txd      <= 1'b1;
            bit_cnt  <= 4'd0;
            baud_cnt <= 16'd0;
            shifter  <= 10'h3FF;
        end else if (bit_cnt == 4'd0) begin
            txd <= 1'b1;
            if (start) begin
                shifter  <= {1'b1, data, 1'b0}; // stop, data[7:0], start
                bit_cnt  <= 4'd10;
                baud_cnt <= 16'd0;
            end
        end else begin
            if (baud_cnt == DIV[15:0] - 1'b1) begin
                baud_cnt <= 16'd0;
                bit_cnt  <= bit_cnt - 1'b1;
                shifter  <= {1'b1, shifter[9:1]};
            end else begin
                baud_cnt <= baud_cnt + 1'b1;
            end
            txd <= shifter[0];
        end
    end
endmodule
