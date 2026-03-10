module myCPU(
    input  logic         cpu_clk,
    input  logic         cpu_rst,   // High active
    
    // Interface to IROM
    output logic [31:0] irom_addr,  // CPU输出PC地址
    input  logic [31:0] irom_data,  // IROM返回指令数据

    // Interface to Peripheral
    output logic [31:0] perip_addr,    
    output logic [0 :0] perip_wen,   
    output logic [1 :0] perip_mask,  
    output logic [31:0] perip_wdata,  
    input  logic [31:0] perip_rdata 
);

    logic [3 :0] bus_wen;
    //logic [31:0] bus_addr_internal;

    assign perip_wen = |bus_wen; // 只要bus_wen中有一个bit为1，perip_wen就为1

    // perip_mask: 读操作时也需要正确的mask
    // dram_driver 用 perip_mask 来选择返回的字节数
    // CPU的MEM模块自己做 lb/lh 截取，所以读操作应该总是返回完整 32-bit word
    always_comb begin
        if (|bus_wen) begin
            // 写操作：根据 bus_wen 推断写宽度
            case(bus_wen)
                4'b0001,
                4'b0010,
                4'b0100,
                4'b1000: perip_mask = 2'b00; // 1字节写
                4'b0011,
                4'b1100: perip_mask = 2'b01; // 2字节写
                4'b1111: perip_mask = 2'b10; // 4字节写
                default: perip_mask = 2'b10; // 默认按字
            endcase
        end else begin
            // 读操作：始终返回完整字（CPU的MEM模块自己做 byte/halfword 选择）
            perip_mask = 2'b10;
        end
    end

    myCPU1 Core_cpu1 (
        .cpu_rst            (cpu_rst),
        .cpu_clk            (cpu_clk),

        // Interface to IROM
        .irom_rdata         (irom_data),  // irom的输出接cpu的输入
        .irom_addr          (irom_addr),  // cpu的输出接irom的输入（PC）

        // Interface to DRAM & peripheral
        .bus_rdata          (perip_rdata),
        .bus_addr           (perip_addr),
        .bus_wdata          (perip_wdata),
        .bus_wen            (bus_wen),
        
        // Debug信号暂时悬空
        .debug_wb_have_inst (),
        .debug_wb_pc        (),
        .debug_wb_ena       (),
        .debug_wb_reg       (),
        .debug_wb_value     ()
    );
endmodule