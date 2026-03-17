`timescale 1ns / 1ps

module Inst_Buffer#(
    parameter WIDTH   = 64,
    parameter DEPTH   = 4,
    parameter ADDR_W  = 2
)(
    input  logic                  clk,
    input  logic                  rst,
    input  logic                  flush,
    input  logic                  push,
    input  logic                  push_upper,
    input  logic [31:0]           pc_in,
    input  logic [WIDTH-1:0]      data_in,
    input  logic                  pop0,
    input  logic                  pop1,
    input  logic                  drop1,
    output logic                  accept,
    output logic                  valid0,
    output logic [31:0]           pc0_out,
    output logic [(WIDTH/2)-1:0]  data0_out,
    output logic                  valid1,
    output logic [31:0]           pc1_out,
    output logic [(WIDTH/2)-1:0]  data1_out
);

    localparam COUNT_W = ADDR_W + 1;

    logic [31:0]      pc_q[DEPTH-1:0];
    logic             valid0_q[DEPTH-1:0];
    logic             valid1_q[DEPTH-1:0];
    logic [WIDTH-1:0] ram_q[DEPTH-1:0];
    logic [ADDR_W-1:0] rd_ptr_q;
    logic [ADDR_W-1:0] wr_ptr_q;
    logic [COUNT_W-1:0] count_q;

    logic push_w;
    logic pop0_w;
    logic pop1_w;
    logic drop1_w;
    logic pop_complete_w;
    logic slot0_from_upper_w;
    integer i;

    assign push_w = push && accept;
    assign pop0_w = pop0 && valid0;
    assign pop1_w = pop1 && valid1;
    assign drop1_w = drop1 && valid0_q[rd_ptr_q] && valid1_q[rd_ptr_q];
    assign pop_complete_w = (pop0_w && pop1_w) ||
                            (pop0_w && drop1_w) ||
                            (pop0_w && !valid1) ||
                            (pop1_w && !valid0);

    always_ff @(posedge clk) begin
        if (rst) begin
            rd_ptr_q <= '0;
            wr_ptr_q <= '0;
            count_q <= '0;
            for (i = 0; i < DEPTH; i = i + 1) begin
                ram_q[i] <= '0;
                pc_q[i] <= 32'd0;
                valid0_q[i] <= 1'b0;
                valid1_q[i] <= 1'b0;
            end
        end else if (flush) begin
            rd_ptr_q <= '0;
            wr_ptr_q <= '0;
            count_q <= '0;
        end else begin
            if (push_w) begin
                ram_q[wr_ptr_q] <= data_in;
                pc_q[wr_ptr_q] <= {pc_in[31:3], 3'b000};
                valid0_q[wr_ptr_q] <= !push_upper;
                valid1_q[wr_ptr_q] <= 1'b1;
                wr_ptr_q <= wr_ptr_q + 1'b1;
            end

            if (pop0_w) begin
                valid0_q[rd_ptr_q] <= 1'b0;
            end
            if (pop1_w) begin
                valid1_q[rd_ptr_q] <= 1'b0;
            end
            if (drop1_w) begin
                valid1_q[rd_ptr_q] <= 1'b0;
            end

            if (pop_complete_w) begin
                rd_ptr_q <= rd_ptr_q + 1'b1;
            end

            if (push_w && !pop_complete_w) begin
                count_q <= count_q + 1'b1;
            end else if (!push_w && pop_complete_w) begin
                count_q <= count_q - 1'b1;
            end
        end
    end

    assign slot0_from_upper_w = !valid0_q[rd_ptr_q] && valid1_q[rd_ptr_q];
    assign valid0 = (count_q != '0) && (valid0_q[rd_ptr_q] || valid1_q[rd_ptr_q]);
    assign valid1 = (count_q != '0) && valid0_q[rd_ptr_q] && valid1_q[rd_ptr_q];
    assign accept = (count_q < DEPTH - 1);

    assign pc0_out = slot0_from_upper_w ? (pc_q[rd_ptr_q] + 32'h4) : pc_q[rd_ptr_q];
    assign pc1_out = pc_q[rd_ptr_q] + 32'h4;
    assign data0_out = slot0_from_upper_w ? ram_q[rd_ptr_q][WIDTH-1:(WIDTH/2)] :
                                            ram_q[rd_ptr_q][(WIDTH/2)-1:0];
    assign data1_out = ram_q[rd_ptr_q][WIDTH-1:(WIDTH/2)];

endmodule
