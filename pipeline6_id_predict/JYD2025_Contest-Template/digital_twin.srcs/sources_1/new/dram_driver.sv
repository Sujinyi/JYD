`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// dram_driver - BRAM Byte Write Enable 版本
// 
// 改动说明：
//   - 去掉了 perip_mask 和 sb/sh 的 Read-Modify-Write 逻辑
//   - 直接使用 BRAM 的 4-bit wea (Byte Write Enable)
//   - CPU 的 Write_Ctrl 已经做好了字节复制，这里只需透传
//   - 读操作始终返回完整 32-bit word，由 CPU 的 Read_Ctrl 做截取
//////////////////////////////////////////////////////////////////////////////////

module dram_driver(
    input  logic         clk,
    input  logic [17:0]  perip_addr,
    input  logic [31:0]  perip_wdata,
    input  logic [3:0]   dram_wstrb,        // 4-bit 字节写使能
    output logic [31:0]  perip_rdata
);
    logic [15:0] dram_addr;
    logic [31:0] dram_rdata_raw;

    assign dram_addr = perip_addr[17:2];
    assign perip_rdata = dram_rdata_raw;    // 读操作：直接返回完整字

    DRAM your_instance_name (
        .clka(clk),                // input wire clka
        .wea(dram_wstrb),          // input wire [3 : 0] wea  (Byte Write Enable)
        .addra(dram_addr),         // input wire [15 : 0] addra
        .dina(perip_wdata),        // input wire [31 : 0] dina (CPU已做字节复制)
        .douta(dram_rdata_raw)     // output wire [31 : 0] douta
    );

endmodule
