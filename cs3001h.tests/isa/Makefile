#=======================================================================
# Makefile for rv32mi isa
#-----------------------------------------------------------------------

SRC_DIR := ./rv32mi
INC_DIR := ./
LINK_FILE := ./link.ld

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= riscv64-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -march=rv32i -mabi=ilp32 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles
RISCV_OBJCOPY ?= $(RISCV_PREFIX)objcopy
RISCV_OBJCOPY_OPTS ?= -O binary
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump
RISCV_OBJDUMP_OPTS ?= -M no-aliases,numeric --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data

#------------------------------------------------------------
# Build tests
#------------------------------------------------------------

OBJS := $(subst .S,.o,$(wildcard $(SRC_DIR)/*.S))
COES := $(subst .S,.coe,$(wildcard $(SRC_DIR)/*.S))
BINS := $(subst .S,.bin,$(wildcard $(SRC_DIR)/*.S))
DUMPS := $(subst .S,.dump,$(wildcard $(SRC_DIR)/*.S))
HEXS := $(foreach obj,$(OBJS),$(obj:.o=_text.hex) $(obj:.o=_data.hex))

all: $(DUMPS) $(COES) $(BINS) $(OBJS) hex

.PHONY: hex
hex: $(OBJS)
	@echo "Generating HEX files..."
	@for obj in $(OBJS); do \
		python3 generate_hex.py $$obj $(SRC_DIR)/ || exit 1; \
	done

%.dump: %.o
	$(RISCV_OBJDUMP) $(RISCV_OBJDUMP_OPTS) $< > $@

%.coe: %.bin bin2coe
	./bin2coe $< $@

%.bin: %.o
	$(RISCV_OBJCOPY) $(RISCV_OBJCOPY_OPTS) $< $@

%.o: %.S
	$(RISCV_GCC) $(RISCV_GCC_OPTS) -I $(INC_DIR) -T $(LINK_FILE) -o $@ $<

bin2coe: ../tools/bin2coe.cpp
	g++ ../tools/bin2coe.cpp -o bin2coe

#------------------------------------------------------------
# Clean up
#------------------------------------------------------------

.PHONY: clean
clean:
	rm -rf $(SRC_DIR)/*.dump $(SRC_DIR)/*.bin $(SRC_DIR)/*.coe $(SRC_DIR)/*.o $(SRC_DIR)/*_text.hex $(SRC_DIR)/*_data.hex bin2coe
