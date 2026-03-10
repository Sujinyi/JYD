`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/04/30 8:26:09
// Design Name: 
// Module Name: Control
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

module Control(
    input  logic [6:0]  opcode      ,
    input  logic [3:0]  funct      ,
    output logic [1:0]  NpcOp       ,//00: pc+4,01:branch,10:jalr,11:jal
    output logic        RegWrite    ,//写入寄存器使能
    output logic [1:0]  MemToReg    ,//写入寄存器数据来源 00:pc+4 01:alu 10:mem 11:imm
    output logic        MemWrite    ,
    output logic        OffsetOrigin,//0：imm 1:aluout
    output logic        alua_sel,//0:reg 1:pc       
    output logic        alub_sel,//0:reg 1:imm
    output logic [1:0]  LdSrc,       //00:lw, 01:lb(u),10:lh(u)
    output logic [1:0]  StSrc,       //00:sw, 01:sb, 10:sh
    output logic        Sext,        //0:zero_ext, 1:sign_ext
    output logic        isLUI,
    output logic        have_inst
);

    always_comb begin 
        case(opcode)
            7'b0000000: have_inst = 1'b0; // NOP
            default: have_inst = 1'b1;
        endcase
    end
   // controller module
   always_comb begin
       case (opcode)
           7'b0110011: begin // R-type
               NpcOp    = 2'b00;
               RegWrite = 1'b1;
               MemToReg = 2'b01;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b0;
               //PcSrc    = 1'b0;
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0; 
               isLUI    = 1'b0;
           end
           7'b0010011: begin // I-type
               NpcOp    = 2'b00;
               RegWrite = 1'b1;
               MemToReg = 2'b01;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b1;
               //PcSrc    = 1'b0;
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           7'b0000011: begin // IL-type
               NpcOp    = 2'b00;
               RegWrite = 1'b1;
               MemToReg = 2'b10;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b1;
               //PcSrc    = 1'b0;
               case(funct[1:0])
                   2'b10: LdSrc = 2'b00; // lw
                   2'b00: LdSrc = 2'b01; // lb/lbu
                   2'b01: LdSrc = 2'b10; // lh/lhu
                   default: LdSrc = 2'b00;
                endcase
               StSrc    = 2'b00;
               Sext     = ~funct[2];
               isLUI    = 1'b0;
           end
           7'b1100111: begin // IJ-type jalr
               NpcOp    = 2'b10;
               RegWrite = 1'b1;
               MemToReg = 2'b00;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b1;
               alua_sel = 1'b0;
               alub_sel   = 1'b1;
               //PcSrc    = 1'b0;//pcadd4_wb
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           7'b0100011: begin // S-type
               NpcOp    = 2'b00;
               RegWrite = 1'b0;
               MemToReg = 2'b00;//dont care
               MemWrite = 1'b1;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b1;
               //PcSrc    = 1'b0;
               LdSrc    = 2'b00;
               case(funct[1:0])
                   2'b10: StSrc = 2'b00; // sw
                   2'b00: StSrc = 2'b01; // sb
                   2'b01: StSrc = 2'b10; // sh
                   default: StSrc = 2'b00;
                endcase
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           7'b1100011: begin // B-type
               NpcOp    = 2'b01;
               RegWrite = 1'b0;
               MemToReg = 2'b00;//dont care
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b0;
               //PcSrc    = 1'b0;
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           7'b0110111: begin // U-type lui
               NpcOp    = 2'b00;
               RegWrite = 1'b1;
               MemToReg = 2'b11;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b1;
               //PcSrc    = 1'b0;//pcadd4_wb
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b1;
           end
           7'b0010111: begin // U-type auipc
               NpcOp    = 2'b00;
               RegWrite = 1'b1;
               //MemToReg = 2'b00;
               MemToReg = 2'b01;//复用alu的adder
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b1;//pc
               alub_sel   = 1'b1;
               //PcSrc    = 1'b1;
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           7'b1101111: begin // J-type jal
               NpcOp    = 2'b11;
               RegWrite = 1'b1;
               MemToReg = 2'b00;
               MemWrite = 1'b0;
               OffsetOrigin = 1'b0;
               alua_sel = 1'b0;
               alub_sel   = 1'b0;
               //PcSrc    = 1'b0;//pcadd4_wb
               LdSrc    = 2'b00;
               StSrc    = 2'b00;
               Sext     = 1'b0;
               isLUI    = 1'b0;
           end
           default: begin
              NpcOp        = 2'b00;
              RegWrite     = 1'b0;
              MemToReg     = 2'b00;
              MemWrite     = 1'b0;
              OffsetOrigin = 1'b0;
              alua_sel = 1'b0;
              alub_sel       = 1'b0;
              //PcSrc    = 1'b0;
              LdSrc    = 2'b00;
              StSrc    = 2'b00;
              Sext     = 1'b0; 
              isLUI    = 1'b0;
           end
       endcase
   end
endmodule
