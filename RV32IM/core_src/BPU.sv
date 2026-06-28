module BPU (
    input  logic        clk,
    input  logic        rst,

    // Prediction interface (IF1 stage)
    input  logic [31:0] pc_if1,
    output logic        predict_taken,
    output logic [31:0] pc_to_take,
    output logic        btb_hit,

    // Update interface (EX stage)
    input  logic        update_en,
    input  logic [31:0] update_pc,
    input  logic        actual_taken,
    input  logic [31:0] actual_target,
    input  logic        update_is_ret,
    input  logic        ras_push,
    input  logic        ras_pop,
    input  logic [31:0] ras_push_addr
);

    localparam int INDEX_BITS = 8;
    localparam int ENTRY_NUM  = 1 << INDEX_BITS;
    localparam int TAG_BITS   = 32 - INDEX_BITS - 2;
    localparam int BHT_BITS   = 2;
    localparam int BTB_BITS   = 1 + TAG_BITS + 30;
    localparam int RAS_DEPTH  = 4;
    localparam int RAS_PTR_W  = $clog2(RAS_DEPTH + 1);
    localparam int RAS_INDEX_W = $clog2(RAS_DEPTH);

    (* ram_style = "distributed" *) logic [BHT_BITS-1:0] bht [0:ENTRY_NUM-1];
    (* ram_style = "distributed" *) logic [BTB_BITS-1:0] btb [0:ENTRY_NUM-1];

    logic [ENTRY_NUM-1:0] btb_valid;
    logic [31:0] ras_stack [0:RAS_DEPTH-1];
    logic [RAS_PTR_W-1:0] ras_sp;
    logic [31:0] ras_top;

    logic [INDEX_BITS-1:0] index_if1;
    logic [TAG_BITS-1:0]   tag_if1;
    logic [BHT_BITS-1:0]   bht_rdata_if1;
    logic [BTB_BITS-1:0]   btb_rdata_if1;
    logic                  btb_is_ret_if1;
    logic [TAG_BITS-1:0]   btb_tag_if1;
    logic [29:0]           btb_target_if1;
    logic                  hit_btb_if1;
    logic                  ras_valid_if1;

    logic [INDEX_BITS-1:0] index_ex;
    logic [TAG_BITS-1:0]   tag_ex;
    logic [BHT_BITS-1:0]   old_counter;
    logic [BHT_BITS-1:0]   new_counter;

    assign index_if1     = pc_if1[INDEX_BITS+1:2];
    assign tag_if1       = pc_if1[31:INDEX_BITS+2];
    assign bht_rdata_if1 = bht[index_if1];
    assign btb_rdata_if1 = btb[index_if1];
    assign {btb_is_ret_if1, btb_tag_if1, btb_target_if1} = btb_rdata_if1;
    assign hit_btb_if1   = btb_valid[index_if1] && (btb_tag_if1 == tag_if1);
    assign ras_valid_if1 = (ras_sp != 0);

    always_comb begin
        predict_taken = hit_btb_if1 && (btb_is_ret_if1 || bht_rdata_if1[1]);
        pc_to_take    = (btb_is_ret_if1 && ras_valid_if1) ? ras_top : {btb_target_if1, 2'b00};
        btb_hit       = hit_btb_if1;
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
            ras_sp    <= '0;
            ras_top   <= 32'h0;
        end else begin
            if (update_en) begin
                bht[index_ex] <= new_counter;
                if (actual_taken) begin
                    btb[index_ex] <= {update_is_ret, tag_ex, actual_target[31:2]};
                    btb_valid[index_ex] <= 1'b1;
                end
            end

            case ({ras_push, ras_pop})
                2'b10: begin
                    if (ras_sp < RAS_PTR_W'(RAS_DEPTH)) begin
                        ras_stack[ras_sp[RAS_INDEX_W-1:0]] <= ras_push_addr;
                        ras_sp <= ras_sp + 1'b1;
                    end else begin
                        ras_stack[RAS_DEPTH-1] <= ras_push_addr;
                    end
                    ras_top <= ras_push_addr;
                end
                2'b01: begin
                    if (ras_sp > 1) begin
                        ras_sp <= ras_sp - 1'b1;
                        ras_top <= ras_stack[ras_sp-2];
                    end else if (ras_sp == 1) begin
                        ras_sp <= '0;
                        ras_top <= 32'h0;
                    end
                end
                2'b11: begin
                    if (ras_sp == 0) begin
                        ras_stack[0] <= ras_push_addr;
                        ras_sp <= RAS_PTR_W'(1);
                    end else begin
                        ras_stack[ras_sp-1] <= ras_push_addr;
                    end
                    ras_top <= ras_push_addr;
                end
                default: begin
                end
            endcase
        end
    end

endmodule
