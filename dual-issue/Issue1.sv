`timescale 1ns / 1ps

module Issue #(
    parameter RESET_VAL = 32'h0
)(
    input  logic        clk,
    input  logic        rst,

    input  logic        fetch0_valid,
    input  logic [31:0] fetch0_inst,
    input  logic [31:0] fetch0_pc,
    input  logic        fetch0_inst_exec,
    input  logic        fetch0_inst_lsu,
    input  logic        fetch0_inst_branch,
    input  logic        fetch0_inst_rd_valid,

    input  logic        fetch1_valid,
    input  logic [31:0] fetch1_inst,
    input  logic [31:0] fetch1_pc,
    input  logic        fetch1_inst_exec,
    input  logic        fetch1_inst_lsu,
    input  logic        fetch1_inst_branch,
    input  logic        fetch1_inst_rd_valid,

    input  logic        branch_exec0_request,
    input  logic        branch_exec1_request,

    input  logic [31:0] wb_exec0_value,
    input  logic [31:0] wb_exec1_value,
    input  logic        wb_mem_valid,
    input  logic [31:0] wb_mem_value,

    input  logic [31:0] rf_rs1_val0,
    input  logic [31:0] rf_rs2_val0,
    input  logic [31:0] rf_rs1_val1,
    input  logic [31:0] rf_rs2_val1,

    input  logic        lsu_stall,

    output logic        fetch0_accept,
    output logic        fetch1_accept,
    output logic        exec0_valid,
    output logic        exec1_valid,
    output logic        lsu_valid,
    output logic [31:0] opcode0_inst,
    output logic [31:0] opcode0_pc,
    output logic [4:0]  opcode0_rd_idx,
    output logic [4:0]  opcode0_ra_idx,
    output logic [4:0]  opcode0_rb_idx,
    output logic [31:0] opcode0_ra_operand,
    output logic [31:0] opcode0_rb_operand,
    output logic [31:0] opcode1_inst,
    output logic [31:0] opcode1_pc,
    output logic [4:0]  opcode1_rd_idx,
    output logic [4:0]  opcode1_ra_idx,
    output logic [4:0]  opcode1_rb_idx,
    output logic [31:0] opcode1_ra_operand,
    output logic [31:0] opcode1_rb_operand,
    output logic [31:0] lsu_opcode_inst,
    output logic [31:0] lsu_opcode_pc,
    output logic [4:0]  lsu_opcode_rd_idx,
    output logic [4:0]  lsu_opcode_ra_idx,
    output logic [4:0]  lsu_opcode_rb_idx,
    output logic [31:0] lsu_opcode_ra_operand,
    output logic [31:0] lsu_opcode_rb_operand,
    output logic        exec0_hold,
    output logic        exec1_hold
);

    logic [4:0] s0_rs1;
    logic [4:0] s0_rs2;
    logic [4:0] s0_rd;
    logic [4:0] s1_rs1;
    logic [4:0] s1_rs2;
    logic [4:0] s1_rd;

    logic       branch_hit;
    logic       stall_w;
    logic       issue0_fire;
    logic       issue1_fire;

    logic [4:0] ex_rd0_q;
    logic [4:0] mem_rd0_q;
    logic       ex_we0_q;
    logic       mem_we0_q;
    logic       ex_load0_q;
    logic       mem_load0_q;
    logic [31:0] ex_result0_q;
    logic [31:0] mem_result0_q;

    logic [4:0] ex_rd1_q;
    logic [4:0] mem_rd1_q;
    logic       ex_we1_q;
    logic       mem_we1_q;

    logic s0_rs1_hit_ex0;
    logic s0_rs1_hit_mem0;
    logic s0_rs1_hit_ex1;
    logic s0_rs1_wait_ex0_load;
    logic s0_rs1_wait_mem0_load;
    logic s0_rs2_hit_ex0;
    logic s0_rs2_hit_mem0;
    logic s0_rs2_hit_ex1;
    logic s0_rs2_wait_ex0_load;
    logic s0_rs2_wait_mem0_load;
    logic s1_rs1_hit_ex0;
    logic s1_rs1_hit_mem0;
    logic s1_rs1_hit_ex1;
    logic s1_rs1_hit_s0;
    logic s1_rs1_wait_ex0_load;
    logic s1_rs1_wait_mem0_load;
    logic s1_rs2_hit_ex0;
    logic s1_rs2_hit_mem0;
    logic s1_rs2_hit_ex1;
    logic s1_rs2_hit_s0;
    logic s1_rs2_wait_ex0_load;
    logic s1_rs2_wait_mem0_load;
    logic s1_waw_on_s0;
    logic s0_hazard;
    logic s1_hazard;
    logic s0_is_exec_to_ex_pipe;
    logic s0_is_branch_to_ex_pipe;
    logic s1_is_exec_to_ex_pipe;

    assign s0_rs1 = fetch0_inst[19:15];
    assign s0_rs2 = fetch0_inst[24:20];
    assign s0_rd  = fetch0_inst[11:7];
    assign s1_rs1 = fetch1_inst[19:15];
    assign s1_rs2 = fetch1_inst[24:20];
    assign s1_rd  = fetch1_inst[11:7];

    assign branch_hit = branch_exec0_request | branch_exec1_request;
    assign exec0_hold = lsu_stall;
    assign exec1_hold = lsu_stall;
    assign stall_w = lsu_stall;

    always_ff @(posedge clk) begin
        if (rst || branch_hit) begin
            ex_rd0_q  <= 5'd0;
            mem_rd0_q <= 5'd0;
            ex_we0_q  <= 1'b0;
            mem_we0_q <= 1'b0;
            ex_load0_q <= 1'b0;
            mem_load0_q <= 1'b0;
            ex_result0_q <= 32'd0;
            mem_result0_q <= 32'd0;
            ex_rd1_q  <= 5'd0;
            mem_rd1_q <= 5'd0;
            ex_we1_q  <= 1'b0;
            mem_we1_q <= 1'b0;
        end else if (!stall_w) begin
            ex_rd0_q  <= issue0_fire ? s0_rd : 5'd0;
            ex_we0_q  <= issue0_fire ? fetch0_inst_rd_valid : 1'b0;
            ex_load0_q <= issue0_fire ? (fetch0_inst_lsu && fetch0_inst_rd_valid) : 1'b0;
            ex_rd1_q  <= issue1_fire ? s1_rd : 5'd0;
            ex_we1_q  <= issue1_fire ? fetch1_inst_rd_valid : 1'b0;

            mem_rd0_q <= ex_rd0_q;
            mem_we0_q <= ex_we0_q;
            mem_load0_q <= ex_load0_q;
            ex_result0_q <= wb_exec0_value;
            mem_result0_q <= ex_result0_q;
            mem_rd1_q <= ex_rd1_q;
            mem_we1_q <= ex_we1_q;
        end
    end

    assign s0_rs1_hit_ex0  = ex_we0_q  && !ex_load0_q  && (s0_rs1 == ex_rd0_q)  && (s0_rs1 != 5'd0);
    assign s0_rs1_hit_mem0 = mem_we0_q && mem_load0_q && wb_mem_valid &&
                             (s0_rs1 == mem_rd0_q) && (s0_rs1 != 5'd0);
    assign s0_rs1_hit_ex1  = ex_we1_q  && (s0_rs1 == ex_rd1_q)  && (s0_rs1 != 5'd0);
    assign s0_rs1_wait_ex0_load = ex_we0_q && ex_load0_q && (s0_rs1 == ex_rd0_q) && (s0_rs1 != 5'd0);
    assign s0_rs1_wait_mem0_load = mem_we0_q && mem_load0_q && !wb_mem_valid && (s0_rs1 == mem_rd0_q) && (s0_rs1 != 5'd0);

    assign s0_rs2_hit_ex0  = ex_we0_q  && !ex_load0_q  && (s0_rs2 == ex_rd0_q)  && (s0_rs2 != 5'd0);
    assign s0_rs2_hit_mem0 = mem_we0_q && mem_load0_q && wb_mem_valid &&
                             (s0_rs2 == mem_rd0_q) && (s0_rs2 != 5'd0);
    assign s0_rs2_hit_ex1  = ex_we1_q  && (s0_rs2 == ex_rd1_q)  && (s0_rs2 != 5'd0);
    assign s0_rs2_wait_ex0_load = ex_we0_q && ex_load0_q && (s0_rs2 == ex_rd0_q) && (s0_rs2 != 5'd0);
    assign s0_rs2_wait_mem0_load = mem_we0_q && mem_load0_q && !wb_mem_valid && (s0_rs2 == mem_rd0_q) && (s0_rs2 != 5'd0);

    assign s1_rs1_hit_ex0  = ex_we0_q  && !ex_load0_q  && (s1_rs1 == ex_rd0_q)  && (s1_rs1 != 5'd0);
    assign s1_rs1_hit_mem0 = mem_we0_q && mem_load0_q && wb_mem_valid &&
                             (s1_rs1 == mem_rd0_q) && (s1_rs1 != 5'd0);
    assign s1_rs1_hit_ex1  = ex_we1_q  && (s1_rs1 == ex_rd1_q)  && (s1_rs1 != 5'd0);
    assign s1_rs1_hit_s0   = fetch0_valid && (s1_rs1 == s0_rd) && (s1_rs1 != 5'd0) && fetch0_inst_rd_valid;
    assign s1_rs1_wait_ex0_load = ex_we0_q && ex_load0_q && (s1_rs1 == ex_rd0_q) && (s1_rs1 != 5'd0);
    assign s1_rs1_wait_mem0_load = mem_we0_q && mem_load0_q && !wb_mem_valid && (s1_rs1 == mem_rd0_q) && (s1_rs1 != 5'd0);

    assign s1_rs2_hit_ex0  = ex_we0_q  && !ex_load0_q  && (s1_rs2 == ex_rd0_q)  && (s1_rs2 != 5'd0);
    assign s1_rs2_hit_mem0 = mem_we0_q && mem_load0_q && wb_mem_valid &&
                             (s1_rs2 == mem_rd0_q) && (s1_rs2 != 5'd0);
    assign s1_rs2_hit_ex1  = ex_we1_q  && (s1_rs2 == ex_rd1_q)  && (s1_rs2 != 5'd0);
    assign s1_rs2_hit_s0   = fetch0_valid && (s1_rs2 == s0_rd) && (s1_rs2 != 5'd0) && fetch0_inst_rd_valid;
    assign s1_rs2_wait_ex0_load = ex_we0_q && ex_load0_q && (s1_rs2 == ex_rd0_q) && (s1_rs2 != 5'd0);
    assign s1_rs2_wait_mem0_load = mem_we0_q && mem_load0_q && !wb_mem_valid && (s1_rs2 == mem_rd0_q) && (s1_rs2 != 5'd0);

    assign s1_waw_on_s0 = fetch0_valid && fetch1_valid &&
                          (s1_rd == s0_rd) &&
                          (s1_rd != 5'd0) &&
                          fetch0_inst_rd_valid;

    assign s0_hazard = s0_rs1_wait_ex0_load || s0_rs1_wait_mem0_load ||
                       s0_rs2_wait_ex0_load || s0_rs2_wait_mem0_load;

    assign s1_hazard = s1_rs1_wait_ex0_load || s1_rs1_wait_mem0_load ||
                       s1_rs2_wait_ex0_load || s1_rs2_wait_mem0_load ||
                       s1_rs1_hit_s0   || s1_rs2_hit_s0   || s1_waw_on_s0;

    always_comb begin
        fetch0_accept = fetch0_valid && !branch_hit && !s0_hazard && !stall_w;
        fetch1_accept = fetch0_accept &&
                        fetch1_valid &&
                        !s1_hazard &&
                        fetch1_inst_exec &&
                        !fetch0_inst_branch &&
                        !fetch0_inst_lsu;
    end

    assign issue0_fire = fetch0_accept;
    assign issue1_fire = fetch1_accept;
    assign s0_is_exec_to_ex_pipe = fetch0_inst_exec;
    assign s0_is_branch_to_ex_pipe = fetch0_inst_branch;
    assign s1_is_exec_to_ex_pipe = fetch1_inst_exec;

    always_comb begin
        casez ({s0_rs1_hit_ex0, s0_rs1_hit_mem0, s0_rs1_hit_ex1})
            3'b1??: opcode0_ra_operand = wb_exec0_value;
            3'b01?: opcode0_ra_operand = mem_load0_q ? wb_mem_value : mem_result0_q;
            3'b001: opcode0_ra_operand = wb_exec1_value;
            default: opcode0_ra_operand = rf_rs1_val0;
        endcase
    end

    always_comb begin
        casez ({s0_rs2_hit_ex0, s0_rs2_hit_mem0, s0_rs2_hit_ex1})
            3'b1??: opcode0_rb_operand = wb_exec0_value;
            3'b01?: opcode0_rb_operand = mem_load0_q ? wb_mem_value : mem_result0_q;
            3'b001: opcode0_rb_operand = wb_exec1_value;
            default: opcode0_rb_operand = rf_rs2_val0;
        endcase
    end

    always_comb begin
        if (s1_rs1_hit_s0) begin
            opcode1_ra_operand = wb_exec0_value;
        end else begin
            casez ({s1_rs1_hit_ex0, s1_rs1_hit_mem0, s1_rs1_hit_ex1})
                3'b1??: opcode1_ra_operand = wb_exec0_value;
                3'b01?: opcode1_ra_operand = mem_load0_q ? wb_mem_value : mem_result0_q;
                3'b001: opcode1_ra_operand = wb_exec1_value;
                default: opcode1_ra_operand = rf_rs1_val1;
            endcase
        end
    end

    always_comb begin
        if (s1_rs2_hit_s0) begin
            opcode1_rb_operand = wb_exec0_value;
        end else begin
            casez ({s1_rs2_hit_ex0, s1_rs2_hit_mem0, s1_rs2_hit_ex1})
                3'b1??: opcode1_rb_operand = wb_exec0_value;
                3'b01?: opcode1_rb_operand = mem_load0_q ? wb_mem_value : mem_result0_q;
                3'b001: opcode1_rb_operand = wb_exec1_value;
                default: opcode1_rb_operand = rf_rs2_val1;
            endcase
        end
    end

    assign exec0_valid = fetch0_accept && (s0_is_exec_to_ex_pipe || s0_is_branch_to_ex_pipe);
    assign exec1_valid = fetch1_accept && s1_is_exec_to_ex_pipe;
    assign lsu_valid   = fetch0_accept && fetch0_inst_lsu;

    assign opcode0_inst   = fetch0_inst;
    assign opcode0_pc     = fetch0_pc;
    assign opcode0_rd_idx = s0_rd;
    assign opcode0_ra_idx = s0_rs1;
    assign opcode0_rb_idx = s0_rs2;

    assign opcode1_inst   = fetch1_inst;
    assign opcode1_pc     = fetch1_pc;
    assign opcode1_rd_idx = s1_rd;
    assign opcode1_ra_idx = s1_rs1;
    assign opcode1_rb_idx = s1_rs2;

    assign lsu_opcode_inst       = fetch0_inst;
    assign lsu_opcode_pc         = fetch0_pc;
    assign lsu_opcode_rd_idx     = s0_rd;
    assign lsu_opcode_ra_idx     = s0_rs1;
    assign lsu_opcode_rb_idx     = s0_rs2;
    assign lsu_opcode_ra_operand = opcode0_ra_operand;
    assign lsu_opcode_rb_operand = opcode0_rb_operand;

endmodule
