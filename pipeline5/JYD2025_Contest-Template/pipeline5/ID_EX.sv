`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/02/24 14:29:22
// Design Name: 
// Module Name: ID_EX
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


module ID_EX#(
    parameter RESET_VAL = 32'h8000_0000
)(
    input logic clk,
    input logic rst,
    input logic [1:0] npc_op_id,
    input logic MemWrite_id,
    input logic RegWrite_id,
    input logic [1:0] MemToReg_id,
    input logic OffsetOrigin_id,
    input logic alua_sel_id,
    input logic alub_sel_id,
    input logic [1:0] LdSrc_id,
    input logic [1:0] StSrc_id,
    input logic Sext_id,
    input logic [31:0] imm_id,
    input logic [4:0] rR1_id,
    input logic [4:0] rR2_id,
    input logic [4:0] rRd_id,
    input logic [31:0] pc_id,
    input logic [31:0] pcadd4_id,
    input logic [3:0]  ALUControl_id,
    input logic [31:0] rR1_data_id,
    input logic [31:0] rR2_data_id,
    input logic isLUI_id,
    input logic flush,
    output logic isLUI_ex,
    output logic [31:0] pc_ex,
    output logic [31:0] pcadd4_ex,
    output logic [3:0] ALUControl_ex,
    output logic [31:0] rR1_data_ex,
    output logic [31:0] rR2_data_ex,
    //output logic [31:0] instr_ex,
    output logic [1:0] npc_op_ex,
    output logic MemWrite_ex,
    output logic RegWrite_ex,
    output logic [1:0] MemToReg_ex,
    output logic OffsetOrigin_ex,
    output logic alua_sel_ex,
    output logic alub_sel_ex,
    output logic [1:0] LdSrc_ex,
    output logic [1:0] StSrc_ex,
    output logic Sext_ex,
    output logic [31:0] imm_ex,
    output logic [4:0] rR1_ex,
    output logic [4:0] rR2_ex,
    output logic [4:0] rRd_ex,
    //trace
    input logic have_inst_id,
    output logic have_inst_ex
    );  

    always_ff @(posedge clk) begin
        if(rst) begin
            have_inst_ex <= 1'b0;
        end
        else begin
            if(flush) begin
                have_inst_ex <= 1'b0;
            end
            else begin
                have_inst_ex <= have_inst_id;
            end
        end
    end

    always_ff @(posedge clk) begin
        if(rst) begin
            isLUI_ex <= 1'b0;
            pc_ex <= RESET_VAL;
            pcadd4_ex <= 32'd0;
            ALUControl_ex <= 4'd0;
            rR1_data_ex <= 32'd0;
            rR2_data_ex <= 32'd0;
            //instr_ex <= 32'd0;
            npc_op_ex <= 2'b00;
            MemWrite_ex <= 1'b0;
            RegWrite_ex <= 1'b0;
            MemToReg_ex <= 2'b00;
            OffsetOrigin_ex <= 1'b0;
            alua_sel_ex <= 1'b0;
            alub_sel_ex <= 1'b0;
            LdSrc_ex <= 2'b00;
            StSrc_ex <= 2'b00;
            Sext_ex <= 1'b0;
            imm_ex <= 32'd0;
            rR1_ex <= 5'd0;
            rR2_ex <= 5'd0;
            rRd_ex <= 5'd0; 
        end
        else begin
            if(flush) begin
                isLUI_ex <= 1'b0;
                pc_ex <= RESET_VAL;
                pcadd4_ex <= 32'd0;
                ALUControl_ex <= 4'd0;
                rR1_data_ex <= 32'd0;
                rR2_data_ex <= 32'd0;
                //instr_ex <= 32'd0;
                npc_op_ex <= 2'b00;
                MemWrite_ex <= 1'b0;
                RegWrite_ex <= 1'b0;
                MemToReg_ex <= 2'b00;
                OffsetOrigin_ex <= 1'b0;
                alua_sel_ex <= 1'b0;
                alub_sel_ex <= 1'b0;
                LdSrc_ex <= 2'b00;
                StSrc_ex <= 2'b00;
                Sext_ex <= 1'b0;
                imm_ex <= 32'd0;
                rR1_ex <= 5'd0;
                rR2_ex <= 5'd0;
                rRd_ex <= 5'd0; 
            end
            else begin
                isLUI_ex <= isLUI_id;
                pc_ex <= pc_id;
                pcadd4_ex <= pcadd4_id;
                ALUControl_ex <= ALUControl_id;
                rR1_data_ex <= rR1_data_id;
                rR2_data_ex <= rR2_data_id;
                //instr_ex <= instr_id;
                npc_op_ex <= npc_op_id;
                MemWrite_ex <= MemWrite_id;
                RegWrite_ex <= RegWrite_id;
                MemToReg_ex <= MemToReg_id;
                OffsetOrigin_ex <= OffsetOrigin_id;
                alua_sel_ex <= alua_sel_id;
                alub_sel_ex <= alub_sel_id;
                LdSrc_ex <= LdSrc_id;
                StSrc_ex <= StSrc_id;
                Sext_ex <= Sext_id;
                imm_ex <= imm_id;
                rR1_ex <= rR1_id;
                rR2_ex <= rR2_id;
                rRd_ex <= rRd_id; 
            end
        end
        
    end
endmodule
