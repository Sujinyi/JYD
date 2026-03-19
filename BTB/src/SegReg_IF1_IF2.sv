module SegReg_IF1_IF2#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] stall,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_if1,
    input  logic [ 0:0] predict_taken_if1,
    input  logic [31:0] predict_target_if1,
    output logic [31:0] pc_if2,
    output logic [ 0:0] predict_taken_if2,
    output logic [31:0] predict_target_if2
);
    always_ff @(posedge clk) begin
        if(rst || flush) begin
            pc_if2              <= PC_RESET_VAL;
            predict_taken_if2   <= 1'b0;
            predict_target_if2  <= 32'h0;
        end 
        else if(!stall) begin
            pc_if2              <= pc_if1;
            predict_taken_if2   <= predict_taken_if1;
            predict_target_if2  <= predict_target_if1;
        end
    end

endmodule