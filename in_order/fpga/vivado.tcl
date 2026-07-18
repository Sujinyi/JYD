# Usage: vivado -mode batch -source fpga/vivado.tcl [-tclargs <prog.mem>]
# Creates project, runs synth+impl, writes bitstream to fpga/vivado/rv32i.runs/impl_1/
set proj_dir  fpga/vivado
set part      xc7k325tffg900-2
set mem_file  build/fpga/led.mem
if { $argc >= 1 } { set mem_file [lindex $argv 0] }
set mem_file [file normalize $mem_file]

create_project rv32i $proj_dir -part $part -force

add_files [list \
    rtl/core.v rtl/alu.v rtl/regfile_2w.v rtl/decoder.v \
    fpga/rtl/uart_tx.v fpga/rtl/fpga_top.v rtl/muldiv.v]
add_files -fileset constrs_1 fpga/constrs/genesys2.xdc

set_property top fpga_top [current_fileset]
set_property generic "MEM_FILE0=\"${mem_file}0\" MEM_FILE1=\"${mem_file}1\"" [current_fileset]

# high-effort timing closure
set_property STEPS.SYNTH_DESIGN.ARGS.DIRECTIVE PerformanceOptimized [get_runs synth_1]
set_property STEPS.OPT_DESIGN.ARGS.DIRECTIVE ExploreWithRemap [get_runs impl_1]
set_property STEPS.PLACE_DESIGN.ARGS.DIRECTIVE ExtraTimingOpt [get_runs impl_1]
set_property STEPS.PHYS_OPT_DESIGN.IS_ENABLED true [get_runs impl_1]
set_property STEPS.PHYS_OPT_DESIGN.ARGS.DIRECTIVE AggressiveExplore [get_runs impl_1]
set_property STEPS.ROUTE_DESIGN.ARGS.DIRECTIVE Explore [get_runs impl_1]
set_property STEPS.POST_ROUTE_PHYS_OPT_DESIGN.IS_ENABLED true [get_runs impl_1]
set_property STEPS.POST_ROUTE_PHYS_OPT_DESIGN.ARGS.DIRECTIVE AggressiveExplore [get_runs impl_1]

launch_runs synth_1 -jobs 8
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1

open_run impl_1
report_utilization
report_timing_summary -max_paths 3
puts "Bitstream: [glob -nocomplain $proj_dir/rv32i.runs/impl_1/*.bit]"
