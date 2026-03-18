# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

这是 RISC-V CPU (RV32I 指令集) 测试项目，裁剪自官方 [riscv-tests](https://github.com/riscv-software-src/riscv-tests)，用于验证 CPU 的功能正确性和性能表现。

**项目结构**:
- `isa/`: 功能测试，验证指令集功能正确性
- `benchmark/`: 性能测试，测量程序执行性能
- `baseline/`: 参考实现 (`cpu.v`)，提供 CPU 接口示例
- `tools/`: 辅助工具 (`bin2coe.cpp` 用于生成 COE 文件)

## 构建命令

### 功能测试 (ISA)
```bash
cd isa
make          # 编译所有测试程序，生成 .bin/.coe/.dump 文件
make clean    # 清理生成的文件
```

### 性能测试 (Benchmark)
```bash
cd benchmark
make          # 编译冒泡排序测试程序，生成 .bin/.coe/.dump 文件
make clean    # 清理生成的文件
```

### 单个测试文件编译
功能测试会自动编译 `isa/rv32mi/` 目录下的所有 `.S` 文件。要单独编译某个测试：
```bash
cd isa
make rv32mi/add.o    # 编译 add.S 目标文件
make rv32mi/add.bin  # 生成二进制文件
make rv32mi/add.coe  # 生成 COE 文件 (用于 Vivado Block RAM IP 初始化)
```

**工具链说明**:
- ISA 测试默认使用 `riscv64-elf-` 前缀
- Benchmark 测试默认使用 `riscv32-unknown-elf-` 前缀
- 可通过环境变量 `RISCV_PREFIX` 覆盖默认前缀：
  ```bash
  make RISCV_PREFIX=riscv64-unknown-elf-
  ```

### 生成 HEX 文件（用于仿真）
如果需要在 Verilog 仿真中使用 `$readmemh` 加载测试程序：
```bash
cd isa
make hex  # 批量生成所有测试的 _text.hex 和 _data.hex 文件
# 或者单独生成
python3 generate_hex.py rv32mi/sw.o ./rv32mi/  # 生成 sw_text.hex 和 sw_data.hex
```
HEX 文件格式：每行一个 32 位十六进制字，小端模式，可直接用于 `$readmemh`。

## 测试流程

### 前期准备
CPU 需要先正确实现基础指令：
- **功能测试**: `addi, lui, bne, jal`
- **性能测试**: `addi, slli, lw, sw, jal, jalr, bge, blt, bltu`

### 测试方法
1. **单独测试**: 使用生成的 `.coe` 文件初始化指令存储器 IP，在仿真或 FPGA 上运行
2. **内存配置**: 所有地址为字节寻址，数据存储为**小端模式**
3. **地址映射**:
   - 功能测试: 代码段 `0x00001000`，数据段 `0x00000000`
   - 性能测试: 代码段 `0x00004000`，数据段 `0x00000000`

### 测试结果判断
功能测试通过以下寄存器判断：
- `TESTRES` (fp) = 1: 测试完成
- `TESTNUM` (gp) ≠ 0: 测试成功

性能测试：
- 返回值 = 0: 排序正确
- 返回值 ≠ 0: 出错的测试数据序号

## 测试架构

### 功能测试 (isa/)
测试指令集功能的正确性，按指令类型组织：
- **算术逻辑指令**: `add.S, addi.S, and.S, andi.S, ori.S, xori.S, slli.S, srli.S, srai.S, slti.S, sltiu.S`
- **分支指令**: `beq.S, bne.S, blt.S, bge.S, bltu.S, bgeu.S, jal.S, jalr.S`
- **访存指令**: `lw.S, lb.S, lbu.S, lh.S, lhu.S, sw.S, sb.S, sh.S`
- **其他指令**: `lui.S, auipc.S, slt.S, sltu.S, sub.S, xor.S, or.S, sll.S, srl.S, sra.S`
- **冒险测试**: `bypass.S` - 测试数据冒险、控制冒险、结构冒险

测试宏定义 (`isa/macros.h`):
- `TEST_RR_OP`: R-type 指令测试（寄存器-寄存器）
- `TEST_IMM_OP`: I-type 指令测试（立即数）
- `TEST_LD_OP` / `TEST_ST_OP`: Load/Store 指令测试
- `TEST_BR2_OP`: 分支指令测试
- `*_BYPASS`: 冒险测试（测试不同流水线深度下的数据转发）
- `TESTNUM = gp`: 测试编号，非 0 表示通过
- `TESTRES = fp`: 测试完成标志，1 表示完成

测试流程: 初始化寄存器 → 执行测试用例 → 检查结果 → 返回状态

### 性能测试 (benchmark/)
测试 CPU 执行程序的性能：
- `sort.c`: 冒泡排序主程序
- `datasheet.h`: 2048 项测试数据和验证数据
- 计算性能得分: `score = (t_baseline / t) = (c_baseline/f_baseline) / (c/f)`

### CPU 接口规范
参考实现 (`baseline/cpu.v`) 展示了测试所需的 CPU 接口：

**指令存储器接口**:
- `imem_en`: 指令存储器使能
- `imem_addr[31:0]`: 指令地址（字节寻址）
- `imem_rdata[31:0]`: 读取的指令

**数据存储器接口**:
- `dmem_en`: 数据存储器使能
- `dmem_wen`: 数据存储器写使能
- `dmem_addr[31:0]`: 数据地址（字节寻址）
- `dmem_wdata[31:0]`: 写入数据
- `dmem_rdata[31:0]`: 读取数据

所有地址均为字节寻址，数据以**小端模式**存储。

## 工具链要求

需要 RISC-V 交叉编译工具链：
- 主要工具: `gcc`, `objcopy`, `objdump`
- ISA 测试默认前缀: `riscv64-elf-`
- Benchmark 测试默认前缀: `riscv32-unknown-elf-`
- 可通过环境变量 `RISCV_PREFIX` 修改

构建过程会自动编译 `tools/bin2coe.cpp` 用于生成 COE 文件（Vivado IP 初始化格式）。

## 开发工作流

### 修改测试用例
1. 修改 `isa/rv32mi/*.S` 汇编文件中的测试用例
2. 运行 `make` 重新编译
3. 使用生成的 `.coe` 或 `.hex` 文件进行测试

### 添加新测试
1. 在 `isa/rv32mi/` 创建新的 `.S` 文件
2. 包含必要的头文件和测试宏：
   ```assembly
   #include "macros.h"

   RVTEST_RV32MI
   RVTEST_CODE_BEGIN
     # 测试用例
     TEST_RR_OP(1, add, 2, 1, 1)  // testnum=1, add, result=2, rs1=1, rs2=1
   RVTEST_CODE_END

   .data
   RVTEST_DATA_BEGIN
     TEST_DATA
   RVTEST_DATA_END
   ```
3. Makefile 会自动检测并编译新的 `.S` 文件

### 集成测试到 CPU 仿真
1. **FPGA 实现**: 使用 `.coe` 文件初始化 Block RAM IP
2. **Verilog 仿真**: 使用 `_text.hex` 和 `_data.hex` 文件配合 `$readmemh`
   ```verilog
   reg [31:0] imem [0:1023];
   reg [31:0] dmem [0:1023];
   initial begin
       $readmemh("rv32mi/add_text.hex", imem);
       $readmemh("rv32mi/add_data.hex", dmem);
   end
   ```

## 注意事项

- **测试顺序**: 建议按基础指令优先测试，如 `jal → bne → lui → addi → ...`
- **小端模式**: 内存数据必须以小端模式存储
- **寄存器使用**: `gp` 用于 TESTNUM，`fp` 用于 TESTRES，避免在测试用例中修改这两个寄存器
- **宏定义**: `macros.h` 定义了测试框架和断言机制，修改前需理解其对测试流程的影响

## 输出文件格式

### COE 文件 (`.coe`)
- 用途：Vivado Block RAM IP 初始化（FPGA 实现）
- 格式：`memory_initialization_radix = 16; memory_initialization_vector = ...`
- 生成：由 `tools/bin2coe.cpp` 从 `.bin` 文件生成

### HEX 文件 (`_text.hex`, `_data.hex`)
- 用途：Verilog 仿真，通过 `$readmemh` 加载
- 格式：每行一个 32 位十六进制字，小端模式
- 生成：由 `isa/generate_hex.py` 从 `.o` 文件分离 .text 和 .data 段
- 优势：分离指令存储器和数据存储器，便于独立调试

### 二进制文件 (`.bin`)
- 用途：原始二进制镜像
- 格式：连续的字节序列，小端模式
- 生成：由 `objcopy -O binary` 从 `.o` 文件生成

### 反汇编文件 (`.dump`)
- 用途：调试和验证指令编码
- 格式：包含地址、机器码和汇编指令
- 生成：由 `objdump` 从 `.o` 文件生成