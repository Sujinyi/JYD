`timescale 1ns / 1ps

module miniRV_SoC (
    input  logic         fpga_rst,
    input  logic         fpga_clk,

    output logic         debug_wb_have_inst,
    output logic [31:0]  debug_wb_pc,
    output logic         debug_wb_ena,
    output logic [ 4:0]  debug_wb_reg,
    output logic [31:0]  debug_wb_value,

    output logic         debug_wb_have_inst_1,
    output logic [31:0]  debug_wb_pc_1,
    output logic         debug_wb_ena_1,
    output logic [ 4:0]  debug_wb_reg_1,
    output logic [31:0]  debug_wb_value_1
);

    logic        i_rd_en;
    logic        i_flush;
    logic [63:0] i_rdata;
    logic [31:0] i_addr;
    logic [31:0] d_addr;
    logic [31:0] d_rdata;
    logic [ 3:0] d_wen;
    logic [31:0] d_wdata;

    CORE Core_cpu (
        .clk                 (fpga_clk),
        .rst                 (fpga_rst),
        .irom_addr           (i_addr),
        .irom_inst           (i_rdata),
        .irom_rd_en          (i_rd_en),
        .irom_flush          (i_flush),
        .dram_addr           (d_addr),
        .dram_data_wr        (d_wdata),
        .dram_wr             (d_wen),
        .dram_data_rd        (d_rdata),
        .debug_wb_have_inst  (debug_wb_have_inst),
        .debug_wb_pc         (debug_wb_pc),
        .debug_wb_ena        (debug_wb_ena),
        .debug_wb_reg        (debug_wb_reg),
        .debug_wb_value      (debug_wb_value),
        .debug_wb_have_inst_1(debug_wb_have_inst_1),
        .debug_wb_pc_1       (debug_wb_pc_1),
        .debug_wb_ena_1      (debug_wb_ena_1),
        .debug_wb_reg_1      (debug_wb_reg_1),
        .debug_wb_value_1    (debug_wb_value_1)
    );

    IROM #(
        .ADDR_BITS(16)
    ) Mem_IROM (
        .clk (fpga_clk),
        .rst (fpga_rst),
        .en  (i_rd_en),
        .a   (i_addr[18:3]),
        .spo (i_rdata)
    );

    DRAM #(
        .ADDR_BITS(16)
    ) Mem_DRAM (
        .clk (fpga_clk),
        .a   (d_addr[17:2]),
        .we  (d_wen),
        .d   (d_wdata),
        .spo (d_rdata)
    );

endmodule
