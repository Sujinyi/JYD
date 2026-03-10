`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/04/08 12:42:16
// Design Name: 
// Module Name: PC
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

module PC#(
    parameter   DATAWIDTH = 32,
    parameter   RESET_VAL = 32'h8000_0000
)(
    input  logic                   clk  ,
    input  logic                   rst,
    input  logic [0:0]             stall ,
    input  logic [DATAWIDTH - 1:0] npc  ,
    output logic [DATAWIDTH - 1:0] pc_out
          
);
    always_ff @(posedge clk) begin
        if (rst) begin
            pc_out <= RESET_VAL;
        end
        else begin
            if(stall) begin
                pc_out <= pc_out; // 保持当前PC不变
            end
            else
                pc_out <= npc;
        end
    end
endmodule