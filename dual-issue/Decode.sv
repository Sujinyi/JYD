`timescale 1ns / 1ps

module Decode(
    input  logic        clk,
    input  logic        rst,
    input  logic        branch_request,
    input  logic        fetch_in_valid,
    input  logic [63:0] fetch_in_inst,
    input  logic [31:0] fetch_in_pc,
    input  logic        fetch_out0_accept,
    input  logic        fetch_out1_accept,

    output logic        fetch_in_accept,
    output logic        fetch_out0_valid,
    output logic [31:0] fetch_out0_inst,
    output logic [31:0] fetch_out0_pc,
    output logic        fetch_out0_inst_exec,
    output logic        fetch_out0_inst_lsu,
    output logic        fetch_out0_inst_branch,
    output logic        fetch_out0_inst_rd_valid,
    output logic        fetch_out1_valid,
    output logic [31:0] fetch_out1_inst,
    output logic [31:0] fetch_out1_pc,
    output logic        fetch_out1_inst_exec,
    output logic        fetch_out1_inst_lsu,
    output logic        fetch_out1_inst_branch,
    output logic        fetch_out1_inst_rd_valid
);

    Inst_Buffer inst_buffer(
        .clk(clk),
        .rst(rst),
        .flush(branch_request),
        .push(fetch_in_valid),
        .pc_in(fetch_in_pc),
        .data_in(fetch_in_inst),
        .pop0(fetch_out0_accept),
        .pop1(fetch_out1_accept),
        .accept(fetch_in_accept),
        .valid0(fetch_out0_valid),
        .pc0_out(fetch_out0_pc),
        .data0_out(fetch_out0_inst),
        .valid1(fetch_out1_valid),
        .pc1_out(fetch_out1_pc),
        .data1_out(fetch_out1_inst)
    );

    Decoder decoder0(
        .opcode(fetch_out0_inst[6:0]),
        .exec(fetch_out0_inst_exec),
        .lsu(fetch_out0_inst_lsu),
        .branch(fetch_out0_inst_branch),
        .rd_valid(fetch_out0_inst_rd_valid)
    );

    Decoder decoder1(
        .opcode(fetch_out1_inst[6:0]),
        .exec(fetch_out1_inst_exec),
        .lsu(fetch_out1_inst_lsu),
        .branch(fetch_out1_inst_branch),
        .rd_valid(fetch_out1_inst_rd_valid)
    );

endmodule
