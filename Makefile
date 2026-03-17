# RISC-V CPU 统一测试 Makefile
# 用法:
#   make CPU=single        - 测试单周期 CPU
#   make CPU=pipeline5     - 测试 5 级流水线 CPU
#   make all               - 测试所有 CPU

# 默认测试单周期 CPU
CPU ?= single

# 验证 CPU 参数（仅在非 clean 目标时检查）
ifneq ($(MAKECMDGOALS),clean)
  ifeq ($(filter $(CPU),single pipeline5),)
    $(error 无效的 CPU 参数：$(CPU)。请使用 CPU=single 或 CPU=pipeline5)
  endif
endif

# 工具链配置
AS = riscv64-elf-as
LD = riscv64-elf-ld
OBJCOPY = riscv64-elf-objcopy
OBJDUMP = riscv64-elf-objdump

ASFLAGS = -march=rv32i -mabi=ilp32
LDFLAGS = -T $(LINK_SCRIPT) -m elf32lriscv

# 目录配置
ifeq ($(CPU),single)
  CPU_DIR = verify/single
  LINK_SCRIPT = link/single_link.ld
else ifeq ($(CPU),pipeline5)
  CPU_DIR = pipeline5/JYD2025_Contest-Template/pipeline5
  LINK_SCRIPT = link/pipeline5_link.ld
endif
ASM_DIR = asm

# 源文件
ifeq ($(CPU),single)
  CPU_SRCS = myCPU1.sv PC.sv NPC.sv RF.sv ALU.sv ACTL.sv \
             Control.sv IMMGEN.sv MEM.sv \
             MUX2_1.sv MUX3_1.sv MUX4_1.sv adder.sv
  TEST_DIR = test
else ifeq ($(CPU),pipeline5)
  CPU_SRCS = myCPU1.sv PC.sv NPC.sv RF.sv ALU.sv ACTL.sv \
             Control.sv IMMGEN.sv MEM.sv \
             MUX2_1.sv MUX3_1.sv MUX4_1.sv adder.sv \
             IF_ID.sv ID_EX.sv EX_MEM.sv MEM_WB.sv \
             Forwarding.sv Hazard_Detection.sv
  TEST_DIR = test
endif

# 目标
BUILD_DIR = build
SIM_TARGET = $(BUILD_DIR)/cpu_tb
HEX_TARGETS = $(BUILD_DIR)/test_simple.hex $(BUILD_DIR)/test_simple.dump

.PHONY: all sim clean hex help single pipeline5

# 默认目标：编译并运行仿真
all: hex sim

# 创建 build 目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 仅编译汇编程序
hex: $(BUILD_DIR) $(HEX_TARGETS)

# 运行仿真
sim: $(SIM_TARGET)
	@echo "====================================="
	@echo "Running simulation ($(CPU) CPU)..."
	@echo "====================================="
	vvp $(SIM_TARGET)

# 编译仿真器
$(SIM_TARGET): $(BUILD_DIR) $(addprefix $(CPU_DIR)/,$(CPU_SRCS)) $(TEST_DIR)/tb_myCPU1.sv $(TEST_DIR)/irom.sv $(TEST_DIR)/dram.sv
	@echo "====================================="
	@echo "Building simulation ($(CPU) CPU)..."
	@echo "====================================="
	iverilog -g2012 -o $@ \
		$(addprefix $(CPU_DIR)/,$(CPU_SRCS)) \
		$(TEST_DIR)/irom.sv \
		$(TEST_DIR)/dram.sv \
		$(TEST_DIR)/tb_myCPU1.sv

# 汇编编译规则
$(BUILD_DIR)/test_simple.o: $(ASM_DIR)/test_simple.s | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/test_simple.elf: $(BUILD_DIR)/test_simple.o
	$(LD) $(LDFLAGS) -o $@ $<

$(BUILD_DIR)/test_simple.hex: $(BUILD_DIR)/test_simple.elf
	$(OBJCOPY) -O verilog --verilog-data-width=4 $< $@.tmp
	grep -v '^@' $@.tmp > $@ || true
	rm -f $@.tmp

$(BUILD_DIR)/test_simple.dump: $(BUILD_DIR)/test_simple.elf
	$(OBJDUMP) -d $< > $@

# 测试所有 CPU
single:
	$(MAKE) CPU=single

pipeline5:
	$(MAKE) CPU=pipeline5

# 清理
clean:
	@echo "Cleaning generated files..."
	rm -rf $(BUILD_DIR)
	@echo "Clean completed!"

# 帮助信息
help:
	@echo "RISC-V CPU 统一测试框架"
	@echo ""
	@echo "用法:"
	@echo "  make CPU=single           - 测试单周期 CPU"
	@echo "  make CPU=pipeline5        - 测试 5 级流水线 CPU"
	@echo "  make all                  - 测试所有 CPU (默认 single)"
	@echo ""
	@echo "  make hex                  - 仅编译汇编程序"
	@echo "  make sim                  - 运行仿真 (需要先编译汇编)"
	@echo "  make clean                - 清理生成的文件"
	@echo ""
	@echo "示例:"
	@echo "  make CPU=single sim           - 运行单周期 CPU 仿真"
	@echo "  make CPU=pipeline5 all        - 编译并运行流水线 CPU 仿真"
