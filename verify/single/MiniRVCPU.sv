`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// Create Date: 2024/04/24 10:11:33
// Design Name: 
// Module Name: MiniRVCPU
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

module miniRV_SoC (
    input  logic         fpga_rst,   // High active
    input  logic         fpga_clk,

    output logic         debug_wb_have_inst, // 当前时钟周期是否有指令写回 (对单周期CPU，可在复位后恒置1)
    output logic [31:0]  debug_wb_pc,        // 当前写回的指令的PC (若wb_have_inst=0，此项可为任意值)
    output               debug_wb_ena,       // 指令写回时，寄存器堆的写使能 (若wb_have_inst=0，此项可为任意值)
    output logic [ 4:0]  debug_wb_reg,       // 指令写回时，写入的寄存器号 (若wb_ena或wb_have_inst=0，此项可为任意值)
    output logic [31:0]  debug_wb_value      // 指令写回时，写入寄存器的值 (若wb_ena或wb_have_inst=0，此项可为任意值)
);

    logic cpu_clk;
    assign cpu_clk = fpga_clk; // 直接使用FPGA时钟
    logic [31:0] i_rdata;
    logic [31:0] i_addr; 
    logic [31:0] bus_rdata;
    logic [31:0] bus_addr;
    logic [31:0] bus_wdata;
    logic [ 3:0] bus_wen;


    myCPU Core_cpu (
        .cpu_rst            (fpga_rst),
        .cpu_clk            (fpga_clk),

        // Interface to IROM
        .irom_rdata         (i_rdata),//irom的输出接cpu的输入
        .irom_addr          (i_addr),//cpu的输出接irom的输入
        // Interface to DRAM
        .bus_rdata         (bus_rdata),
        .bus_addr          (bus_addr),
        .bus_wdata         (bus_wdata),
        .bus_wen           (bus_wen),
        
        .debug_wb_have_inst (debug_wb_have_inst),
        .debug_wb_pc        (debug_wb_pc),
        .debug_wb_ena       (debug_wb_ena),
        .debug_wb_reg       (debug_wb_reg),
        .debug_wb_value     (debug_wb_value)

    );
    
    // IROM 直接和CPU交互
    // IP核通常配置为 32位宽。如果 IP 的地址线是 [15:0]，直接连接即可
    IROM Mem_IROM (
        .a   (i_addr[15:2]), 
        .spo (i_rdata)
    );


    logic dram_clk;
    logic [13:0] d_addr;
    logic [31:0] d_rdata;
    logic [ 3:0] d_wen;
    logic [31:0] d_wdata;

    
    Bridge u_Bridge (
        .rst_from_cpu (fpga_rst),
        .clk_from_cpu (fpga_clk),
        .addr_from_cpu(bus_addr),
        .wen_from_cpu (bus_wen), 
        .wdata_from_cpu(bus_wdata),//CPU输出数据和写使能接入Bridge
        .rdata_to_cpu (bus_rdata), //Bridge输出数据接CPU输入

        .clk_to_dram (dram_clk),
        .addr_to_dram(d_addr), 
        .rdata_from_dram(d_rdata),
        .wen_to_dram(d_wen), 
        .wdata_to_dram(d_wdata),    

        //下列外设在TRACE中忽略，悬空即可
        .rst_to_dig(),
        .clk_to_dig(),
        .addr_to_dig(), 
        .rdata_from_dig(), 
        .wen_to_dig(), 
        .wdata_to_dig(), 

        .rst_to_led(),
        .clk_to_led(),
        .addr_to_led(), 
        .rdata_from_led(), 
        .wen_to_led(), 
        .wdata_to_led(),  

        .addr_to_sw(), 
        .rdata_from_sw(),

        .addr_to_key(), 
        .rdata_from_key()
    );  


    // DRAM 通过Bridge与CPU交互
    DRAM Mem_DRAM (
        .clk (cpu_clk),
        .a   (d_addr), 
        .spo (d_rdata),
        .we  (d_wen),
        .d   (d_wdata)
        /*
        .a   (bus_addr[15:2]), // 16KB DRAM，地址线 [13:0]，直接连接即可
        .spo (bus_rdata),
        .we  (bus_wen),
        .d   (bus_wdata)
        */
    );

endmodule
