`timescale 1ns / 1ps
/*
 * 多测试支持 Testbench
 * 支持批量运行 rv32mi 测试集
 */

module tb_myCPU1;

    // ============================================================
    // 参数配置
    // ============================================================
    parameter CLK_PERIOD     = 10;           // 时钟周期 (ns)
    parameter SIM_TIMEOUT    = 100000;       // 单个测试超时 (ns)
    parameter RESET_CYCLES   = 5;            // 复位持续周期数
    parameter CPU_RESET_ADDR = 32'h0000_1000; // CPU 复位地址
    parameter MAX_INST_COUNT = 10000;        // 单个测试最大指令数

    // 调试级别控制
    parameter DEBUG_LEVEL    = 1;            // 0: 关闭, 1: 基本信息, 2: 详细跟踪

    // 测试文件路径前缀
    parameter TEST_PATH      = "cs3001h.tests/isa/rv32mi/";

    // ============================================================
    // 测试列表
    // ============================================================
    string test_list[] = {
        // 算术逻辑指令
        "add", "addi", "sub",
        "and", "andi", "or", "ori", "xor", "xori",
        "sll", "slli", "srl", "srli", "sra", "srai",
        "slt", "slti",  // 注：sltu/sltiu 无源文件
	"sltu", "sltiu",

        // 分支指令
        "beq", "bne", "blt", "bge", "bltu", "bgeu",

        // 跳转指令
        "jal", "jalr",

        // U-type 指令
        "lui", "auipc",

        // 访存指令
        "lw", "lh", "lhu", "lb", "lbu",
        "sw", "sh", "sb",

        // 冒险测试
        "bypass"
    };

    // ============================================================
    // 测试管理变量
    // ============================================================
    int test_index;              // 当前测试索引
    string current_test;          // 当前测试名称
    int test_passed_cnt;          // 通过测试计数
    int test_failed_cnt;          // 失败测试计数
    int test_timeout_cnt;         // 超时测试计数

    // 单个测试状态
    logic test_completed;         // 测试完成标志 (fp=1)
    logic test_passed;            // 测试通过标志 (gp≠0)
    logic test_timeout;           // 测试超时标志
    int inst_count;               // 当前测试指令计数

    // ============================================================
    // 信号声明
    // ============================================================
    logic clk;
    logic rst;

    // IROM 接口
    logic [31:0] irom_rdata;
    logic [31:0] irom_addr;

    // DRAM 接口
    logic [31:0] bus_rdata;
    logic [31:0] bus_addr;
    logic [31:0] bus_wdata;
    logic [3:0]  bus_wen;

    // Debug 接口
    logic        debug_wb_have_inst;
    logic [31:0] debug_wb_pc;
    logic        debug_wb_ena;
    logic [4:0]  debug_wb_reg;
    logic [31:0] debug_wb_value;

    // ============================================================
    // CPU 实例
    // ============================================================
    myCPU1 #(
        .DATAWIDTH (32),
        .RESET_VAL (CPU_RESET_ADDR)
    ) u_cpu (
        .cpu_clk              (clk),
        .cpu_rst              (rst),
        .irom_rdata           (irom_rdata),
        .irom_addr            (irom_addr),
        .bus_rdata            (bus_rdata),
        .bus_addr             (bus_addr),
        .bus_wdata            (bus_wdata),
        .bus_wen              (bus_wen),
        .debug_wb_have_inst   (debug_wb_have_inst),
        .debug_wb_pc          (debug_wb_pc),
        .debug_wb_ena         (debug_wb_ena),
        .debug_wb_reg         (debug_wb_reg),
        .debug_wb_value       (debug_wb_value)
    );

    // ============================================================
    // 存储器实例
    // ============================================================
    irom #(
        .DATAWIDTH  (32),
        .ADDR_WIDTH (32),
        .ROM_DEPTH  (4096)
    ) u_irom (
        .addr  (irom_addr),
        .rdata (irom_rdata)
    );

    dram #(
        .DATAWIDTH  (32),
        .ADDR_WIDTH (32),
        .RAM_DEPTH  (4096)
    ) u_dram (
        .clk   (clk),
        .addr  (bus_addr),
        .wdata (bus_wdata),
        .wen   (bus_wen),
        .rdata (bus_rdata)
    );

    // ============================================================
    // 寄存器监控（通过层次化路径访问）
    // ============================================================
    logic [31:0] x [0:31];

    generate
        for (genvar i = 0; i < 32; i++) begin : gen_reg_monitor
            assign x[i] = u_cpu.reg_file_inst.reg_bank[i];
        end
    endgenerate

    // ABI 命名别名
    logic [31:0] zero, ra, sp, gp, tp;                       // x0-x4
    logic [31:0] t0, t1, t2;                                 // x5-x7
    logic [31:0] s0, s1, fp;                                 // x8-x9 (fp = s0)
    logic [31:0] a0, a1, a2, a3, a4, a5, a6, a7;             // x10-x17
    logic [31:0] s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;   // x18-x27
    logic [31:0] t3, t4, t5, t6;                             // x28-x31

    assign zero = x[0];  assign ra   = x[1];  assign sp   = x[2];  assign gp   = x[3];
    assign tp   = x[4];  assign t0   = x[5];  assign t1   = x[6];  assign t2   = x[7];
    assign s0   = x[8];  assign s1   = x[9];  assign fp   = x[8];  // fp = s0
    assign a0   = x[10]; assign a1   = x[11]; assign a2   = x[12]; assign a3   = x[13];
    assign a4   = x[14]; assign a5   = x[15]; assign a6   = x[16]; assign a7   = x[17];
    assign s2   = x[18]; assign s3   = x[19]; assign s4   = x[20]; assign s5   = x[21];
    assign s6   = x[22]; assign s7   = x[23]; assign s8   = x[24]; assign s9   = x[25];
    assign s10  = x[26]; assign s11  = x[27]; assign t3   = x[28]; assign t4   = x[29];
    assign t5   = x[30]; assign t6   = x[31];

    // ============================================================
    // 时钟生成
    // ============================================================
    initial begin
        clk = 0;
        forever #(CLK_PERIOD/2) clk = ~clk;
    end

    // ============================================================
    // 主测试流程
    // ============================================================
    initial begin
        // 1. 初始化测试统计
        init_test_statistics();

        // 2. 打印测试头信息
        print_header();

        // 3. 遍历所有测试
        for (test_index = 0; test_index < test_list.size(); test_index++) begin
            current_test = test_list[test_index];

            // 执行单个测试
            run_single_test(current_test);

            // 等待一段时间再开始下一个测试
            #(CLK_PERIOD * 10);
        end

        // 4. 打印测试汇总
        print_summary();

        // 5. 结束仿真
        $finish;
    end

    // ============================================================
    // 仿真监控逻辑
    // ============================================================

    // 指令执行跟踪与计数
    always @(posedge clk) begin
        if (!rst && !test_completed && !test_timeout) begin
            inst_count = inst_count + 1;
            trace_instruction();

            // 检查指令计数是否超限
            if (inst_count >= MAX_INST_COUNT) begin
                test_timeout = 1;
                $display("\n[ERROR] Test '%s' exceeded max instruction count (%0d)",
                         current_test, MAX_INST_COUNT);
            end
        end
    end

    // 测试完成检测 (fp = 1)
    always @(posedge clk) begin
        if (!rst && !test_completed && !test_timeout) begin
            if (fp == 1) begin
                test_completed = 1;
                test_passed = (gp != 0);
                $display("\n[INFO] Test '%s' completed: fp=%0d, gp=%0d",
                         current_test, fp, gp);
            end
        end
    end

    // ============================================================
    // Task 定义区
    // ============================================================

    // 任务：初始化测试统计
    task init_test_statistics();
        begin
            test_passed_cnt  = 0;
            test_failed_cnt  = 0;
            test_timeout_cnt = 0;
            test_index       = 0;
        end
    endtask

    // 任务：打印测试头信息
    task print_header();
        begin
            $display("\n========================================");
            $display("  RISC-V CPU Multi-Test Framework");
            $display("========================================");
            $display("Configuration:");
            $display("  Total Tests:       %0d", test_list.size());
            $display("  CPU Reset Address: 0x%08h", CPU_RESET_ADDR);
            $display("  Max Instructions:  %0d per test", MAX_INST_COUNT);
            $display("  Debug Level:       %0d", DEBUG_LEVEL);
            $display("  Test Path:         %s", TEST_PATH);
            $display("========================================\n");
        end
    endtask

    // 任务：执行单个测试
    task run_single_test(string test_name);
        begin
            $display("\n----------------------------------------");
            $display("Test #%0d: %s", test_index + 1, test_name);
            $display("----------------------------------------");

            // 1. 初始化测试状态
            init_single_test_state();

            // 2. 加载测试文件
            load_test_files(test_name);

            // 3. 执行复位
            apply_reset();

            // 4. 运行测试直到完成或超时
            wait_test_completion();

            // 5. 检查并记录结果
            check_and_record_result(test_name);
        end
    endtask

    // 任务：初始化单个测试状态
    task init_single_test_state();
        begin
            test_completed = 0;
            test_passed    = 0;
            test_timeout   = 0;
            inst_count     = 0;
        end
    endtask

    // 任务：加载测试文件
    task load_test_files(string test_name);
        string text_file;
        string data_file;
        begin
            text_file = {TEST_PATH, test_name, "_text.hex"};
            data_file = {TEST_PATH, test_name, "_data.hex"};

            // 加载指令存储器
            u_irom.load_hex_file(text_file);

            // 加载数据存储器
            u_dram.load_hex_file(data_file);
        end
    endtask

    // 任务：执行复位序列
    task apply_reset();
        begin
            rst = 1;
            repeat(RESET_CYCLES) @(posedge clk);
            @(negedge clk);
            rst = 0;
            $display("[INFO] Reset released, starting execution...");

            // 等待第一个有效时钟沿
            @(posedge clk);
        end
    endtask

    // 任务：等待测试完成
    task wait_test_completion();
        integer timeout_cycles;
        begin
            timeout_cycles = SIM_TIMEOUT / CLK_PERIOD;

            // 等待完成或超时
            fork
                begin
                    // 正常完成
                    wait(test_completed || test_timeout);
                end
                begin
                    // 超时保护
                    repeat(timeout_cycles) @(posedge clk);
                    if (!test_completed && !test_timeout) begin
                        test_timeout = 1;
                        $display("\n[ERROR] Test '%s' timed out after %0t",
                                 current_test, $time);
                    end
                end
            join_any

            // 取消未完成的进程
            disable fork;
        end
    endtask

    // 任务：检查并记录测试结果
    task check_and_record_result(string test_name);
        begin
            if (test_timeout) begin
                test_timeout_cnt = test_timeout_cnt + 1;
                $display("[RESULT] TIMEOUT");
                $display("  Test:     %s", test_name);
                $display("  Reason:   Exceeded max instructions or time limit");
            end
            else if (test_completed) begin
                if (test_passed) begin
                    test_passed_cnt = test_passed_cnt + 1;
                    $display("[RESULT] PASSED");
                    $display("  Test:     %s", test_name);
                    $display("  TESTNUM:  %0d (gp/x3)", gp);
                    $display("  Instructions: %0d", inst_count);
                end else begin
                    test_failed_cnt = test_failed_cnt + 1;
                    $display("[RESULT] FAILED");
                    $display("  Test:     %s", test_name);
                    $display("  TESTNUM:  %0d (gp/x3, expected non-zero)", gp);
                    $display("  Instructions: %0d", inst_count);
                end
            end else begin
                test_failed_cnt = test_failed_cnt + 1;
                $display("[RESULT] FAILED");
                $display("  Test:     %s", test_name);
                $display("  Reason:   Test did not complete (fp != 1)");
            end
        end
    endtask

    // 任务：指令跟踪
    task trace_instruction();
        begin
            if (DEBUG_LEVEL >= 2) begin
                $display("  [%0t] Cycle #%0d: PC=0x%08h, Inst=0x%08h",
                         $time, inst_count, u_cpu.pc_out, irom_rdata);

                if (debug_wb_ena) begin
                    $display("              -> Write x%0d = 0x%08h",
                             debug_wb_reg, debug_wb_value);
                end
            end else if (DEBUG_LEVEL >= 1 && inst_count % 100 == 0) begin
                $display("  [INFO] %0d instructions executed...", inst_count);
            end
        end
    endtask

    // 任务：打印测试汇总
    task print_summary();
        begin
            $display("\n========================================");
            $display("  Test Summary");
            $display("========================================");
            $display("Total Tests:  %0d", test_list.size());
            $display("  PASSED:     %0d", test_passed_cnt);
            $display("  FAILED:     %0d", test_failed_cnt);
            $display("  TIMEOUT:    %0d", test_timeout_cnt);
            $display("----------------------------------------");

            if (test_failed_cnt == 0 && test_timeout_cnt == 0) begin
                $display("*** ALL TESTS PASSED ***");
            end else begin
                $display("*** SOME TESTS FAILED ***");
                $display("  Success Rate: %0.1f%%",
                         real'(test_passed_cnt) * 100.0 / real'(test_list.size()));
            end

            $display("========================================\n");
        end
    endtask

    // ============================================================
    // 调试辅助任务
    // ============================================================

    // 任务：检查寄存器值
    task check_reg(input [4:0] reg_id, input [31:0] expected);
        begin
            if (x[reg_id] != expected) begin
                $display("[ERROR] Register x%0d mismatch: expected 0x%08h, got 0x%08h",
                         reg_id, expected, x[reg_id]);
            end else begin
                $display("[OK] Register x%0d = 0x%08h", reg_id, x[reg_id]);
            end
        end
    endtask

    // 任务：检查内存值
    task check_mem(input [31:0] addr, input [31:0] expected);
        logic [31:0] actual;
        begin
            // 直接访问 dram 内部 ram
            actual = {u_dram.ram[addr+3], u_dram.ram[addr+2],
                      u_dram.ram[addr+1], u_dram.ram[addr]};

            if (actual != expected) begin
                $display("[ERROR] Memory [0x%08h] mismatch: expected 0x%08h, got 0x%08h",
                         addr, expected, actual);
            end else begin
                $display("[OK] Memory [0x%08h] = 0x%08h", addr, actual);
            end
        end
    endtask

    // 任务：打印所有寄存器（数字 + ABI 命名）
    task dump_registers_with_abi();
        begin
            $display("\n========================================");
            $display("All Registers (with ABI Names):");
            $display("========================================");
            $display("x0  (zero) = 0x%08h    x1  (ra)   = 0x%08h", x[0],  x[1]);
            $display("x2  (sp)   = 0x%08h    x3  (gp)   = 0x%08h", x[2],  x[3]);
            $display("x4  (tp)   = 0x%08h    x5  (t0)   = 0x%08h", x[4],  x[5]);
            $display("x6  (t1)   = 0x%08h    x7  (t2)   = 0x%08h", x[6],  x[7]);
            $display("x8  (s0/fp)= 0x%08h    x9  (s1)   = 0x%08h", x[8],  x[9]);
            $display("x10 (a0)   = 0x%08h    x11 (a1)   = 0x%08h", x[10], x[11]);
            $display("x12 (a2)   = 0x%08h    x13 (a3)   = 0x%08h", x[12], x[13]);
            $display("x14 (a4)   = 0x%08h    x15 (a5)   = 0x%08h", x[14], x[15]);
            $display("x16 (a6)   = 0x%08h    x17 (a7)   = 0x%08h", x[16], x[17]);
            $display("x18 (s2)   = 0x%08h    x19 (s3)   = 0x%08h", x[18], x[19]);
            $display("x20 (s4)   = 0x%08h    x21 (s5)   = 0x%08h", x[20], x[21]);
            $display("x22 (s6)   = 0x%08h    x23 (s7)   = 0x%08h", x[22], x[23]);
            $display("x24 (s8)   = 0x%08h    x25 (s9)   = 0x%08h", x[24], x[25]);
            $display("x26 (s10)  = 0x%08h    x27 (s11)  = 0x%08h", x[26], x[27]);
            $display("x28 (t3)   = 0x%08h    x29 (t4)   = 0x%08h", x[28], x[29]);
            $display("x30 (t5)   = 0x%08h    x31 (t6)   = 0x%08h", x[30], x[31]);
            $display("========================================");
        end
    endtask

    // 任务：打印内存区域
    task dump_memory(input [31:0] start_addr, input int length);
        int i;
        logic [31:0] data;
        begin
            $display("\n========================================");
            $display("Memory Dump [0x%08h - 0x%08h]:", start_addr, start_addr + length*4 - 1);
            $display("========================================");

            for (i = 0; i < length; i++) begin
                data = {u_dram.ram[start_addr+i*4+3], u_dram.ram[start_addr+i*4+2],
                        u_dram.ram[start_addr+i*4+1], u_dram.ram[start_addr+i*4]};
                $display("[0x%08h] = 0x%08h", start_addr + i*4, data);
            end

            $display("========================================");
        end
    endtask

endmodule
