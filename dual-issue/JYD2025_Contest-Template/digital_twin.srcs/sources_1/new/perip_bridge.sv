`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/04/22 10:25:24
// Design Name: 
// Module Name: perip_bridge
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module perip_bridge(
    input  logic         clk				,
    input  logic         cnt_clk			,
    input  logic         rst                ,

    input  logic [31:0]  perip_addr			,
    input  logic [31:0]  perip_wdata		,
	input  logic [3:0]	 perip_wstrb			,  // 4-bit 字节写使能 (from CPU bus_wen)
    output logic [31:0]  perip_rdata		,

    input  logic [63:0]  virtual_sw_input	,
    input  logic [7:0]   virtual_key_input	,	

	output logic [39:0]  virtual_seg_output	,
    output logic [31:0]  virtual_led_output
);
    localparam DRAM_ADDR_START = 32'h8010_0000;
    localparam DRAM_ADDR_END   = 32'h8013_FFFF;
    localparam SW0_ADDR  = 32'h8020_0000;  // sw[31:0]
    localparam SW1_ADDR  = 32'h8020_0004;  // sw[63:32]
    localparam KEY_ADDR  = 32'h8020_0010;  // key[7:0]
    localparam SEG_ADDR  = 32'h8020_0020;  // seg
    localparam LED_ADDR  = 32'h8020_0040;  // led[31:0]
    localparam CNT_ADDR  = 32'h8020_0050;  // counter

    logic [31:0] LED;
    logic [31:0] seg_wdata, cnt_rdata, mmio_rdata, dram_rdata;
    logic [39:0] seg_output;

    logic [31:0] perip_addr_reg;
    always_ff @(posedge clk) begin 
        if(rst) begin
            perip_addr_reg <= 32'h0;
        end else begin
            perip_addr_reg <= perip_addr;  // 每拍都锁存，读写都需要
        end
    end


    // 内部生成 1-bit 写使能
    wire perip_wen = |perip_wstrb;

    // 写入DRAM时的地址范围判断（EX阶段，不打拍）
    wire dram_addr_whit = perip_addr[31:18] == 14'h2004;
    wire dram_addr_rhit = perip_addr_reg[31:18] == 14'h2004;

    // we don't care perip_mask in LED, SEG, SW & KEY, only care in DRAM
    // write process
    always_ff @(posedge clk) begin
        if (perip_wen) begin
            case (perip_addr)
                LED_ADDR:   LED <= perip_wdata;
                SEG_ADDR:   seg_wdata <= perip_wdata;
            endcase
        end
    end

    // read process: in one cycle
    always_comb begin
        if (~perip_wen) begin
            case (perip_addr_reg)
                SW0_ADDR:  mmio_rdata = virtual_sw_input[31:0];
                SW1_ADDR:  mmio_rdata = virtual_sw_input[63:32];
                KEY_ADDR:  mmio_rdata = {24'd0, virtual_key_input};
                SEG_ADDR:  mmio_rdata = seg_wdata;
                default:   mmio_rdata = 32'hDEAD_BEEF;
            endcase
        end else begin
            mmio_rdata = 32'h0;
        end
    end

    // seg driver
    display_seg seg_driver (
        .clk    (clk),
        .rst    (rst),
        .s      (seg_wdata),
        .seg1   (seg_output[6:0]),
        .seg2   (seg_output[16:10]),
        .seg3   (seg_output[26:20]),
        .seg4   (seg_output[36:30]),
        .ans    ({seg_output[39:38], seg_output[29:28], seg_output[19:18], seg_output[9:8]})
    ); 
   
    assign seg_output[7]  = 0;
    assign seg_output[17] = 0;
    assign seg_output[27] = 0;
    assign seg_output[37] = 0;
    

    // dram rw (使用 Byte Write Enable)
    dram_driver dram_driver_inst (
        .clk				(clk),
        .perip_addr			(perip_addr[17:0]),
        .perip_wdata		(perip_wdata),
        .dram_wstrb			(perip_wstrb & {4{dram_addr_whit}}),  // 4-bit 字节写使能
        .perip_rdata		(dram_rdata)
    );

    // counter rw
    counter counter_inst (
        .clk				(cnt_clk),
        .rst                (rst),
        .perip_wdata		(perip_wdata),
        .cnt_wen 			(perip_wen & (perip_addr == CNT_ADDR)),
        .perip_rdata		(cnt_rdata)
    );

    always_comb begin
        unique case (1'b1)
            (perip_addr_reg == SW0_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == SW1_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == KEY_ADDR): perip_rdata = mmio_rdata;
            (perip_addr_reg == SEG_ADDR): perip_rdata = mmio_rdata;
            dram_addr_rhit:               perip_rdata = dram_rdata;
            (perip_addr_reg == CNT_ADDR): perip_rdata = cnt_rdata;
            default:                      perip_rdata = 32'h0;
        endcase
    end
    
    assign virtual_led_output = LED;
    assign virtual_seg_output = seg_output;

endmodule
