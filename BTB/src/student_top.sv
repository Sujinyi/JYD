`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/16/2025 06:21:13 PM
// Design Name: 
// Module Name: student_top
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


module student_top#(
    parameter                           P_SW_CNT            = 64,
    parameter                           P_LED_CNT           = 32,
    parameter                           P_SEG_CNT           = 40,
    parameter                           P_KEY_CNT           = 8
) (
    input                                       w_cpu_clk     ,
    input                                       w_clk_50Mhz   ,
    input                                       w_clk_rst     ,
    input  [P_KEY_CNT - 1:0]                    virtual_key   ,
    input  [P_SW_CNT  - 1:0]                    virtual_sw    ,

    output [P_LED_CNT - 1:0]                    virtual_led   ,
    output [P_SEG_CNT - 1:0]                    virtual_seg   
);

    // IROM
    logic irom_en, irom_rst;
    logic [31:0] pc;
    logic [11:0] inst_addr;
    logic [31:0] instruction;

    // perip
    logic [31:0] perip_addr, perip_wdata, perip_rdata;
    logic [3:0] perip_wstrb;

    // 16KB = 2^12 * 32bit
    assign inst_addr = pc[13:2];

    CPU Core_cpu (
        .cpu_rst            (w_clk_rst),
        .cpu_clk            (w_cpu_clk),

        // Interface to IROM
        .irom_en            (irom_en),
        .irom_rst           (irom_rst),
        .irom_addr          (pc),             
        .irom_rdata          (instruction),   

        // Interface to DRAM & periphera
        .bus_addr         (perip_addr),         
        .bus_wen          (perip_wstrb),   
        .bus_wdata        (perip_wdata),    
        .bus_rdata        (perip_rdata)     
    );

    IROM Mem_IROM (
        .clka(w_cpu_clk),            // input wire clka
        .rsta(irom_rst),            // input wire rsta
        .ena(irom_en),              // input wire ena
        .addra(inst_addr),          // input wire [11 : 0] addra
        .douta(instruction),          // output wire [31 : 0] douta
        .rsta_busy()  // output wire rsta_busy
    );
    
    perip_bridge bridge_inst (
        .clk				(w_cpu_clk),
        .cnt_clk            (w_clk_50Mhz),
        .rst                (w_clk_rst),
        .perip_addr			(perip_addr),
        .perip_wdata		(perip_wdata),
        .perip_wstrb		(perip_wstrb),
        .perip_rdata		(perip_rdata),
        .virtual_sw_input	(virtual_sw),
        .virtual_key_input	(virtual_key),	
        .virtual_seg_output	(virtual_seg),
        .virtual_led_output (virtual_led)
    );

endmodule
