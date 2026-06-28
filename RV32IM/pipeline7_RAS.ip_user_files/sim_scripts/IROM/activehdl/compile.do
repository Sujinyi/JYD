transcript off
onbreak {quit -force}
onerror {quit -force}
transcript on

vlib work
vlib activehdl/xpm
vlib activehdl/blk_mem_gen_v8_4_12
vlib activehdl/xil_defaultlib

vmap xpm activehdl/xpm
vmap blk_mem_gen_v8_4_12 activehdl/blk_mem_gen_v8_4_12
vmap xil_defaultlib activehdl/xil_defaultlib

vlog -work xpm  -sv2k12 "+incdir+E:/Vivado25/2025.2.1/Vivado/data/rsb/busdef" -l xpm -l blk_mem_gen_v8_4_12 -l xil_defaultlib \
"E:/Vivado25/2025.2.1/Vivado/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"E:/Vivado25/2025.2.1/Vivado/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93  \
"E:/Vivado25/2025.2.1/Vivado/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work blk_mem_gen_v8_4_12  -v2k5 "+incdir+E:/Vivado25/2025.2.1/Vivado/data/rsb/busdef" -l xpm -l blk_mem_gen_v8_4_12 -l xil_defaultlib \
"../../../ipstatic/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+E:/Vivado25/2025.2.1/Vivado/data/rsb/busdef" -l xpm -l blk_mem_gen_v8_4_12 -l xil_defaultlib \
"../../../../../pipeline7_RAS/pipeline7_RAS.gen/sources_1/ip/IROM/sim/IROM.v" \

vlog -work xil_defaultlib \
"glbl.v"

