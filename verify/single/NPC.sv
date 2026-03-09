`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/04/23 12:42:16
// Design Name: 
// Module Name: NPC
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

module NPC#(
    parameter   DATAWIDTH = 32
)(
    input  logic                   isTrue   ,
    input  logic [1:0]             npc_op   ,
    input  logic [DATAWIDTH - 1:0] pc       ,
    input  logic [DATAWIDTH - 1:0] offset   ,
    output logic [DATAWIDTH - 1:0] npc      ,
    output logic [DATAWIDTH - 1:0] pcadd4  
);

    logic [DATAWIDTH - 1:0] npc_imm;

    adder #(
        .DATAWIDTH  (DATAWIDTH)
    ) adder_pc_4(
        .A          (32'd4),
        .B          (pc),
        .Result     (pcadd4)
    );

    adder #(
        .DATAWIDTH  (DATAWIDTH)
    ) adder_right(
        .A          (pc),
        .B          (offset),
        .Result     (npc_imm)
    );

    logic [DATAWIDTH - 1:0] npc_branch;
    assign npc_branch = isTrue ? npc_imm : pcadd4;
    logic [DATAWIDTH - 1:0] npc_jar;
    assign npc_jar = npc_imm;
    logic [DATAWIDTH - 1:0] npc_jalr;
    assign npc_jalr = offset&32'hFFFF_FFFE;

    MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_npc(
        .A          (pcadd4),//00 non-branch
        .B          (npc_branch),//01 branch
        .C          (npc_jalr),//10 处理jalr指令
        .D          (npc_jar),   //11 处理jar指令
        .Control    (npc_op),
        .Result     (npc)
    );

endmodule