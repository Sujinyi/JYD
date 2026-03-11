module SegReg_ID_EX#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_id,
    input  logic [31:0] inst_id,
    input  logic [31:0] rdata1_id,
    input  logic [31:0] rdata2_id,
    input  logic [31:0] imm_id,
    input  logic [ 4:0] mem_access_id,
    input  logic [ 4:0] alu_op_id,
    input  logic [ 4:0] br_type_id,
    input  logic [ 0:0] wb_rf_sel_id,
    input  logic [ 1:0] alu_rs1_sel_id,
    input  logic [ 1:0] alu_rs2_sel_id,
    input  logic [ 0:0] rf_we_id,
    input  logic [ 0:0] have_inst_id,
    input  logic [ 0:0] branch_taken_id,

    output logic [ 0:0] branch_taken_ex,
    output logic [31:0] pc_ex,
    output logic [31:0] inst_ex,
    output logic [31:0] rdata1_ex,
    output logic [31:0] rdata2_ex,
    output logic [31:0] imm_ex,
    output logic [ 4:0] mem_access_ex,
    output logic [ 4:0] alu_op_ex,
    output logic [ 4:0] br_type_ex,
    output logic [ 0:0] wb_rf_sel_ex,
    output logic [ 1:0] alu_rs1_sel_ex,
    output logic [ 1:0] alu_rs2_sel_ex,
    output logic [ 0:0] rf_we_ex,
    output logic [ 0:0] have_inst_ex
);
    always_ff @(posedge clk) begin
        if(rst || flush) begin
            branch_taken_ex <= 1'b0;
            pc_ex           <= PC_RESET_VAL;
            inst_ex         <= 32'h0;
            rdata1_ex       <= 32'h0;
            rdata2_ex       <= 32'h0;
            imm_ex          <= 32'h0;
            mem_access_ex   <=  5'h0;
            alu_op_ex       <=  5'h0;
            br_type_ex      <=  5'h0;
            wb_rf_sel_ex    <=  1'h0;
            alu_rs1_sel_ex  <=  2'h0;
            alu_rs2_sel_ex  <=  2'h0;
            rf_we_ex        <=  1'h0;
            have_inst_ex    <=  1'h0;
        end 
        else begin
            branch_taken_ex <= branch_taken_id;
            pc_ex           <= pc_id;
            inst_ex         <= inst_id;
            rdata1_ex       <= rdata1_id;
            rdata2_ex       <= rdata2_id;
            imm_ex          <= imm_id;
            mem_access_ex   <= mem_access_id;
            alu_op_ex       <= alu_op_id;
            br_type_ex      <= br_type_id;
            wb_rf_sel_ex    <= wb_rf_sel_id;
            alu_rs1_sel_ex  <= alu_rs1_sel_id;
            alu_rs2_sel_ex  <= alu_rs2_sel_id;
            rf_we_ex        <= rf_we_id;
            have_inst_ex    <= have_inst_id;
        end
    end

endmodule