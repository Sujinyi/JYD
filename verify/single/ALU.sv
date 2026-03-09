`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/05/01 10:31:41
// Design Name: 
// Module Name: ALU
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

module ALU#(
    parameter   DATAWIDTH = 32	
)(
    input  logic [DATAWIDTH - 1:0]  A           ,
    input  logic [DATAWIDTH - 1:0]  B           ,
    input  logic [3:0]              ALUControl  ,
    output logic [DATAWIDTH - 1:0]  Result      ,
    output logic                    isTrue        
);
    always_comb begin 
        case (ALUControl)
            4'b0000: Result = A + B;
            4'b0001: Result = A + (~B) + 32'd1;
            4'b0010: Result = A & B;
            4'b0011: Result = A | B;
            4'b0100: Result = A ^ B;
            4'b0101: Result = A << (B[4:0]);
            4'b0110: Result = A >> (B[4:0]);
            //4'b0111: Result = A >>> (B[4:0]);
            4'b0111: Result = $signed(A) >>> (B[4:0]);
            4'b1000: isTrue = (A==B)? 1'b1 : 1'b0;//beq
            4'b1001: isTrue = (A!=B)? 1'b1 : 1'b0;//bne
            4'b1010: isTrue = ($signed(A) < $signed(B)) ? 1'b1 : 1'b0;//blt
            4'b1011: isTrue = ($signed(A) >= $signed(B)) ? 1'b1 : 1'b0;//bge
            4'b1100: isTrue = (A < B) ? 1'b1 : 1'b0;//bltu
            4'b1101: isTrue = (A >= B) ? 1'b1 : 1'b0;//bgeu
            4'b1110: Result = ($signed(A) < $signed(B)) ? 32'd1 : 32'd0; //slt
            4'b1111: Result = (A < B) ? 32'd1 : 32'd0; //sltu
            default:begin 
                Result = 32'd0;
                isTrue = 1'b0;
            end
        endcase
    end
endmodule