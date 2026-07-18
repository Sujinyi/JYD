`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// CDC-fixed perip_bridge
//
// Key changes:
// 1) virtual_sw_input / virtual_key_input are synchronized into clk domain
// 2) LED / SEG write data are transferred from clk domain to cnt_clk domain
//    with a 1-entry request/ack handshake (latest value is preserved)
// 3) display_seg now runs in cnt_clk domain, so virtual_seg_output and
//    virtual_led_output are both cnt_clk-domain signals for twin_controller
//////////////////////////////////////////////////////////////////////////////////

module perip_bridge(
    input  logic         clk,
    input  logic         cnt_clk,
    input  logic         rst,

    input  logic [31:0]  perip_addr,
    input  logic [31:0]  perip_wdata,
    input  logic [3:0]   perip_wstrb,
    output logic [31:0]  perip_rdata,

    input  logic [63:0]  virtual_sw_input,
    input  logic [7:0]   virtual_key_input,

    output logic [39:0]  virtual_seg_output,
    output logic [31:0]  virtual_led_output
);
    localparam DRAM_ADDR_START = 32'h8010_0000;
    localparam DRAM_ADDR_END   = 32'h8013_FFFF;
    localparam SW0_ADDR        = 32'h8020_0000;  // sw[31:0]
    localparam SW1_ADDR        = 32'h8020_0004;  // sw[63:32]
    localparam KEY_ADDR        = 32'h8020_0010;  // key[7:0]
    localparam SEG_ADDR        = 32'h8020_0020;  // seg data register
    localparam LED_ADDR        = 32'h8020_0040;  // led[31:0]
    localparam CNT_ADDR        = 32'h8020_0050;  // counter

    logic [31:0] LED_cpu;
    logic [31:0] seg_wdata_cpu;
    logic [31:0] LED_cnt;
    logic [31:0] seg_wdata_cnt;
    logic [39:0] seg_output_cnt;

    logic [31:0] cnt_rdata, mmio_rdata, dram_rdata;
    logic [31:0] perip_addr_reg;

    // ------------------------------------------------------------------------
    // CPU-domain read address register
    // ------------------------------------------------------------------------
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            perip_addr_reg <= 32'h0;
        end else begin
            perip_addr_reg <= perip_addr;
        end
    end

    wire perip_wen       = |perip_wstrb;
    wire cnt_addr_whit   = (perip_addr == CNT_ADDR);
    wire cnt_start_req   = perip_wen && cnt_addr_whit && (perip_wdata == 32'h8000_0000);
    wire cnt_stop_req    = perip_wen && cnt_addr_whit && (perip_wdata == 32'hFFFF_FFFF);

    wire dram_addr_whit  = perip_addr[31:18]     == 14'h2004;
    wire dram_addr_rhit  = perip_addr_reg[31:18] == 14'h2004;

    // ------------------------------------------------------------------------
    // cnt_clk -> clk : synchronize slow virtual inputs for CPU MMIO reads
    // ------------------------------------------------------------------------
    (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *) logic [63:0] sw_meta;
    (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *) logic [63:0] sw_sync;
    (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *) logic [7:0]  key_meta;
    (* ASYNC_REG = "TRUE", SHREG_EXTRACT = "NO" *) logic [7:0]  key_sync;

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            sw_meta  <= 64'd0;
            sw_sync  <= 64'd0;
            key_meta <= 8'd0;
            key_sync <= 8'd0;
        end else begin
            sw_meta  <= virtual_sw_input;
            sw_sync  <= sw_meta;
            key_meta <= virtual_key_input;
            key_sync <= key_meta;
        end
    end

    // ------------------------------------------------------------------------
    // clk -> cnt_clk : LED one-entry mailbox with req/ack handshake
    // ------------------------------------------------------------------------
    logic [31:0] led_tx_data_cpu;
    logic [31:0] led_sent_value_cpu;
    logic        led_req_toggle_cpu;
    logic        led_ack_meta_cpu;
    logic        led_ack_sync_cpu;
    logic        led_req_meta_cnt;
    logic        led_req_sync_cnt;
    logic        led_req_sync_d_cnt;
    logic        led_ack_toggle_cnt;

    wire led_channel_idle_cpu = (led_req_toggle_cpu == led_ack_sync_cpu);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            LED_cpu           <= 32'd0;
            led_tx_data_cpu   <= 32'd0;
            led_sent_value_cpu<= 32'd0;
            led_req_toggle_cpu<= 1'b0;
            led_ack_meta_cpu  <= 1'b0;
            led_ack_sync_cpu  <= 1'b0;
        end else begin
            led_ack_meta_cpu <= led_ack_toggle_cnt;
            led_ack_sync_cpu <= led_ack_meta_cpu;

            if (perip_wen && (perip_addr == LED_ADDR)) begin
                LED_cpu <= perip_wdata;
                if (led_channel_idle_cpu) begin
                    led_tx_data_cpu    <= perip_wdata;
                    led_sent_value_cpu <= perip_wdata;
                    led_req_toggle_cpu <= ~led_req_toggle_cpu;
                end
            end else if (led_channel_idle_cpu && (LED_cpu != led_sent_value_cpu)) begin
                led_tx_data_cpu    <= LED_cpu;
                led_sent_value_cpu <= LED_cpu;
                led_req_toggle_cpu <= ~led_req_toggle_cpu;
            end
        end
    end

    always_ff @(posedge cnt_clk or posedge rst) begin
        if (rst) begin
            led_req_meta_cnt   <= 1'b0;
            led_req_sync_cnt   <= 1'b0;
            led_req_sync_d_cnt <= 1'b0;
            led_ack_toggle_cnt <= 1'b0;
            LED_cnt            <= 32'd0;
        end else begin
            led_req_meta_cnt   <= led_req_toggle_cpu;
            led_req_sync_cnt   <= led_req_meta_cnt;
            led_req_sync_d_cnt <= led_req_sync_cnt;

            if (led_req_sync_cnt ^ led_req_sync_d_cnt) begin
                LED_cnt            <= led_tx_data_cpu;
                led_ack_toggle_cnt <= ~led_ack_toggle_cnt;
            end
        end
    end

    // ------------------------------------------------------------------------
    // clk -> cnt_clk : SEG one-entry mailbox with req/ack handshake
    // ------------------------------------------------------------------------
    logic [31:0] seg_tx_data_cpu;
    logic [31:0] seg_sent_value_cpu;
    logic        seg_req_toggle_cpu;
    logic        seg_ack_meta_cpu;
    logic        seg_ack_sync_cpu;
    logic        seg_req_meta_cnt;
    logic        seg_req_sync_cnt;
    logic        seg_req_sync_d_cnt;
    logic        seg_ack_toggle_cnt;

    wire seg_channel_idle_cpu = (seg_req_toggle_cpu == seg_ack_sync_cpu);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            seg_wdata_cpu      <= 32'd0;
            seg_tx_data_cpu    <= 32'd0;
            seg_sent_value_cpu <= 32'd0;
            seg_req_toggle_cpu <= 1'b0;
            seg_ack_meta_cpu   <= 1'b0;
            seg_ack_sync_cpu   <= 1'b0;
        end else begin
            seg_ack_meta_cpu <= seg_ack_toggle_cnt;
            seg_ack_sync_cpu <= seg_ack_meta_cpu;

            if (perip_wen && (perip_addr == SEG_ADDR)) begin
                seg_wdata_cpu <= perip_wdata;
                if (seg_channel_idle_cpu) begin
                    seg_tx_data_cpu    <= perip_wdata;
                    seg_sent_value_cpu <= perip_wdata;
                    seg_req_toggle_cpu <= ~seg_req_toggle_cpu;
                end
            end else if (seg_channel_idle_cpu && (seg_wdata_cpu != seg_sent_value_cpu)) begin
                seg_tx_data_cpu    <= seg_wdata_cpu;
                seg_sent_value_cpu <= seg_wdata_cpu;
                seg_req_toggle_cpu <= ~seg_req_toggle_cpu;
            end
        end
    end

    always_ff @(posedge cnt_clk or posedge rst) begin
        if (rst) begin
            seg_req_meta_cnt   <= 1'b0;
            seg_req_sync_cnt   <= 1'b0;
            seg_req_sync_d_cnt <= 1'b0;
            seg_ack_toggle_cnt <= 1'b0;
            seg_wdata_cnt      <= 32'd0;
        end else begin
            seg_req_meta_cnt   <= seg_req_toggle_cpu;
            seg_req_sync_cnt   <= seg_req_meta_cnt;
            seg_req_sync_d_cnt <= seg_req_sync_cnt;

            if (seg_req_sync_cnt ^ seg_req_sync_d_cnt) begin
                seg_wdata_cnt      <= seg_tx_data_cpu;
                seg_ack_toggle_cnt <= ~seg_ack_toggle_cnt;
            end
        end
    end

    // ------------------------------------------------------------------------
    // MMIO read process (clk domain)
    // ------------------------------------------------------------------------
    always_comb begin
        if (~perip_wen) begin
            case (perip_addr_reg)
                SW0_ADDR:  mmio_rdata = sw_sync[31:0];
                SW1_ADDR:  mmio_rdata = sw_sync[63:32];
                KEY_ADDR:  mmio_rdata = {24'd0, key_sync};
                SEG_ADDR:  mmio_rdata = seg_wdata_cpu;
                LED_ADDR:  mmio_rdata = LED_cpu;
                default:   mmio_rdata = 32'hDEAD_BEEF;
            endcase
        end else begin
            mmio_rdata = 32'h0;
        end
    end

    // ------------------------------------------------------------------------
    // display_seg now runs in cnt_clk domain
    // ------------------------------------------------------------------------
    display_seg seg_driver (
        .clk    (cnt_clk),
        .rst    (rst),
        .s      (seg_wdata_cnt),
        .seg1   (seg_output_cnt[6:0]),
        .seg2   (seg_output_cnt[16:10]),
        .seg3   (seg_output_cnt[26:20]),
        .seg4   (seg_output_cnt[36:30]),
        .ans    ({seg_output_cnt[39:38], seg_output_cnt[29:28], seg_output_cnt[19:18], seg_output_cnt[9:8]})
    );

    assign seg_output_cnt[7]  = 1'b0;
    assign seg_output_cnt[17] = 1'b0;
    assign seg_output_cnt[27] = 1'b0;
    assign seg_output_cnt[37] = 1'b0;

    // ------------------------------------------------------------------------
    // DRAM (clk domain)
    // ------------------------------------------------------------------------
    DRAM Mem_DRAM (
        .clka  (clk),
        .wea   (perip_wstrb & {4{dram_addr_whit}}),
        .addra (perip_addr[17:2]),
        .dina  (perip_wdata),
        .douta (dram_rdata)
    );

    // ------------------------------------------------------------------------
    // Counter bridge
    // ------------------------------------------------------------------------
    counter counter_inst (
        .cpu_clk     (clk),
        .cnt_clk     (cnt_clk),
        .rst         (rst),
        .start_req   (cnt_start_req),
        .stop_req    (cnt_stop_req),
        .perip_rdata (cnt_rdata)
    );

    always_comb begin
        unique case (1'b1)
            (perip_addr_reg == SW0_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == SW1_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == KEY_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == SEG_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == LED_ADDR): perip_rdata = mmio_rdata;
            dram_addr_rhit:               perip_rdata = dram_rdata;
            (perip_addr_reg == CNT_ADDR): perip_rdata = cnt_rdata;
            default:                      perip_rdata = 32'h0;
        endcase
    end

    assign virtual_led_output = LED_cnt;
    assign virtual_seg_output = seg_output_cnt;

endmodule
