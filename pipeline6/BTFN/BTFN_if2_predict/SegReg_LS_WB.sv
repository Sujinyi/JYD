module SegReg_LS_WB#(
    parameter PC_RESET_VAL = 32'h0
)(
    input  logic [ 0:0] clk,
    input  logic [ 0:0] rst,

    input  logic [31:0] pc_ls,
    input  logic [31:0] inst_ls,
    input  logic [31:0] alu_result_ls,
    input  logic [31:0] mem_rdata_ls,
    input  logic [ 0:0] wb_rf_sel_ls,
    input  logic [ 0:0] rf_we_ls,
    input  logic [ 0:0] have_inst_ls,

    output logic [31:0] pc_wb,
    output logic [31:0] inst_wb,
    output logic [31:0] alu_result_wb,
    output logic [31:0] mem_rdata_wb,
    output logic [ 0:0] wb_rf_sel_wb,
    output logic [ 0:0] rf_we_wb,
    output logic [ 0:0] have_inst_wb
);
    always_ff @(posedge clk) begin
        if(rst) begin
            pc_wb           <= PC_RESET_VAL;
            inst_wb         <= 32'h13;
            alu_result_wb   <= 32'h0;
            mem_rdata_wb    <= 32'h0;
            wb_rf_sel_wb    <= 1'h0;
            rf_we_wb        <= 1'h0;
            have_inst_wb    <= 1'h0;
        end 
        else begin
            pc_wb           <= pc_ls;
            inst_wb         <= inst_ls;
            alu_result_wb <= alu_result_ls;
            mem_rdata_wb    <= mem_rdata_ls;
            wb_rf_sel_wb    <= wb_rf_sel_ls;
            rf_we_wb        <= rf_we_ls;
            have_inst_wb    <= have_inst_ls;
        end
    end

endmodule