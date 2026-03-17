`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/03/14 09:33:14
// Design Name: 
// Module Name: Fronted
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


module Fronted#(
    parameter RESET_VAL = 32'h80000000
)(
    input logic clk,
    input logic rst,
    input [63:0] irom_inst,
    input logic fetch0_accept,
    input logic fetch1_accept,
    input logic branch_request,
    input logic [31:0] branch_target,


    output logic irom_rd_en,   
    output logic irom_flush,
    output logic [31:0] irom_addr,
    output logic fetch0_valid,
    output logic [31:0] fetch0_inst,
    output logic [31:0] fetch0_pc,
    output logic fetch0_inst_exec,
    output logic fetch0_inst_lsu,
    output logic fetch0_inst_branch,
    output logic fetch0_inst_rd_valid,
    output logic fetch1_valid,
    output logic [31:0] fetch1_inst,
    output logic [31:0] fetch1_pc,
    output logic fetch1_inst_exec,      
    output logic fetch1_inst_lsu,
    output logic fetch1_inst_branch,
    output logic fetch1_inst_rd_valid
);

    wire fetch_valid_w;
    wire [63:0] fetch_inst_w;
    wire [31:0] fetch_pc_w;
    wire fetch_accept_w;

    Fetch #(
        .RESET_VAL(RESET_VAL)
    ) fetch(
        .clk(clk),
        .rst(rst),
        .fetch_accept(fetch_accept_w),
        .branch_request(branch_request),
        .branch_target(branch_target),
        .irom_inst(irom_inst),
        .irom_rd_en(irom_rd_en),
        .irom_flush(irom_flush),
        .irom_addr(irom_addr),
        .fetch_valid(fetch_valid_w),
        .fetch_inst(fetch_inst_w),
        .fetch_pc(fetch_pc_w)
    );

    Decode decode(
        .clk(clk),
        .rst(rst),
        .branch_request(branch_request),
        .fetch_in_valid(fetch_valid_w),
        .fetch_in_inst(fetch_inst_w),
        .fetch_in_pc(fetch_pc_w),
        .fetch_out0_accept(fetch0_accept),
        .fetch_out1_accept(fetch1_accept),

        .fetch_in_accept(fetch_accept_w),
        .fetch_out0_valid(fetch0_valid),
        .fetch_out0_inst(fetch0_inst),
        .fetch_out0_pc(fetch0_pc),
        .fetch_out0_inst_exec(fetch0_inst_exec),
        .fetch_out0_inst_lsu(fetch0_inst_lsu),
        .fetch_out0_inst_branch(fetch0_inst_branch),
        .fetch_out0_inst_rd_valid(fetch0_inst_rd_valid),

        .fetch_out1_valid(fetch1_valid),
        .fetch_out1_inst(fetch1_inst),
        .fetch_out1_pc(fetch1_pc),
        .fetch_out1_inst_exec(fetch1_inst_exec),      
        .fetch_out1_inst_lsu(fetch1_inst_lsu),
        .fetch_out1_inst_branch(fetch1_inst_branch),
        .fetch_out1_inst_rd_valid(fetch1_inst_rd_valid)
    );
endmodule
