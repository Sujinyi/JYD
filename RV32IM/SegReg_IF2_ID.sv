module SegReg_IF2_ID#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] stall,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_if2,
    input  logic [31:0] inst_if2,
    input  logic [ 0:0] predict_taken_if2,
    input  logic [31:0] predict_target_if2,
    output logic [31:0] pc_id,
    output logic [31:0] inst_id,
    output logic [ 0:0] predict_taken_id,
    output logic [31:0] predict_target_id
);
    always_ff @(posedge clk) begin
        if(rst || flush) begin
            pc_id            <= PC_RESET_VAL;
            inst_id          <= 32'h0;
            predict_taken_id <= 1'b0;
            predict_target_id<= 32'h0;
        end 
        else if(!stall) begin
            pc_id            <= pc_if2;
            inst_id          <= inst_if2;
            predict_taken_id <= predict_taken_if2;
            predict_target_id<= predict_target_if2;
        end
    end

endmodule