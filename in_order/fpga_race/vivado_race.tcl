# Usage: vivado -mode batch -source fpga_race/vivado_race.tcl
# Competition platform build: JYD peripherals + dual-issue core @ 200MHz.
# Bitstream: fpga_race/vivado/race.runs/impl_1/top.bit
set proj_dir fpga_race/vivado
set part     xc7k325tffg900-2
set_param general.maxThreads 8

create_project race $proj_dir -part $part -force

add_files [list \
    rtl/core.v rtl/alu.v rtl/regfile_2w.v rtl/decoder.v rtl/muldiv.v \
    fpga_race/rtl/top.sv fpga_race/rtl/student_top.sv fpga_race/rtl/pll.v \
    fpga_race/rtl/perip_bridge.sv fpga_race/rtl/irom3p.v fpga_race/rtl/dram.v \
    fpga_race/rtl/counter.sv fpga_race/rtl/display_seg.sv fpga_race/rtl/seg7.sv \
    fpga_race/rtl/uart.sv fpga_race/rtl/twin_controller.sv \
    build/race/irom.mem build/race/dram.mem]
add_files -fileset constrs_1 fpga_race/constrs/race.xdc

set_property top top [current_fileset]
set_property file_type {Memory Initialization Files} [get_files build/race/irom.mem]
set_property file_type {Memory Initialization Files} [get_files build/race/dram.mem]

# directives: Default everywhere (fast, ~3min). Mid/high-effort recipes were
# probed and rejected on runtime grounds (phys_opt-only: 5min for +0.02;
# +ExtraTimingOpt place: >10min, killed).
set_property STEPS.PHYS_OPT_DESIGN.IS_ENABLED true [get_runs impl_1]

launch_runs synth_1 -jobs 8
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1

open_run impl_1
report_utilization
report_timing_summary -max_paths 3
puts "Bitstream: [glob -nocomplain $proj_dir/race.runs/impl_1/*.bit]"
