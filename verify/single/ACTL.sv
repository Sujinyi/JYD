`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/05/03 11:25:24
// Design Name: 
// Module Name: ACTL
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

module ACTL(
    input  logic [6:0] opcode       ,
    input  logic [3:0] funct        ,
    output logic [3:0] ALUControl    
);
    // ALU control module
    always_comb  begin
        case(opcode)
            7'b0110011: begin // R-type
                case(funct[2:0])
                    3'b000: ALUControl = (!funct[3]) ? 4'b0000:4'b0001; // add/sub
                    3'b111: ALUControl = 4'b0010; // and
                    3'b110: ALUControl = 4'b0011; // or
                    3'b100: ALUControl = 4'b0100; // xor
                    3'b001: ALUControl = 4'b0101; // sll
                    3'b101: ALUControl = (!funct[3]) ? 4'b0110 : 4'b0111; // srl/sra
                    3'b010: ALUControl = 4'b1110; // slt
                    3'b011: ALUControl = 4'b1111; // sltu
                    default: ALUControl = 4'b1111; 
                endcase
            end
            7'b0010011:begin //I-type
                case(funct[2:0])
                    3'b000: ALUControl = 4'b0000; // addi 
                    3'b111: ALUControl = 4'b0010; // andi
                    3'b110: ALUControl = 4'b0011; // ori
                    3'b100: ALUControl = 4'b0100; // xori
                    3'b001: ALUControl = 4'b0101; // slli
                    3'b101: ALUControl = funct[3] ? 4'b0111 : 4'b0110; // srai/srli
                    3'b010: ALUControl = 4'b1110; // slt
                    3'b011: ALUControl = 4'b1111; // sltu
                    default: ALUControl = 4'b1111;
                endcase
            end
            7'b0000011: // IL-type
                ALUControl = 4'b0000; // add for address calculation
            7'b1100111: // jalr
                ALUControl = 4'b0000; // add 
            7'b0100011: // S-type
                ALUControl = 4'b0000; // add for address calculation
            7'b1100011:begin // B-type
                case(funct[2:0])
                    3'b000: ALUControl = 4'b1000; // beq
                    3'b001: ALUControl = 4'b1001; // bne
                    3'b100: ALUControl = 4'b1010; // blt
                    3'b101: ALUControl = 4'b1011; // bge
                    3'b110: ALUControl = 4'b1100; // bltu
                    3'b111: ALUControl = 4'b1101; // bgeu
                    default: ALUControl = 4'b1111;
                endcase
            end
            7'b0010111: // U-type auipc
                ALUControl = 4'b0000; // add for address calculation
            default:
                ALUControl = 4'b1111;
        endcase
    end
endmodule