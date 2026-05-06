module PC#(
    parameter RESET_VALUE = 0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] stall,
    input  logic [31:0] next_pc,
    output logic [31:0] pc 
);
    always_ff @(posedge clk) begin
        if(rst) begin
            pc <= RESET_VALUE;
        end 
        else if(!stall) begin
            pc <= next_pc;
        end
    end
endmodule