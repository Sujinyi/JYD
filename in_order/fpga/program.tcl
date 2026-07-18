# Usage: vivado -mode batch -source fpga/program.tcl [-tclargs <bitfile>]
set bit fpga/vivado/rv32i.runs/impl_1/fpga_top.bit
if { $argc >= 1 } { set bit [lindex $argv 0] }

open_hw_manager
connect_hw_server
open_hw_target
set dev [lindex [get_hw_devices xc7k325t*] 0]
current_hw_device $dev
set_property PROGRAM.FILE $bit $dev
program_hw_devices $dev
puts "Programmed: $bit"
close_hw_manager
