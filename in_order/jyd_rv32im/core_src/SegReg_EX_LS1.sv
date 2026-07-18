module SegReg_EX_LS1#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_ex,
    input  logic [31:0] inst_ex,
    input  logic [31:0] alu_result_ex,
    input  logic [ 4:0] mem_access_ex,
    input  logic [ 0:0] wb_rf_sel_ex,
    input  logic [ 0:0] rf_we_ex,
    input  logic [ 0:0] have_inst_ex,
    input  logic [31:0] mem_wdata_ex,
    input  logic [31:0] csr_wdata_ex,
    input  logic [ 2:0] priv_vec_ex,

    output logic [31:0] csr_wdata_ls1,
    output logic [ 2:0] priv_vec_ls1,
    output logic [31:0] mem_wdata_ls1,
    output logic [31:0] pc_ls1,
    output logic [31:0] inst_ls1,
    output logic [31:0] alu_result_ls1,
    output logic [ 4:0] mem_access_ls1,
    output logic [ 0:0] wb_rf_sel_ls1,
    output logic [ 0:0] rf_we_ls1,
    output logic [ 0:0] have_inst_ls1
);
    always_ff @(posedge clk) begin
        if(rst) begin
            pc_ls1           <= PC_RESET_VAL;
            inst_ls1         <= 32'h0;
            alu_result_ls1   <= 32'h0;
            mem_access_ls1   <=  5'h0;
            wb_rf_sel_ls1    <=  1'h0;
            rf_we_ls1        <=  1'h0;
            have_inst_ls1    <=  1'h0;
            mem_wdata_ls1    <= 32'h0;
            csr_wdata_ls1    <= 32'h0;
            priv_vec_ls1     <=  3'h0;
        end
        else if(flush) begin
            have_inst_ls1    <=  1'h0;
        end 
        else begin
            pc_ls1           <= pc_ex;
            inst_ls1         <= inst_ex;
            alu_result_ls1   <= alu_result_ex;
            mem_access_ls1   <= mem_access_ex;
            wb_rf_sel_ls1    <= wb_rf_sel_ex;
            rf_we_ls1        <= rf_we_ex;
            have_inst_ls1    <= have_inst_ex;
            mem_wdata_ls1    <= mem_wdata_ex;
            csr_wdata_ls1    <= csr_wdata_ex;
            priv_vec_ls1     <= priv_vec_ex;
        end
    end
endmodule
