module myCPU(
    input  logic         cpu_clk,
    input  logic         cpu_rst,   // High active
    
    // Interface to IROM
    output logic        irom_en,    // IROM使能信号
    output logic        irom_rst,   // IROM复位信号
    output logic [31:0] irom_addr,  // CPU输出PC地址
    input  logic [31:0] irom_data,  // IROM返回指令数据

    // Interface to Peripheral
    output logic [31:0] perip_addr,    
    output logic [3 :0] perip_wstrb,  // 4-bit 字节写使能
    output logic [31:0] perip_wdata,  
    input  logic [31:0] perip_rdata 
);

    logic [3 :0] bus_wen;
    //logic [31:0] bus_addr_internal;

    assign perip_wstrb = bus_wen;  // 4-bit 字节写使能直接透传


    wire [31:0] debug_wb_pc;
    wire [0 :0] debug_wb_rf_wen;
    wire [4 :0] debug_wb_rf_wnum;
    wire [31:0] debug_wb_rf_wdata;

    CPU Core_cpu6 (
        .cpu_rst            (cpu_rst),
        .cpu_clk            (cpu_clk),

        // Interface to IROM
        .irom_rdata         (irom_data),  // irom的输出接cpu的输入
        .irom_en            (irom_en),
        .irom_rst           (irom_rst),
        .irom_addr          (irom_addr),  // cpu的输出接irom的输入（PC）

        // Interface to DRAM & peripheral
        .bus_rdata          (perip_rdata),
        .bus_addr           (perip_addr),
        .bus_wdata          (perip_wdata),
        .bus_wen            (bus_wen),
        
        .debug_wb_have_inst (),
        .debug_wb_pc        (debug_wb_pc),
        .debug_wb_ena       (debug_wb_rf_wen),
        .debug_wb_reg       (debug_wb_rf_wnum),
        .debug_wb_value     (debug_wb_rf_wdata)
    );
endmodule