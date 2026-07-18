set script_dir [file dirname [file normalize [info script]]]
set race_dir   [file normalize [file join $script_dir ..]]
set xci_path   [file join $race_dir ip IROM IROM.xci]

create_project -in_memory -part xc7k325tffg900-2
read_ip $xci_path
set irom_ip [get_ips IROM]

puts "IROM_MEMORY_TYPE=[get_property CONFIG.Memory_Type $irom_ip]"
puts "IROM_COE_FILE=[get_property CONFIG.Coe_File $irom_ip]"

generate_target synthesis [get_files $xci_path]
puts "IROM_GENERATION_OK"
