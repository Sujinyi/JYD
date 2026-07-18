`include "config.sv"
module Hazard(
    input  logic rst,
    input  logic clk,
    // forwarding 
    input  logic [ 4:0] rf_rd_ls1,
    input  logic [ 4:0] rf_rd_ls2,
    input  logic [ 4:0] rf_rd_wb,
    input  logic [ 0:0] rf_we_ls1,
    input  logic [ 0:0] rf_we_ls2,
    input  logic [ 0:0] rf_we_wb,
    input  logic [ 4:0] rf_rs1_ex,
    input  logic [ 4:0] rf_rs2_ex,
    input  logic [31:0] rf_wdata_ls1,
    input  logic [31:0] rf_wdata_ls2,
    input  logic [31:0] rf_wdata_wb,

    output logic [ 0:0] forward1_en,
    output logic [ 0:0] forward2_en,
    output logic [31:0] forward1_data,
    output logic [31:0] forward2_data,

    // load-use
    input  logic [ 4:0] mem_access_ex,
    input  logic [ 4:0] rf_rd_ex,
    input  logic [ 4:0] rf_rs1_if2,
    input  logic [ 4:0] rf_rs2_if2,
    input  logic [ 4:0] rf_rs1_id,
    input  logic [ 4:0] rf_rs2_id,

    // control hazard
    input  logic [31:0] pc_ex,
    input  logic [31:0] pc_wb,
    input  logic [31:0] mepc_global,
    input  logic [31:0] mtvec_global,
    input  logic [31:0] mcause_global,
    input  logic [ 2:0] priv_vec_ex,
    input  logic [ 2:0] priv_vec_wb,
    input  logic [ 0:0] is_muldiv_ex,
    input  logic [ 0:0] muldiv_busy,
    input  logic [ 0:0] muldiv_done,

    input  logic [ 0:0] predict_taken_if1,
    input  logic [ 0:0] predict_taken_ex,
    input  logic [31:0] predict_target_ex,
    input  logic [ 0:0] jump,
    input  logic [31:0] jump_target,

    output logic [ 0:0] pc_set,
    output logic [ 0:0] IF1_IF2_flush,
    output logic [ 0:0] IF2_ID_flush,
    output logic [ 0:0] ID_EX_flush,
    output logic [ 0:0] EX_LS1_flush,
    output logic [ 0:0] LS1_LS2_flush,
    output logic [ 0:0] LS2_WB_flush,

    output logic [ 0:0] pc_stall,
    output logic [ 0:0] IF1_IF2_stall,
    output logic [ 0:0] IF2_ID_stall,
    output logic [ 0:0] ID_EX_stall,

    output logic [31:0] pc_set_target
);
    // forwarding
    always_comb begin
        forward1_en = 0;
        forward2_en = 0;
        forward1_data = 0;
        forward2_data = 0;
        if (rf_we_ls1 && (rf_rd_ls1 != 5'd0) && rf_rd_ls1 == rf_rs1_ex) begin //ls1_hazard
            forward1_en = 1'b1;
            forward1_data = rf_wdata_ls1;
        end
        else if (rf_we_ls2 && (rf_rd_ls2 != 5'd0) && rf_rd_ls2 == rf_rs1_ex) begin //ls2_hazard
            forward1_en = 1'b1;
            forward1_data = rf_wdata_ls2;
        end
        else if (rf_we_wb && (rf_rd_wb != 5'd0) && rf_rd_wb == rf_rs1_ex) begin //wb_hazard
            forward1_en = 1'b1;
            forward1_data = rf_wdata_wb;
        end
        if (rf_we_ls1 && (rf_rd_ls1 != 5'd0) && rf_rd_ls1 == rf_rs2_ex) begin //ls1_hazard
            forward2_en = 1'b1;
            forward2_data = rf_wdata_ls1;
        end
        else if (rf_we_ls2 && (rf_rd_ls2 != 5'd0) && rf_rd_ls2 == rf_rs2_ex) begin //ls2_hazard
            forward2_en = 1'b1;
            forward2_data = rf_wdata_ls2;
        end
        else if (rf_we_wb && (rf_rd_wb != 5'd0) && rf_rd_wb == rf_rs2_ex) begin
            forward2_en = 1'b1;
            forward2_data = rf_wdata_wb;
        end
    end

    // load-use
    logic stall_by_load_use, flush_by_load_use;
    wire is_load_ex = mem_access_ex[`LOAD_BIT];
    logic load_use_ex,load_use_if2;
    assign load_use_ex = is_load_ex && (rf_rd_ex == rf_rs1_id || rf_rd_ex == rf_rs2_id);
    assign load_use_if2 = is_load_ex && (rf_rd_ex == rf_rs1_if2|| rf_rd_ex == rf_rs2_if2);

    assign stall_by_load_use = load_use_ex|load_use_if2;
    assign flush_by_load_use = load_use_ex|load_use_if2;

    logic stall_by_load_use_r;
    always_ff@(posedge clk) begin
        if(rst) begin
            stall_by_load_use_r <= 1'b0;
        end
        else if(load_use_ex) begin
            stall_by_load_use_r <= stall_by_load_use;
        end
        else begin
            stall_by_load_use_r <= 1'b0;
        end
    end
    // control hazard
    // A prediction is correct only when both taken/not-taken and target are correct.
    wire target_mispredicted = jump && predict_taken_ex && (predict_target_ex != jump_target);
    wire mispredicted = (predict_taken_ex ^ jump) || target_mispredicted;

    wire flush_by_priv_ex = |priv_vec_ex;
    wire flush_by_exp = |mcause_global;

    wire stall_by_muldiv = is_muldiv_ex && !muldiv_done;
    
    // We flush all instructions behind if there is a misprediction in EX.
    // If we predict in IF1 (zero-cycle), we don't need a flush on a CORRECT prediction.
    assign pc_set           = mispredicted||flush_by_priv_ex||flush_by_exp;
    assign IF1_IF2_flush    = mispredicted||flush_by_priv_ex||flush_by_exp;
    assign IF2_ID_flush     = mispredicted||flush_by_priv_ex||flush_by_exp;
    assign ID_EX_flush      = mispredicted || flush_by_load_use || flush_by_priv_ex || flush_by_exp;
    assign EX_LS1_flush     = flush_by_exp || stall_by_muldiv;
    assign LS1_LS2_flush    = flush_by_exp;
    assign LS2_WB_flush     = flush_by_exp;

    wire frontend_stall = stall_by_load_use || stall_by_load_use_r || stall_by_muldiv;
    assign pc_stall         = frontend_stall && !mispredicted;
    assign IF1_IF2_stall    = frontend_stall ;
    assign IF2_ID_stall     = frontend_stall ;
    assign ID_EX_stall      = stall_by_load_use_r||stall_by_muldiv;

    always_comb begin
        if(flush_by_exp) begin
            pc_set_target = {mtvec_global[31:2], 2'b0};
        end
        else if (flush_by_priv_ex) begin
            pc_set_target = priv_vec_ex[`MRET]? mepc_global : pc_ex + 4;
        end
        else if (jump && !predict_taken_ex) begin // Predicted not taken, but actually jump
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
