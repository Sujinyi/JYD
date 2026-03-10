`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/02/24 14:29:22
// Design Name: 
// Module Name: MEM_WB
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


module MEM_WB#(
    parameter RESET_VAL = 32'h8000_0000
)(
    input logic clk,
    input logic rst,
    input logic RegWrite_mem,
    input logic [1:0] MemToReg_mem,
    input logic [31:0] aluout_mem,
    input logic [31:0] imm_mem,
    input logic [31:0] pcadd4_mem,
    input logic [31:0] d_rdata_mem,
    input logic [31:0] pc_mem,
    input logic [4:0] rRd_mem,
    output logic RegWrite_wb,
    output logic [1:0] MemToReg_wb,
    output logic [31:0] aluout_wb,
    output logic [31:0] imm_wb,
    output logic [31:0] pcadd4_wb,
    output logic [31:0] d_rdata_wb,
    output logic [31:0] pc_wb,
    output logic [4:0] rRd_wb,
    //trace
    input logic have_inst_mem,
    output logic have_inst_wb
    );

    always_ff @(posedge clk) begin
        if(rst) begin
            have_inst_wb <= 1'b0;
        end
        else begin
            have_inst_wb <= have_inst_mem;
        end
    end

    always_ff @( posedge clk ) begin
        if(rst) begin
            RegWrite_wb <= 1'd0;
            MemToReg_wb <= 2'd0;
            aluout_wb <= 32'd0;
            imm_wb <= 32'd0;
            pcadd4_wb <= 32'd0;
            d_rdata_wb <= 32'd0;
            pc_wb <= RESET_VAL;
            rRd_wb <= 5'd0;
        end
        else begin
            RegWrite_wb <= RegWrite_mem;
            MemToReg_wb <= MemToReg_mem;
            aluout_wb <= aluout_mem;
            imm_wb <= imm_mem;
            pcadd4_wb <= pcadd4_mem;
            d_rdata_wb <= d_rdata_mem;
            pc_wb <= pc_mem;
            rRd_wb <= rRd_mem;
        end
    end
endmodule
