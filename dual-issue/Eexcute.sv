`timescale 1ns / 1ps
`include "config.sv"


module Eexcute(
    input  logic        clk,
    input  logic        rst,
    input  logic        exec_valid,
    input  logic [31:0] opcode_inst,
    input  logic [31:0] opcode_pc,
    input  logic [ 4:0] opcode_rd_idx,
    input  logic [ 4:0] opcode_ra_idx,
    input  logic [ 4:0] opcode_rb_idx,
    input  logic [31:0] opcode_ra_operand,
    input  logic [31:0] opcode_rb_operand,
    input  logic        hold,

    output logic        branch_request,
    output logic [31:0] branch_targhet,
    output logic        writeback_valid,
    output logic [ 4:0] writeback_rd_idx,
    output logic [31:0] writeback_value
);

    wire [31:0] imm_i = {{20{opcode_inst[31]}}, opcode_inst[31:20]};
    wire [31:0] imm_b = {{19{opcode_inst[31]}}, opcode_inst[31], opcode_inst[7], opcode_inst[30:25], opcode_inst[11:8], 1'b0};
    wire [31:0] imm_u = {opcode_inst[31:12], 12'b0};
    wire [31:0] imm_j = {{12{opcode_inst[31]}}, opcode_inst[19:12], opcode_inst[20], opcode_inst[30:25], opcode_inst[24:21], 1'b0};

    logic [31:0] alu_in1, alu_in2;
    logic [3:0]  alu_op;
    logic        is_br, is_jal, is_jalr;
    logic        rd_write_en;
    
    wire [6:0] op = opcode_inst[6:0];
    wire [2:0] f3 = opcode_inst[14:12];
    wire [6:0] f7 = opcode_inst[31:25];

    always_comb begin
        alu_in1 = opcode_ra_operand;
        alu_in2 = opcode_rb_operand;
        alu_op  = `ADD;
        is_br   = 1'b0;
        is_jal  = 1'b0;
        is_jalr = 1'b0;
        rd_write_en = 1'b0;

        case (op)
            7'h33: begin
                alu_op = {f7[5], f3}; // R-type
                rd_write_en = 1'b1;
            end
            7'h13: begin // I-type
                alu_in2 = imm_i;
                alu_op  = (f3 == 3'h5 && f7[5]) ? `SRA : {1'b0, f3};
                rd_write_en = 1'b1;
            end
            7'h37: begin // LUI
                alu_in1 = 32'b0;
                alu_in2 = imm_u;
                rd_write_en = 1'b1;
            end
            7'h17: begin // AUIPC
                alu_in1 = opcode_pc;
                alu_in2 = imm_u;
                rd_write_en = 1'b1;
            end
            7'h63: is_br   = 1'b1;
            7'h6f: begin
                is_jal  = 1'b1;
                rd_write_en = 1'b1;
            end
            7'h67: begin
                is_jalr = 1'b1;
                rd_write_en = 1'b1;
            end
        endcase
    end

    wire [31:0] alu_res;
    ALU u_alu (
        .sr1(alu_in1),
        .sr2(alu_in2),
        .alu_op(alu_op),
        .result(alu_res)
    );

    logic br_taken;
    always_comb begin
        case (f3)
            3'h0: br_taken = (opcode_ra_operand == opcode_rb_operand); // BEQ
            3'h1: br_taken = (opcode_ra_operand != opcode_rb_operand); // BNE
            3'h4: br_taken = ($signed(opcode_ra_operand) < $signed(opcode_rb_operand)); // BLT
            3'h5: br_taken = ($signed(opcode_ra_operand) >= $signed(opcode_rb_operand)); // BGE
            3'h6: br_taken = (opcode_ra_operand < opcode_rb_operand);  // BLTU
            3'h7: br_taken = (opcode_ra_operand >= opcode_rb_operand); // BGEU
            default: br_taken = 1'b0;
        endcase
    end

    wire [31:0] br_target   = opcode_pc + imm_b;
    wire [31:0] jal_target  = opcode_pc + imm_j;
    wire [31:0] jalr_target = (opcode_ra_operand + imm_i) & ~32'h1;

    wire jump_fire = (is_br && br_taken) || is_jal || is_jalr;
    
    always_ff @(posedge clk) begin
        if (rst) begin
            branch_request  <= 1'b0;
            branch_targhet <= 32'b0;
            writeback_valid <= 1'b0;
            writeback_rd_idx <= 5'd0;
            writeback_value <= 32'b0;
        end else if (!hold && exec_valid) begin
            branch_request  <= jump_fire;
            branch_targhet <= is_jalr ? jalr_target : (is_jal ? jal_target : br_target);
            writeback_valid <= rd_write_en;
            writeback_rd_idx <= opcode_rd_idx;
            writeback_value <= (is_jal || is_jalr) ? (opcode_pc + 4) : alu_res;
        end else begin
            branch_request  <= 1'b0;
            writeback_valid <= 1'b0;
        end
    end
endmodule
