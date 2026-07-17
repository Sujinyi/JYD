module SegReg_LS1_LS2#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_ls1,
    input  logic [31:0] inst_ls1,
    input  logic [31:0] alu_result_ls1,
    input  logic [4:0] mem_access_ls1,
    input  logic [ 0:0] wb_rf_sel_ls1,
    input  logic [ 0:0] rf_we_ls1,
    input  logic [ 0:0] have_inst_ls1,
    input  logic [31:0] csr_wdata_ls1,
    input  logic [ 2:0] priv_vec_ls1,

    output logic [31:0] csr_wdata_ls2,
    output logic [ 2:0] priv_vec_ls2,
    output logic [31:0] pc_ls2,
    output logic [31:0] inst_ls2,
    output logic [31:0] alu_result_ls2,
    output logic [4:0] mem_access_ls2,
    output logic [ 0:0] wb_rf_sel_ls2,
    output logic [ 0:0] rf_we_ls2,
    output logic [ 0:0] have_inst_ls2
);
    always_ff @(posedge clk) begin
        if(rst) begin
            pc_ls2           <= PC_RESET_VAL;
            inst_ls2         <= 32'h13;
            alu_result_ls2   <= 32'h0;
            mem_access_ls2   <= 5'h0;
            wb_rf_sel_ls2    <= 1'h0;
            rf_we_ls2        <= 1'h0;
            have_inst_ls2    <= 1'h0;
            csr_wdata_ls2    <= 32'h0;
            priv_vec_ls2      <= 3'h0;
        end
        else if(flush) begin
            have_inst_ls2    <= 1'h0;
        end 
        else begin
            pc_ls2           <= pc_ls1;
            inst_ls2         <= inst_ls1;
            alu_result_ls2 <= alu_result_ls1;
            mem_access_ls2   <= mem_access_ls1;
            wb_rf_sel_ls2    <= wb_rf_sel_ls1;
            rf_we_ls2        <= rf_we_ls1;
            have_inst_ls2    <= have_inst_ls1;
            csr_wdata_ls2    <= csr_wdata_ls1;
            priv_vec_ls2      <= priv_vec_ls1;
        end
    end

endmodule
