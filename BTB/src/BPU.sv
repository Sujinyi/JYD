`include "config.sv"
module BPU (
    input  logic        clk,
    input  logic        rst,

    // Prediction Interface (IF1 Stage)
    input  logic [31:0] pc_if1,
    output logic        predict_taken,
    output logic [31:0] pc_to_take,

    // Update Interface (EX Stage)
    input  logic        update_en,
    input  logic [31:0] update_pc,
    input  logic        actual_taken,
    input  logic [31:0] actual_target
);

    localparam int INDEX_BITS = 6;
    localparam int ENTRY_NUM  = 1 << INDEX_BITS;
    localparam int TAG_BITS   = 32 - INDEX_BITS - 2;//24
    localparam int BHT_BITS   = 2;
    localparam int BTB_BITS   = TAG_BITS + 30;//54

    // Keep the predictor in LUTRAM so IF1 can still use asynchronous reads.
    (* ram_style = "distributed" *) logic [BHT_BITS-1:0] bht [0:ENTRY_NUM-1];
    (* ram_style = "distributed" *) logic [BTB_BITS-1:0] btb [0:ENTRY_NUM-1];

    // Valid bits are kept separately so reset only touches a tiny register bank.
    logic [ENTRY_NUM-1:0] btb_valid;

    logic [INDEX_BITS-1:0] index_if1;
    logic [TAG_BITS-1:0]   tag_if1;
    logic [BHT_BITS-1:0]   bht_rdata_if1;
    logic [BTB_BITS-1:0]   btb_rdata_if1;
    logic [TAG_BITS-1:0]   btb_tag_if1;
    logic [29:0]           btb_target_if1;
    logic                  hit_btb_if1;

    logic [INDEX_BITS-1:0] index_ex;
    logic [TAG_BITS-1:0]   tag_ex;
    logic [BHT_BITS-1:0]   old_counter;
    logic [BHT_BITS-1:0]   new_counter;

    assign index_if1     = pc_if1[INDEX_BITS+1:2];
    assign tag_if1       = pc_if1[31:INDEX_BITS+2];
    assign bht_rdata_if1 = bht[index_if1];
    assign btb_rdata_if1 = btb[index_if1];
    assign btb_tag_if1   = btb_rdata_if1[BTB_BITS-1:30];
    assign btb_target_if1 = btb_rdata_if1[29:0];//pc[31:2] stored in BTB, so target is also aligned to 4 bytes, we can ignore the last 2 bits
    assign hit_btb_if1   = btb_valid[index_if1] && (btb_tag_if1 == tag_if1);

    always_comb begin
        predict_taken = hit_btb_if1 && bht_rdata_if1[1];
        pc_to_take    = {btb_target_if1, 2'b00};
    end

    assign index_ex = update_pc[INDEX_BITS+1:2];
    assign tag_ex   = update_pc[31:INDEX_BITS+2];

    always_comb begin
        old_counter = btb_valid[index_ex] ? bht[index_ex] : 2'b01;

        if (actual_taken) begin
            case (old_counter)
                2'b00:   new_counter = 2'b01;
                2'b01:   new_counter = 2'b10;
                2'b10:   new_counter = 2'b11;
                default: new_counter = 2'b11;
            endcase
        end else begin
            case (old_counter)
                2'b11:   new_counter = 2'b10;
                2'b10:   new_counter = 2'b01;
                2'b01:   new_counter = 2'b00;
                default: new_counter = 2'b00;
            endcase
        end
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            btb_valid <= '0;
        end else if (update_en) begin
            bht[index_ex] <= new_counter;
            if (actual_taken) begin
                btb[index_ex]       <= {tag_ex, actual_target[31:2]};
                btb_valid[index_ex] <= 1'b1;
            end
        end
    end

endmodule
