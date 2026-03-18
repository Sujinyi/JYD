// 指令存储器模型 - 异步读取
module irom #(
    parameter DATAWIDTH = 32,
    parameter ADDR_WIDTH = 32,
    parameter ROM_DEPTH = 1024  // 4KB 指令空间
)(
    input  logic [ADDR_WIDTH-1:0] addr,
    output logic [DATAWIDTH-1:0] rdata
);

    // 字地址深度
    localparam WORD_DEPTH = ROM_DEPTH / 4;
    logic [DATAWIDTH-1:0] rom [0:WORD_DEPTH-1];

    // 地址基址（从链接脚本中的起始地址）
    // 支持两种地址映射：
    // - 0x8000_0000: 用于实际硬件部署
    // - 0x00001000: 用于功能测试 (riscv-tests)
    localparam BASE_ADDR = 32'h0000_1000;

    // 异步读取 - 字节地址转字地址，并重映射到从 0 开始
    logic [ADDR_WIDTH-1:0] word_addr;
    assign word_addr = (addr - BASE_ADDR) >> 2;

    // 地址范围检查
    always_comb begin
        if (addr >= BASE_ADDR && word_addr < WORD_DEPTH) begin
            rdata = rom[word_addr];
        end else begin
            rdata = 32'h00000013; // 返回 nop 指令 (addi x0, x0, 0)
        end
    end

    // Task: 动态加载指令文件
    task load_hex_file(string filename);
        // 清空 ROM
        for (int i = 0; i < WORD_DEPTH; i++) begin
            rom[i] = 32'h00000013; // nop 指令
        end
        // 加载新文件
        $readmemh(filename, rom);
        $display("[IROM] Loaded %s, depth=%0d words (base=0x%08h)", filename, WORD_DEPTH, BASE_ADDR);
    endtask

    // Task: 清空指令存储器
    task clear_rom();
        for (int i = 0; i < WORD_DEPTH; i++) begin
            rom[i] = 32'h00000013; // nop 指令
        end
        $display("[IROM] Cleared, filled with NOP instructions");
    endtask

endmodule
