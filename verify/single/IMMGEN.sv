`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/04/18 11:22:17
// Design Name: 
// Module Name: IMMGEN
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

module IMMGEN#(
    parameter   DATAWIDTH = 32	
)(
    input  logic [31:0]            instr   ,
    output logic [DATAWIDTH - 1:0] imm       
);
   // imm generator
    logic [6:0] opcode;
    assign opcode = instr[6:0];
    logic sign_bit;
    assign sign_bit = instr[31];
    always_comb begin
        case(opcode)  
            //I-type
            7'b0010011,//9条短立即数操作
            7'b0000011,//5条load
            7'b1100111: //1条JALR
            imm = {{20{sign_bit}},instr[31:20]};
            //S-type
            7'b0100011: //3条store
            imm = {{20{sign_bit}},instr[31:25],instr[11:7]};
            //B-type
            7'b1100011: //6个有条件跳转
            imm = {{20{sign_bit}},instr[7],instr[30:25],instr[11:8],1'b0};
            //U-type
            7'b0110111,//LUI
            7'b0010111: //AUIPC
            imm = {instr[31:12],12'd0};//此为完成了左移12位的效果
            //J-type
            7'b1101111: //JAL
            imm = {{12{sign_bit}},instr[19:12],instr[20],instr[30:21],1'b0};
            default: imm = 32'd0;
        endcase
    end 
endmodule