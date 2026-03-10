`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/02/24 14:29:22
// Design Name: 
// Module Name: Forwarding
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


module Forwarding(
    input logic [4:0] rR1_ex,
    input logic [4:0] rR2_ex,
    input logic [4:0] rRd_mem,
    input logic [4:0] rRd_wb,
    input logic isLUI_mem,
    input logic RegWrite_mem,
    input logic RegWrite_wb,
    output logic [1:0] ForwardA,    
    output logic [1:0] ForwardB
    );


    wire ex_hazard1 = RegWrite_mem && (rRd_mem != 0) && (rRd_mem == rR1_ex);
    wire ex_hazard2 = RegWrite_mem && (rRd_mem != 0) && (rRd_mem == rR2_ex);
    wire mem_hazard1 = RegWrite_wb && (rRd_wb != 0) && (rRd_wb == rR1_ex);
    wire mem_hazard2 = RegWrite_wb && (rRd_wb != 0) && (rRd_wb == rR2_ex);

    always_comb begin
        if(ex_hazard1) begin
            ForwardA = isLUI_mem ? 2'b11 : 2'b10;//ex冒险且执行的是LUI时，前递imm_mem而不是alu_mem
        end
        else if(mem_hazard1) begin
            ForwardA = 2'b01;
        end
        else begin
            ForwardA = 2'b00;
        end
    end

    always_comb begin
        if(ex_hazard2) begin
            ForwardB = isLUI_mem ? 2'b11 : 2'b10;//ex冒险且执行的是LUI时，前递imm_mem而不是alu_mem
        end
        else if(mem_hazard2) begin
            ForwardB = 2'b01;
        end
        else begin
            ForwardB = 2'b00;
        end
    end
endmodule
