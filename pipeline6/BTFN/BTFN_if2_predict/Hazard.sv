`include "config.sv"
module Hazard(
    // forwarding 
    input  logic [ 4:0] rf_rd_ls,
    input  logic [ 4:0] rf_rd_wb,
    input  logic [ 0:0] rf_we_ls,
    input  logic [ 0:0] rf_we_wb,
    input  logic [ 4:0] rf_rs1_ex,
    input  logic [ 4:0] rf_rs2_ex,
    input  logic [31:0] rf_wdata_tmp_ls,
    input  logic [31:0] rf_wdata_wb,

    output logic [ 0:0] forward1_en,
    output logic [ 0:0] forward2_en,
    output logic [31:0] forward1_data,
    output logic [31:0] forward2_data,

    // load-use
    input  logic [ 4:0] mem_access_ex,
    input  logic [ 4:0] rf_rd_ex,
    input  logic [ 4:0] rf_rs1_id,
    input  logic [ 4:0] rf_rs2_id,

    // control hazard
    input  logic [31:0] pc_ex,
    input  logic [ 0:0] branch_taken_if2,
    input  logic [ 0:0] branch_taken_id,
    input  logic [ 0:0] branch_taken_ex,
    input  logic [ 0:0] jump,
    input  logic [31:0] jump_target,

    output logic [ 0:0] pc_set,
    output logic [ 0:0] IF1_IF2_flush,
    output logic [ 0:0] IF2_ID_flush,
    output logic [ 0:0] ID_EX_flush,

    output logic [ 0:0] pc_stall,
    output logic [ 0:0] IF1_IF2_stall,
    output logic [ 0:0] IF2_ID_stall,

    output logic [31:0] pc_set_target
);
    // forwarding
    always_comb begin
        forward1_en = 0;
        forward2_en = 0;
        forward1_data = 0;
        forward2_data = 0;
        if (rf_we_ls && (rf_rd_ls != 5'd0) && rf_rd_ls == rf_rs1_ex) begin //ls_hazard
            forward1_en = 1'b1;
            forward1_data = rf_wdata_tmp_ls;
        end
        else if (rf_we_wb && (rf_rd_wb != 5'd0) && rf_rd_wb == rf_rs1_ex) begin //wb_hazard
            forward1_en = 1'b1;
            forward1_data = rf_wdata_wb;
        end
        if (rf_we_ls && (rf_rd_ls != 5'd0) && rf_rd_ls == rf_rs2_ex) begin
            forward2_en = 1'b1;
            forward2_data = rf_wdata_tmp_ls;
        end
        else if (rf_we_wb && (rf_rd_wb != 5'd0) && rf_rd_wb == rf_rs2_ex) begin
            forward2_en = 1'b1;
            forward2_data = rf_wdata_wb;
        end
    end

    // load-use
    logic stall_by_load_use, flush_by_load_use;
    wire is_load_ex = mem_access_ex[`LOAD_BIT];
    logic load_use_hazard;
    assign load_use_hazard = is_load_ex && (rf_rd_ex == rf_rs1_id || rf_rd_ex == rf_rs2_id);
    always_comb begin
        if (load_use_hazard) begin
            stall_by_load_use = 1'b1;
            flush_by_load_use = 1'b1;
        end
        else begin
            stall_by_load_use = 1'b0;
            flush_by_load_use = 1'b0;
        end
    end

    // control hazard
    wire flush_by_jump = (branch_taken_ex&&jump) ? 1'b0 :
                        (branch_taken_ex&&!jump) ? 1'b1 : 
                        (!branch_taken_ex&&jump) ? 1'b1 : 1'b0;
    // Lab3 TODO: generate pc_set, IF1_IF2_flush, IF2_ID_flush, ID_EX_flush, EX_LS_flush, LS_WB_flush
    assign pc_set           = branch_taken_ex^jump;
    assign IF1_IF2_flush    = flush_by_jump|branch_taken_if2;
    assign IF2_ID_flush     = flush_by_jump;
    assign ID_EX_flush      = flush_by_jump|flush_by_load_use;

    // Lab3 TODO: generate pc_stall, IF1_IF2_stall, IF2_ID_stall, ID_EX_stall, EX_LS_stall, LS_WB_stall
    assign pc_stall         = stall_by_load_use;
    assign IF1_IF2_stall    = stall_by_load_use;
    assign IF2_ID_stall     = stall_by_load_use;

    always_comb begin
        pc_set_target = jump_target;
        if (branch_taken_ex&&!jump) begin
            pc_set_target = pc_ex+4;
        end
        else if (!branch_taken_ex&&jump) begin
            pc_set_target = jump_target;
        end
        else begin
            pc_set_target = jump_target;
        end
    end

endmodule