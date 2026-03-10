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
    output logic [DATAWIDTH - 1:0] pcadd4   ,
    output logic [0:0]             branched
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
    assign npc_branch = isTrue ? (npc_imm - 8): pcadd4;//静态分支预测，预测分支不跳转，所以npc_branch默认是pc+4，如果分支预测成功，则npc_branch是pc+offset-8，因为pc在取指阶段已经加了4，执行阶段又加了4，所以要减去8
    logic [DATAWIDTH - 1:0] npc_jal;
    //assign npc_jal = npc_imm;
    assign npc_jal = npc_imm - 8;//jal指令的目标地址是pc+offset-8，因为pc在取指阶段已经加了4，执行阶段又加了4，所以要减去8
    logic [DATAWIDTH - 1:0] npc_jalr;
    assign npc_jalr = offset&32'hFFFF_FFFE;

    MUX4_1 #(
        .WIDTH      (DATAWIDTH)
    ) mux_npc(
        .A          (pcadd4),//00 non-branch
        .B          (npc_branch),//01 branch
        .C          (npc_jalr),//10 处理jalr指令
        .D          (npc_jal),   //11 处理jal指令
        .Control    (npc_op),
        .Result     (npc)
    );

    assign branched = ((npc_op == 2'b01)&isTrue)|(npc_op == 2'b11)|(npc_op == 2'b10);
endmodule