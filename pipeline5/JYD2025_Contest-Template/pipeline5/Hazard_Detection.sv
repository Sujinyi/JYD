`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/02/24 14:29:22
// Design Name: 
// Module Name: Hazard_Detection
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


module Hazard_Detection(
    input logic [4:0] rR1_id,
    input logic [4:0] rR2_id,
    input logic [4:0] rRd_ex,
    input logic [1:0] MemToReg_ex,
    input logic       branched,
    output logic      stall,
    output logic      ID_EX_flush,
    output logic      IF_ID_flush
    );

    logic load_use_hazard;
    assign load_use_hazard = (MemToReg_ex == 2'b10) && ((rRd_ex == rR1_id) || (rRd_ex == rR2_id));

    always_comb begin
        if (load_use_hazard) begin
            stall = 1'b1;
            ID_EX_flush = 1'b1;
            IF_ID_flush = 1'b0; // 不需要清空IF/ID寄存器，因为我们只是暂停IF阶段，不让它更新
        end 
        else begin
            if (branched) begin
                stall = 1'b0; // 分支指令不需要暂停流水线，因为我们会清空IF/ID寄存器
                ID_EX_flush = 1'b1; // 清空ID/EX寄存器，丢弃错误的指令
                IF_ID_flush = 1'b1; // 清空IF/ID寄存器，丢弃错误的指令
            end
            else begin
                // 如果没有分支指令，我们保持之前的控制信号不变
                stall = 1'b0;
                ID_EX_flush = 1'b0;
                IF_ID_flush = 1'b0;
            end 
        end
    end
endmodule
