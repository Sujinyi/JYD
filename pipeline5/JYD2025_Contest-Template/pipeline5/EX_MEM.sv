`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/02/24 14:29:22
// Design Name: 
// Module Name: EX_MEM
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module EX_MEM#(
    parameter RESET_VAL = 32'h8000_0000
)(
    input logic clk,
    input logic rst,
    input logic [1:0] LdSrc_ex,
    input logic [1:0] StSrc_ex,
    input logic Sext_ex,
    input logic [31:0] imm_ex,
    input logic [4:0] rRd_ex,
    input logic RegWrite_ex,
    input logic MemWrite_ex,
    input logic [1:0] MemToReg_ex,
    input logic [31:0] aluout_ex,
    input logic [31:0] rR2_data_ex,
    input logic [31:0] pcadd4_ex,
    input logic [31:0] pc_ex,
    input logic isLUI_ex,
    output logic isLUI_mem,
    output logic [31:0] aluout_mem,
    output logic [31:0] rR2_data_mem,
    output logic [31:0] pcadd4_mem,
    output logic [4:0] rRd_mem,
    output logic RegWrite_mem,
    output logic MemWrite_mem,
    output logic [1:0] MemToReg_mem,
    output logic [1:0] LdSrc_mem,
    output logic [1:0] StSrc_mem,
    output logic Sext_mem,
    output logic [31:0] imm_mem,
    output logic [31:0] pc_mem,
    //trace
    input logic have_inst_ex,
    output logic have_inst_mem
    );

    always_ff @(posedge clk) begin
        if(rst) begin
            have_inst_mem <= 1'b0;
        end
        else begin
            have_inst_mem <= have_inst_ex;
        end
    end

    always_ff@(posedge clk) begin
        if(rst) begin
            isLUI_mem <= 1'b0;
            aluout_mem <= 32'd0;
            rR2_data_mem <= 32'd0;
            pcadd4_mem <= 32'd0;
            rRd_mem <= 5'd0;
            RegWrite_mem <= 1'd0;
            MemWrite_mem <= 1'd0;
            MemToReg_mem <= 2'd0;
            LdSrc_mem <= 2'd0;
            StSrc_mem <= 2'd0;
            Sext_mem <= 1'd0;
            imm_mem <= 32'd0;
            pc_mem <= RESET_VAL;
        end
        else begin
            isLUI_mem <= isLUI_ex;
            aluout_mem <= aluout_ex;
            rR2_data_mem <= rR2_data_ex;
            pcadd4_mem <= pcadd4_ex;
            rRd_mem <= rRd_ex;
            RegWrite_mem <= RegWrite_ex;
            MemWrite_mem <= MemWrite_ex;
            MemToReg_mem <= MemToReg_ex;
            LdSrc_mem <= LdSrc_ex;
            StSrc_mem <= StSrc_ex;
            Sext_mem <= Sext_ex;
            imm_mem <= imm_ex;
            pc_mem <= pc_ex;
        end
    end
endmodule
