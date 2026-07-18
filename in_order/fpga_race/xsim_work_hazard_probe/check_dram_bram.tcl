open_checkpoint {C:/Users/21186/Desktop/CICC2026/in_order/fpga_race/vivado/race.runs/synth_1/top.dcp}
set dram_cells [get_cells -hier -filter {NAME =~ *Mem_DRAM* && REF_NAME =~ RAMB*}]
puts "DRAM_BRAM_COUNT=[llength $dram_cells]"
set casc_a 0
set casc_b 0
set first_cell [lindex $dram_cells 0]
puts "DRAM_FIRST_CELL=$first_cell"
puts "DRAM_CASCADE_PROPERTIES=[list_property $first_cell -regexp {.*CASCADE.*}]"
puts "DRAM_CASCADE_ORDER_A_FIRST=[get_property CASCADE_ORDER_A $first_cell]"
puts "DRAM_CASCADE_ORDER_B_FIRST=[get_property CASCADE_ORDER_B $first_cell]"
puts "DRAM_CASCADE_HEIGHT_FIRST=[get_property CASCADE_HEIGHT $first_cell]"
puts "DRAM_BLOCK_SYNTH_CASCADE_HEIGHT_FIRST=[get_property BLOCK_SYNTH.CASCADE_HEIGHT $first_cell]"
puts "DRAM_BLOCK_SYNTH_LUT_CASCADE_FIRST=[get_property BLOCK_SYNTH.LUT_CASCADE $first_cell]"
set cascade_pins [get_pins -quiet -of_objects $dram_cells -filter {REF_PIN_NAME =~ CASCADE*}]
set cascade_connected 0
foreach p $cascade_pins {
    if {[llength [get_nets -quiet -of_objects $p]] > 0} {incr cascade_connected}
}
puts "DRAM_CASCADE_PIN_COUNT=[llength $cascade_pins]"
puts "DRAM_CASCADE_CONNECTED_PIN_COUNT=$cascade_connected"
foreach pin_name {CASCADEINA CASCADEINB CASCADEOUTA CASCADEOUTB} {
    set named_pins [get_pins -quiet -of_objects $dram_cells -filter "REF_PIN_NAME == $pin_name"]
    set named_connected 0
    foreach p $named_pins {
        if {[llength [get_nets -quiet -of_objects $p]] > 0} {incr named_connected}
    }
    puts "DRAM_${pin_name}_CONNECTED=$named_connected/[llength $named_pins]"
}
foreach c $dram_cells {
    if {[get_property CASCADE_ORDER_A $c] ne "NONE"} {incr casc_a}
    if {[get_property CASCADE_ORDER_B $c] ne "NONE"} {incr casc_b}
}
puts "DRAM_CASCADE_A_NON_NONE=$casc_a"
puts "DRAM_CASCADE_B_NON_NONE=$casc_b"
close_design
exit
