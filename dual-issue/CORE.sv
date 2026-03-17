`timescale 1ns / 1ps
`include "config.sv"

module CORE #(
    parameter RESET_VAL = 32'h0
)(
    input  logic        clk,
    input  logic        rst,

    // Instruction Memory Interface (64-bit)
    output logic [31:0] irom_addr,
    input  logic [63:0] irom_inst,
    output logic        irom_rd_en,
    output logic        irom_flush,

    // Data Memory Interface (32-bit BRAM style)
    output logic [31:0] dram_addr,
    output logic [31:0] dram_data_wr,
    output logic [ 3:0] dram_wr,
    input  logic [31:0] dram_data_rd,

    output logic        debug_wb_have_inst,
    output logic [31:0] debug_wb_pc,
    output logic        debug_wb_ena,
    output logic [ 4:0] debug_wb_reg,
    output logic [31:0] debug_wb_value,

    output logic        debug_wb_have_inst_1,
    output logic [31:0] debug_wb_pc_1,
    output logic        debug_wb_ena_1,
    output logic [ 4:0] debug_wb_reg_1,
    output logic [31:0] debug_wb_value_1
);

    //-------------------------------------------------------------------------
    // 1. Internal Signals
    //-------------------------------------------------------------------------
    
    // Fronted <-> Issue
    logic        f0_valid, f1_valid;
    logic [31:0] f0_inst, f1_inst;
    logic [31:0] f0_pc, f1_pc;
    logic        f0_exec, f0_lsu, f0_branch, f0_rd_v;
    logic        f1_exec, f1_lsu, f1_branch, f1_rd_v;
    logic        f0_accept, f1_accept;

    // Issue <-> Execute/LSU
    logic        ex0_valid, ex1_valid, lsu_valid;
    logic [31:0] op0_inst, op0_pc;
    logic [4:0]  op0_rd, op0_ra, op0_rb;
    logic [31:0] op0_ra_val, op0_rb_val;
    
    logic [31:0] op1_inst, op1_pc;
    logic [4:0]  op1_rd, op1_ra, op1_rb;
    logic [31:0] op1_ra_val, op1_rb_val;

    logic [31:0] lsu_op_inst, lsu_op_pc;
    logic [4:0]  lsu_op_rd, lsu_op_ra, lsu_op_rb;
    logic [31:0] lsu_op_ra_val, lsu_op_rb_val;
    
    logic        ex0_hold, ex1_hold;

    // Execution <-> Writeback/Forwarding
    logic        ex0_wb_v, ex1_wb_v, lsu_wb_v;
    logic [4:0]  ex0_wb_rd, ex1_wb_rd, lsu_wb_rd;
    logic [31:0] ex0_wb_val, ex1_wb_val, lsu_wb_val;
    
    // Branch Resolution
    logic        br_req;
    logic [31:0] br_target;

    // RF Reads
    logic [31:0] rf_ra0, rf_rb0, rf_ra1, rf_rb1;

    // RF Writeback Mux
    logic        wb0_we, wb1_we;
    logic [4:0]  wb0_rd, wb1_rd;
    logic [31:0] wb0_val, wb1_val;
    logic        slot0_exec_q;
    logic        slot0_lsu_q;
    logic [31:0] slot0_pc_q;
    logic        slot1_exec_q;
    logic [31:0] slot1_pc_q;

    //-------------------------------------------------------------------------
    // 2. Module Instantiations
    //-------------------------------------------------------------------------

    // FRONTEND (Wraps Fetch and Decode)
    Fronted #(RESET_VAL) u_frontend (
        .clk(clk),
        .rst(rst),
        .irom_inst(irom_inst),
        .fetch0_accept(f0_accept),
        .fetch1_accept(f1_accept),
        .branch_request(br_req),
        .branch_target(br_target),
        .irom_rd_en(irom_rd_en),
        .irom_flush(irom_flush),
        .irom_addr(irom_addr),
        .fetch0_valid(f0_valid),
        .fetch0_inst(f0_inst),
        .fetch0_pc(f0_pc),
        .fetch0_inst_exec(f0_exec),
        .fetch0_inst_lsu(f0_lsu),
        .fetch0_inst_branch(f0_branch),
        .fetch0_inst_rd_valid(f0_rd_v),
        .fetch1_valid(f1_valid),
        .fetch1_inst(f1_inst),
        .fetch1_pc(f1_pc),
        .fetch1_inst_exec(f1_exec),      
        .fetch1_inst_lsu(f1_lsu),
        .fetch1_inst_branch(f1_branch),
        .fetch1_inst_rd_valid(f1_rd_v)
    );

    // ISSUE Stage
    Issue u_issue (
        .clk(clk),
        .rst(rst),
        .fetch0_valid(f0_valid),
        .fetch0_inst(f0_inst),
        .fetch0_pc(f0_pc),
        .fetch0_inst_exec(f0_exec),
        .fetch0_inst_lsu(f0_lsu),
        .fetch0_inst_branch(f0_branch),
        .fetch0_inst_rd_valid(f0_rd_v),
        .fetch1_valid(f1_valid),
        .fetch1_inst(f1_inst),
        .fetch1_pc(f1_pc),
        .fetch1_inst_exec(f1_exec),
        .fetch1_inst_lsu(f1_lsu),
        .fetch1_inst_branch(f1_branch),
        .fetch1_inst_rd_valid(f1_rd_v),
        .branch_exec0_request(br_req), 
        .branch_exec1_request(1'b0),   
        .wb_exec0_value(ex0_wb_val),
        .wb_exec1_value(ex1_wb_val),
        .wb_mem_valid(lsu_wb_v),
        .wb_mem_value(lsu_wb_val),
        .rf_rs1_val0(rf_ra0),
        .rf_rs2_val0(rf_rb0),
        .rf_rs1_val1(rf_ra1),
        .rf_rs2_val1(rf_rb1),
        .lsu_stall(1'b0), 
        .fetch0_accept(f0_accept),
        .fetch1_accept(f1_accept),
        .exec0_valid(ex0_valid),
        .exec1_valid(ex1_valid),
        .lsu_valid(lsu_valid),
        .opcode0_inst(op0_inst),
        .opcode0_pc(op0_pc),
        .opcode0_rd_idx(op0_rd),
        .opcode0_ra_idx(op0_ra),
        .opcode0_rb_idx(op0_rb),
        .opcode0_ra_operand(op0_ra_val),
        .opcode0_rb_operand(op0_rb_val),
        .opcode1_inst(op1_inst),
        .opcode1_pc(op1_pc),
        .opcode1_rd_idx(op1_rd),
        .opcode1_ra_idx(op1_ra),
        .opcode1_rb_idx(op1_rb),
        .opcode1_ra_operand(op1_ra_val),
        .opcode1_rb_operand(op1_rb_val),
        .lsu_opcode_inst(lsu_op_inst),
        .lsu_opcode_pc(lsu_op_pc),
        .lsu_opcode_rd_idx(lsu_op_rd),
        .lsu_opcode_ra_idx(lsu_op_ra),
        .lsu_opcode_rb_idx(lsu_op_rb),
        .lsu_opcode_ra_operand(lsu_op_ra_val),
        .lsu_opcode_rb_operand(lsu_op_rb_val),
        .exec0_hold(ex0_hold),
        .exec1_hold(ex1_hold)
    );

    // EXECUTE Stage - Slot 0 (ALU + Branch)
    Eexcute u_exec0 (
        .clk(clk),
        .rst(rst),
        .exec_valid(ex0_valid),
        .opcode_inst(op0_inst),
        .opcode_pc(op0_pc),
        .opcode_rd_idx(op0_rd),
        .opcode_ra_idx(op0_ra),
        .opcode_rb_idx(op0_rb),
        .opcode_ra_operand(op0_ra_val),
        .opcode_rb_operand(op0_rb_val),
        .hold(ex0_hold),
        .branch_request(br_req),
        .branch_targhet(br_target),
        .writeback_valid(ex0_wb_v),
        .writeback_rd_idx(ex0_wb_rd),
        .writeback_value(ex0_wb_val)
    );

    // EXECUTE Stage - Slot 1 (ALU only)
    Eexcute u_exec1 (
        .clk(clk),
        .rst(rst),
        .exec_valid(ex1_valid),
        .opcode_inst(op1_inst),
        .opcode_pc(op1_pc),
        .opcode_rd_idx(op1_rd),
        .opcode_ra_idx(op1_ra),
        .opcode_rb_idx(op1_rb),
        .opcode_ra_operand(op1_ra_val),
        .opcode_rb_operand(op1_rb_val),
        .hold(ex1_hold),
        .branch_request(), 
        .branch_targhet(),
        .writeback_valid(ex1_wb_v),
        .writeback_rd_idx(ex1_wb_rd),
        .writeback_value(ex1_wb_val)
    );

    // LSU Stage - Slot 0 only
    LSU u_lsu (
        .clk(clk),
        .rst(rst),
        .lsu_valid(lsu_valid),
        .lsu_opcode_inst(lsu_op_inst),
        .lsu_opcode_pc(lsu_op_pc),
        .lsu_opcode_rd_idx(lsu_op_rd),
        .lsu_opcode_ra_operand(lsu_op_ra_val),
        .lsu_opcode_rb_operand(lsu_op_rb_val),
        .mem_addr(dram_addr),
        .mem_data_wr(dram_data_wr),
        .mem_wr(dram_wr),
        .mem_data_rd(dram_data_rd),
        .writeback_valid(lsu_wb_v),
        .writeback_rd_idx(lsu_wb_rd),
        .writeback_value(lsu_wb_val)
    );

    // REGISTER FILE
    always_comb begin
        wb0_we  = 1'b0;
        wb0_rd  = 5'd0;
        wb0_val = 32'd0;
        wb1_we  = 1'b0;
        wb1_rd  = 5'd0;
        wb1_val = 32'd0;

        // Older results get priority on the two RF write ports.
        if (lsu_wb_v) begin
            wb0_we  = 1'b1;
            wb0_rd  = lsu_wb_rd;
            wb0_val = lsu_wb_val;

            if (ex0_wb_v) begin
                wb1_we  = 1'b1;
                wb1_rd  = ex0_wb_rd;
                wb1_val = ex0_wb_val;
            end else if (ex1_wb_v) begin
                wb1_we  = 1'b1;
                wb1_rd  = ex1_wb_rd;
                wb1_val = ex1_wb_val;
            end
        end else if (ex0_wb_v) begin
            wb0_we  = 1'b1;
            wb0_rd  = ex0_wb_rd;
            wb0_val = ex0_wb_val;

            if (ex1_wb_v) begin
                wb1_we  = 1'b1;
                wb1_rd  = ex1_wb_rd;
                wb1_val = ex1_wb_val;
            end
        end else if (ex1_wb_v) begin
            wb0_we  = 1'b1;
            wb0_rd  = ex1_wb_rd;
            wb0_val = ex1_wb_val;
        end
    end

    RF u_rf (
        .clk(clk),
        .rst(rst),
        .we0(wb0_we),
        .we1(wb1_we),
        .rd0(wb0_rd),
        .rd1(wb1_rd),
        .rd0_value(wb0_val),
        .rd1_value(wb1_val),
        .ra0(op0_ra),
        .rb0(op0_rb),
        .ra1(op1_ra),
        .rb1(op1_rb),
        .ra0_value(rf_ra0),
        .rb0_value(rf_rb0),
        .ra1_value(rf_ra1),
        .rb1_value(rf_rb1)
    );

    always_ff @(posedge clk) begin
        if (rst) begin
            slot0_exec_q <= 1'b0;
            slot0_lsu_q <= 1'b0;
            slot0_pc_q <= 32'd0;
            slot1_exec_q <= 1'b0;
            slot1_pc_q <= 32'd0;
        end else begin
            slot0_exec_q <= ex0_valid;
            slot0_lsu_q <= lsu_valid;
            slot0_pc_q <= op0_pc;
            slot1_exec_q <= ex1_valid;
            slot1_pc_q <= op1_pc;
        end
    end

    always_comb begin
        debug_wb_have_inst = slot0_exec_q || slot0_lsu_q;
        debug_wb_pc = slot0_pc_q;
        debug_wb_ena = 1'b0;
        debug_wb_reg = 5'd0;
        debug_wb_value = 32'd0;

        if (slot0_lsu_q) begin
            debug_wb_ena = lsu_wb_v;
            debug_wb_reg = lsu_wb_rd;
            debug_wb_value = lsu_wb_val;
        end else if (slot0_exec_q) begin
            debug_wb_ena = ex0_wb_v;
            debug_wb_reg = ex0_wb_rd;
            debug_wb_value = ex0_wb_val;
        end
    end

    always_comb begin
        debug_wb_have_inst_1 = slot1_exec_q;
        debug_wb_pc_1 = slot1_pc_q;
        debug_wb_ena_1 = ex1_wb_v;
        debug_wb_reg_1 = ex1_wb_rd;
        debug_wb_value_1 = ex1_wb_val;
    end

endmodule
