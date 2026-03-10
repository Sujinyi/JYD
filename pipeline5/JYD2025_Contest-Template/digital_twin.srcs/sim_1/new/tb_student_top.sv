`timescale 1ns / 1ps

module tb_student_top;

    // 1. 生成时钟和复位
    logic clk_50Mhz;
    logic cpu_clk;
    logic rst; // 高有效复位

    initial begin
        clk_50Mhz = 0;
        forever #10 clk_50Mhz = ~clk_50Mhz; // 50MHz: 20ns period
    end

    // 为了仿真方便，cpu_clk 也用 50MHz
    assign cpu_clk = clk_50Mhz;

    initial begin
        rst = 1;
        #100;
        rst = 0;
    end

    // 2. 交互信号 (全绑0)
    logic [7:0]  virtual_key = 8'd0;
    logic [63:0] virtual_sw  = 64'd0;
    logic [31:0] virtual_led;
    logic [39:0] virtual_seg;

    // 3. 提取 CPU 和外设的接口信号
    logic [31:0] pc, instruction;
    logic [31:0] perip_addr, perip_wdata, perip_rdata;
    logic perip_wen;
    logic [1:0]  perip_mask;

    // 4. 实例化待测 CPU (通过适配器)
    myCPU Core_cpu (
        .cpu_rst            (rst),
        .cpu_clk            (cpu_clk),
        .irom_addr          (pc),             
        .irom_data          (instruction),   
        .perip_addr         (perip_addr),     
        .perip_wen          (perip_wen),     
        .perip_mask         (perip_mask),   
        .perip_wdata        (perip_wdata),    
        .perip_rdata        (perip_rdata)     
    );

    // 5. 行为级 IROM 模型 (替代 Vivado IP核)
    // 16KB = 4096 words
    reg [31:0] irom_mem [0:4095];
    initial begin
        // 读取十六进制指令文件
        $readmemh("irom.hex", irom_mem);
        $display("IROM initialized from irom.hex");
    end

    // IROM 通过地址直接组合逻辑异步读取（无延迟）
    // PC 是字节地址，所以截取 [13:2] 作为字地址索引
    wire [11:0] inst_addr = pc[13:2];
    assign instruction = irom_mem[inst_addr];


    // 6. 行为级外设和 DRAM 响应
    // 地址常量匹配
    localparam DRAM_ADDR_START = 32'h8010_0000;
    localparam DRAM_ADDR_END   = 32'h8013_FFFF;
    localparam SW0_ADDR  = 32'h8020_0000;
    localparam SW1_ADDR  = 32'h8020_0004;
    localparam KEY_ADDR  = 32'h8020_0010;
    localparam SEG_ADDR  = 32'h8020_0020;
    localparam LED_ADDR  = 32'h8020_0040;
    localparam CNT_ADDR  = 32'h8020_0050;

    // 行为级 DRAM (256KB = 65536 words)
    reg [31:0] dram_mem [0:65535];
    initial begin
        $readmemh("dram.hex", dram_mem);
        $display("DRAM initialized from dram.hex");
    end

    wire is_dram    = (perip_addr >= DRAM_ADDR_START && perip_addr <= DRAM_ADDR_END);
    wire is_seg     = (perip_addr == SEG_ADDR);
    wire is_led     = (perip_addr == LED_ADDR);
    wire is_cnt     = (perip_addr == CNT_ADDR);

    // 行为级 DRAM 读写逻辑
    wire [15:0] dram_word_addr = perip_addr[17:2]; 
    wire [1:0]  dram_byte_offset = perip_addr[1:0];

    // Read logic
    reg [31:0] dram_rdata;
    always_comb begin
        dram_rdata = dram_mem[dram_word_addr];
    end

    // Write logic
    always_ff @(posedge cpu_clk) begin
        if (perip_wen && is_dram) begin
            case(perip_mask)
                2'b10: // word write
                    dram_mem[dram_word_addr] <= perip_wdata;
                2'b01: // halfword write
                    if (dram_byte_offset[1] == 1'b0)
                        dram_mem[dram_word_addr][15:0] <= perip_wdata[15:0];
                    else
                        dram_mem[dram_word_addr][31:16] <= perip_wdata[15:0];
                2'b00: // byte write
                    case(dram_byte_offset)
                        2'b00: dram_mem[dram_word_addr][7:0]   <= perip_wdata[7:0];
                        2'b01: dram_mem[dram_word_addr][15:8]  <= perip_wdata[7:0];
                        2'b10: dram_mem[dram_word_addr][23:16] <= perip_wdata[7:0];
                        2'b11: dram_mem[dram_word_addr][31:24] <= perip_wdata[7:0];
                    endcase
            endcase
            $display("[%0t] DRAM WRITE: Addr=0x%08x, Data=0x%08x, Mask=%b", $time, perip_addr, perip_wdata, perip_mask);
        end
    end

    // 行为级 Counter (简化版)
    reg [31:0] counter_ms;
    reg counter_running;
    reg [15:0] clk_tick; // count 50,000 to get 1ms

    initial begin
        counter_ms = 0;
        counter_running = 0;
        clk_tick = 0;
    end

    always_ff @(posedge clk_50Mhz) begin
        if (rst) begin
            counter_ms <= 0;
            counter_running <= 0;
            clk_tick <= 0;
        end else begin
            if (perip_wen && is_cnt) begin
                if (perip_wdata == 32'h8000_0000) begin
                    counter_running <= 1;
                    $display("[%0t] COUNTER STARTED", $time);
                end else if (perip_wdata == 32'hFFFF_FFFF) begin
                    counter_running <= 0;
                    $display("[%0t] COUNTER STOPPED, Total MS = %0d", $time, counter_ms);
                end
            end
            
            if (counter_running) begin
                if (clk_tick == 49999) begin
                    clk_tick <= 0;
                    counter_ms <= counter_ms + 1;
                end else begin
                    clk_tick <= clk_tick + 1;
                end
            end
        end
    end

    // 读数据多路选择器
    always_comb begin
        if (is_dram) begin
            // 简单的组合逻辑字对齐合并，用于行为级模拟
            case(perip_mask)
                2'b10: perip_rdata = dram_rdata; // word read
                2'b01: // halfword read 
                    perip_rdata = dram_byte_offset[1] ? {16'b0, dram_rdata[31:16]} : {16'b0, dram_rdata[15:0]};
                2'b00: // byte read
                    case(dram_byte_offset)
                        2'b00: perip_rdata = {24'b0, dram_rdata[7:0]};
                        2'b01: perip_rdata = {24'b0, dram_rdata[15:8]};
                        2'b10: perip_rdata = {24'b0, dram_rdata[23:16]};
                        2'b11: perip_rdata = {24'b0, dram_rdata[31:24]};
                    endcase
            endcase
        end else if (perip_addr == SW0_ADDR) begin
            perip_rdata = virtual_sw[31:0];
        end else if (perip_addr == SW1_ADDR) begin
            perip_rdata = virtual_sw[63:32];
        end else if (perip_addr == KEY_ADDR) begin
            perip_rdata = {24'd0, virtual_key};
        end else if (is_cnt) begin
            perip_rdata = counter_ms;
        end else begin
            perip_rdata = 32'hDEAD_BEEF;
        end
    end

    // 7. 打印外设写入信息
    reg [31:0] prev_seg;
    always_ff @(posedge cpu_clk) begin
        if (!rst && perip_wen) begin
            if (is_seg) begin
                if (perip_wdata !== prev_seg) begin
                    $display("[%0t] SEG DISPLAY UPDATED: 0x%08x (%0d)", $time, perip_wdata, perip_wdata);
                    prev_seg <= perip_wdata;
                end
            end else if (is_led) begin
                $display("[%0t] LED UPDATED: 0x%08x", $time, perip_wdata);
            end
        end
    end

    // 8. 死循环检测 & 仿真结束
    // JYD的测试程序通常以死循环结尾，或者检测特定的异常退出状态
    reg [31:0] last_pc;
    always_ff @(posedge cpu_clk) begin
        if (!rst) begin
            // 检测 jal x0, 0 或 jal x0, xx 导致PC不再变化
            // 或者直接检测特定的测试结束指令 0x0000006f
            if (instruction == 32'h0000006f && pc == last_pc) begin
                $display("[%0t] INFO: CPU HALTED (Infinite Loop at PC 0x%08x)", $time, pc);
                // 打印最后留在数码管上的成绩
                $display("========================================");
                $display("FINAL SCORE / Result on SEG: %0d", prev_seg);
                $display("========================================");
                $finish;
            end
            last_pc <= pc;
        end
    end

    // 超时退出机制防止无限跑
    initial begin
        #50000000; // 50ms 仿真时间限制，足够执行完毕
        $display("[%0t] ERROR: Simulation Timeout!", $time);
        $finish;
    end

endmodule
