module SegReg_LS2_WB#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,
    input  logic [ 0:0] flush,

    input  logic [31:0] pc_ls2,
    input  logic [31:0] inst_ls2,
    input  logic [31:0] alu_result_ls2,
    input  logic [4:0] mem_access_ls2,
    input  logic [31:0] mem_rdata_ls2,
    input  logic [ 0:0] wb_rf_sel_ls2,
    input  logic [ 0:0] rf_we_ls2,
    input  logic [ 0:0] have_inst_ls2,
    input  logic [31:0] csr_wdata_ls2,
    input  logic [ 2:0] priv_vec_ls2,

    output logic [31:0] csr_wdata_wb,
    output logic [ 2:0] priv_vec_wb,
    output logic [31:0] pc_wb,
    output logic [31:0] inst_wb,
    output logic [31:0] alu_result_wb,
    output logic [4:0] mem_access_wb,
    output logic [31:0] mem_rdata_wb,
    output logic [ 0:0] wb_rf_sel_wb,
    output logic [ 0:0] rf_we_wb,
    output logic [ 0:0] have_inst_wb
);
    always_ff @(posedge clk) begin
        if(rst||flush) begin
            pc_wb           <= PC_RESET_VAL;
            inst_wb         <= 32'h13;
            alu_result_wb   <= 32'h0;
            mem_access_wb   <= 5'h0;
            mem_rdata_wb    <= 32'h0;
            wb_rf_sel_wb    <= 1'h0;
            rf_we_wb        <= 1'h0;
            have_inst_wb    <= 1'h0;
            csr_wdata_wb    <= 32'h0;
            priv_vec_wb     <= 3'h0;
        end 
        else begin
            pc_wb           <= pc_ls2;
            inst_wb         <= inst_ls2;
            alu_result_wb <= alu_result_ls2;
            mem_access_wb   <= mem_access_ls2;
            mem_rdata_wb    <= mem_rdata_ls2;
            wb_rf_sel_wb    <= wb_rf_sel_ls2;
            rf_we_wb        <= rf_we_ls2;
            have_inst_wb    <= have_inst_ls2;
            csr_wdata_wb    <= csr_wdata_ls2;
            priv_vec_wb     <= priv_vec_ls2;
        end
    end

endmodule