`timescale 1ns / 1ps

module Fetch#(
    parameter RESET_VAL = 32'd0
)(
    input  logic        clk,
    input  logic        rst,
    input  logic        fetch_accept,
    input  logic        branch_request,
    input  logic [31:0] branch_target,
    input  logic [63:0] irom_inst,
    output logic        irom_rd_en,
    output logic [31:0] irom_addr,
    output logic        fetch_valid,
    output logic [63:0] fetch_inst,
    output logic [31:0] fetch_pc
);

    logic [31:0] pc_f_q;
    logic [31:0] pc_d_q;
    logic        irom_rd_d_q;

    always_ff @(posedge clk) begin
        if (rst) begin
            pc_f_q <= RESET_VAL;
        end else if (branch_request) begin
            pc_f_q <= branch_target;
        end else if (fetch_accept) begin
            pc_f_q <= pc_f_q + 32'd8;
        end
    end

    assign irom_rd_en = fetch_accept && !branch_request;
    assign irom_addr = pc_f_q;

    always_ff @(posedge clk) begin
        if (rst) begin
            irom_rd_d_q <= 1'b0;
            pc_d_q <= RESET_VAL;
        end else if (branch_request) begin
            irom_rd_d_q <= 1'b0;
        end else if (fetch_accept) begin
            irom_rd_d_q <= irom_rd_en;
            pc_d_q <= pc_f_q;
        end
    end

    assign fetch_valid = irom_rd_d_q && !branch_request;
    assign fetch_inst = irom_inst;
    assign fetch_pc = pc_d_q;

endmodule
