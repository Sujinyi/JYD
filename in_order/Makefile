RTL := rtl/core.v rtl/alu.v rtl/regfile_2w.v rtl/decoder.v rtl/muldiv.v rtl/top.v
VOBJ := obj_dir/Vtop

CROSS := riscv64-elf-
MARCH := rv32im_zifencei
TESTS_DIR := riscv-tests/isa/rv32ui
BUILD := build/tests
TEST_SRCS := $(filter-out $(TESTS_DIR)/ma_data.S,$(wildcard $(TESTS_DIR)/*.S)) $(wildcard riscv-tests/isa/rv32um/*.S) $(wildcard tests/*.S)
TEST_NAMES := $(basename $(notdir $(TEST_SRCS)))
TEST_BINS := $(addprefix $(BUILD)/,$(addsuffix .bin,$(TEST_NAMES)))

CSRC_DIR := csrc
CBUILD := build/csrc
C_SRCS := $(wildcard $(CSRC_DIR)/tests/*.c)
C_NAMES := $(basename $(notdir $(C_SRCS)))
C_BINS := $(addprefix $(CBUILD)/,$(addsuffix .bin,$(C_NAMES)))
CFLAGS := -march=$(MARCH) -mabi=ilp32 -O2 -static -nostdlib -nostartfiles \
  -ffreestanding -mcmodel=medany -I$(CSRC_DIR)/crt

FPGA_RTL := rtl/core.v rtl/alu.v rtl/regfile_2w.v rtl/decoder.v rtl/muldiv.v \
  fpga/rtl/uart_tx.v fpga/rtl/fpga_top.v
FBUILD := build/fpga
FSW_SRCS := $(wildcard fpga/sw/*.c)
FSW_NAMES := $(filter-out putc_uart,$(basename $(notdir $(FSW_SRCS))))
FSW_MEMS := $(addprefix $(FBUILD)/,$(addsuffix .mem,$(FSW_NAMES)))

.PHONY: all sim tests run clean ctests crun fpga-sw fpga-sim
.SECONDARY:

all: sim tests

sim: $(VOBJ)

$(VOBJ): $(RTL) sim/main.cpp sim/golden.h
	verilator --cc --exe --build -O2 -Wall -Wno-UNUSEDSIGNAL -Wno-DECLFILENAME \
	  --trace --top-module top $(RTL) ../sim/main.cpp -o Vtop
	@touch $@

$(BUILD)/%.elf: $(TESTS_DIR)/%.S tests/env/riscv_test.h tests/env/link.ld
	@mkdir -p $(BUILD)
	$(CROSS)gcc -march=$(MARCH) -mabi=ilp32 -static -nostdlib -nostartfiles \
	  -mcmodel=medany -fvisibility=hidden \
	  -Itests/env -Iriscv-tests/isa/macros/scalar \
	  -Ttests/env/link.ld $< -o $@

$(BUILD)/%.elf: riscv-tests/isa/rv32um/%.S tests/env/riscv_test.h tests/env/link.ld
	@mkdir -p $(BUILD)
	$(CROSS)gcc -march=$(MARCH) -mabi=ilp32 -static -nostdlib -nostartfiles \
	  -mcmodel=medany -fvisibility=hidden \
	  -Itests/env -Iriscv-tests/isa/macros/scalar \
	  -Ttests/env/link.ld $< -o $@

$(BUILD)/%.elf: tests/%.S tests/env/riscv_test.h tests/env/link.ld
	@mkdir -p $(BUILD)
	$(CROSS)gcc -march=$(MARCH)_zicsr -mabi=ilp32 -static -nostdlib -nostartfiles \
	  -mcmodel=medany -fvisibility=hidden \
	  -Itests/env -Iriscv-tests/isa/macros/scalar \
	  -Ttests/env/link.ld $< -o $@

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(CROSS)objcopy -O binary $< $@

tests: $(TEST_BINS)

$(CBUILD)/%.elf: $(CSRC_DIR)/tests/%.c $(CSRC_DIR)/crt/start.S $(CSRC_DIR)/crt/runtime.c $(CSRC_DIR)/crt/putc_sim.c $(CSRC_DIR)/crt/link.ld
	@mkdir -p $(CBUILD)
	$(CROSS)gcc $(CFLAGS) -T$(CSRC_DIR)/crt/link.ld \
	  $(CSRC_DIR)/crt/start.S $(CSRC_DIR)/crt/runtime.c $(CSRC_DIR)/crt/putc_sim.c $< -o $@

$(CBUILD)/%.bin: $(CBUILD)/%.elf
	$(CROSS)objcopy -O binary $< $@

ctests: $(C_BINS)

crun: sim ctests
	@bash run_ctests.sh

# ---------------- FPGA ----------------
$(FBUILD)/%.elf: fpga/sw/%.c $(CSRC_DIR)/crt/start.S $(CSRC_DIR)/crt/runtime.c fpga/sw/putc_uart.c fpga/sw/board.h fpga/sw/link.ld
	@mkdir -p $(FBUILD)
	$(CROSS)gcc $(CFLAGS) -Ifpga/sw -Tfpga/sw/link.ld \
	  $(CSRC_DIR)/crt/start.S $(CSRC_DIR)/crt/runtime.c fpga/sw/putc_uart.c $< -o $@

$(FBUILD)/%.bin: $(FBUILD)/%.elf
	$(CROSS)objcopy -O binary $< $@

$(FBUILD)/%.mem: $(FBUILD)/%.bin
	python3 fpga/sw/bin2mem.py $< $@

fpga-sw: $(FSW_MEMS)

fpga-sim: fpga-sw $(FPGA_RTL) fpga/sim/tb.cpp
	verilator --cc --exe --build -O2 -Wall -Wno-UNUSEDSIGNAL -Wno-DECLFILENAME -Wno-PINCONNECTEMPTY \
	  --Mdir obj_dir_fpga --top-module fpga_top $(FPGA_RTL) ../fpga/sim/tb.cpp -o Vfpga_top

# ---------------- competition platform (Genesys 2, JYD peripherals) ----------------
RACE_RTL := rtl/core.v rtl/alu.v rtl/regfile_2w.v rtl/decoder.v rtl/muldiv.v \
            fpga_race/rtl/student_top.sv fpga_race/rtl/perip_bridge.sv \
            fpga_race/rtl/irom3p.v fpga_race/rtl/dram.v \
            fpga_race/rtl/counter.sv fpga_race/rtl/display_seg.sv fpga_race/rtl/seg7.sv

build/race/irom.mem: jyd_rv32im/coe/withM48/irom-new.coe fpga_race/coe2mem.py
	@mkdir -p build/race
	python3 fpga_race/coe2mem.py $< $@ 4096

build/race/dram.mem: jyd_rv32im/coe/withM48/dram.coe fpga_race/coe2mem.py
	@mkdir -p build/race
	python3 fpga_race/coe2mem.py $< $@ 65536

race-mem: build/race/irom.mem build/race/dram.mem

race-sim: race-mem $(RACE_RTL) fpga_race/sim/tb_race.cpp
	verilator --cc --exe --build -O2 -CFLAGS "-O3 -march=native" \
	  -Wall -Wno-UNUSEDSIGNAL -Wno-DECLFILENAME -Wno-PINCONNECTEMPTY \
	  -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC -Wno-EOFNEWLINE -Wno-TIMESCALEMOD \
	  -Wno-UNUSEDPARAM -Wno-SYNCASYNCNET \
	  --Mdir obj_dir_race --top-module student_top \
	  -GIROM_MEM='"build/race/irom.mem"' -GDRAM_MEM='"build/race/dram.mem"' \
	  $(RACE_RTL) ../fpga_race/sim/tb_race.cpp -o Vrace

run: sim tests
	@bash run_tests.sh

clean:
	rm -rf obj_dir obj_dir_fpga obj_dir_race build
