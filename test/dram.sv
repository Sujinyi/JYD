// 数据存储器模型 - 异步读取，同步写入
module dram #(
    parameter DATAWIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter RAM_DEPTH = 1024  // 4KB数据空间
)(
    input  logic                    clk,
    input  logic [ADDR_WIDTH-1:0]   addr,
    input  logic [DATAWIDTH-1:0]    wdata,
    input  logic [3:0]              wen,
    output logic [DATAWIDTH-1:0]    rdata
);

    // 字地址深度
    localparam WORD_DEPTH = RAM_DEPTH / 4;
    logic [7:0] ram [0:RAM_DEPTH-1];

    // 哈佛架构：数据存储器从 0x00000000 开始，不使用基地址重映射
    // 地址范围检查：确保在 0 到 RAM_DEPTH-1 之间
    // 返回字对齐的数据（从 addr&~3 开始的 4 字节），由 MEM 模块负责字节/半字选择
    always_comb begin
        if (addr < RAM_DEPTH) begin
            // 字对齐地址
            logic [ADDR_WIDTH-1:0] word_addr;
            word_addr = {addr[ADDR_WIDTH-1:2], 2'b00};
            rdata = {ram[word_addr+3], ram[word_addr+2], ram[word_addr+1], ram[word_addr]};
        end else begin
            rdata = 32'hxxxxxxxx;  // 地址越界返回未定义值
        end
    end

    // 同步写入 - 字节写使能
    // 注意：wen 信号基于字对齐地址设计，需要根据 addr[1:0] 调整
    // 当 addr[1:0]=00 时：wen[0:1] 写入低字节，wen[2:3] 写入高字节
    // 当 addr[1:0]=10 时：wen[2:3] 应该写入 addr 和 addr+1（而不是 addr+2 和 addr+3）
    always_ff @(posedge clk) begin
        if (addr < RAM_DEPTH) begin
            case (addr[1:0])
                2'b00: begin  // 字对齐
                    if (wen[0]) ram[addr]   <= wdata[7:0];
                    if (wen[1]) ram[addr+1] <= wdata[15:8];
                    if (wen[2]) ram[addr+2] <= wdata[23:16];
                    if (wen[3]) ram[addr+3] <= wdata[31:24];
                end
                2'b10: begin  // 半字对齐（如 0x02, 0x06）
                    // wen[2:3] 应该写入 addr 和 addr+1
                    if (wen[2]) ram[addr]   <= wdata[23:16];
                    if (wen[3]) ram[addr+1] <= wdata[31:24];
                end
                2'b01: begin  // 字节对齐（如 0x01）
                    if (wen[1]) ram[addr]   <= wdata[15:8];
                end
                2'b11: begin  // 字节对齐（如 0x03）
                    if (wen[3]) ram[addr]   <= wdata[31:24];
                end
            endcase
        end
    end

    // Task: 动态加载数据文件
    task load_hex_file(string filename);
        // 清空 RAM
        for (int i = 0; i < RAM_DEPTH; i++) begin
            ram[i] = 8'h00;
        end
        // 加载新文件
        $readmemh(filename, ram);
        $display("[DRAM] Loaded %s, size=%0d bytes (base=0x00000000)", filename, RAM_DEPTH);
    endtask

    // Task: 清空数据存储器
    task clear_ram();
        for (int i = 0; i < RAM_DEPTH; i++) begin
            ram[i] = 8'h00;
        end
        $display("[DRAM] Cleared, all bytes set to 0x00");
    endtask

endmodule
