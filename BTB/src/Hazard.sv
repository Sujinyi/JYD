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

    input  logic [ 0:0] predict_taken_if1,
    input  logic [ 0:0] predict_taken_ex,
    input  logic [31:0] predict_target_ex,
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
    // A prediction is correct only when both taken/not-taken and target are correct.
    wire target_mispredicted = jump && predict_taken_ex && (predict_target_ex != jump_target);
    wire mispredicted = (predict_taken_ex ^ jump) || target_mispredicted;
    
    // We flush all instructions behind if there is a misprediction in EX.
    // If we predict in IF1 (zero-cycle), we don't need a flush on a CORRECT prediction.
    assign pc_set           = mispredicted;
    assign IF1_IF2_flush    = mispredicted;
    assign IF2_ID_flush     = mispredicted;
    assign ID_EX_flush      = mispredicted | flush_by_load_use;

    assign pc_stall         = stall_by_load_use && !mispredicted;
    assign IF1_IF2_stall    = stall_by_load_use && !mispredicted;
    assign IF2_ID_stall     = stall_by_load_use && !mispredicted;

    always_comb begin
        if (jump && !predict_taken_ex) begin // Predicted not taken, but actually jump
            pc_set_target = jump_target;
        end
        else if (!jump && predict_taken_ex) begin // Predicted taken, but actually didn't jump
            pc_set_target = pc_ex + 4;
        end
        else begin
            pc_set_target = jump_target; // Default (shouldn't matter if mispredicted is 0)
        end
    end

endmodule