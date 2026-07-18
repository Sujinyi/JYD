# EmbedFire ShengTeng Mini, XC7A100T-FGG484-2
create_clock -period 20.000 -name sys_clk [get_ports sys_clk]

set_property PACKAGE_PIN W19 [get_ports sys_clk]
set_property PACKAGE_PIN Y19 [get_ports sys_rst_n]
set_property PACKAGE_PIN V17 [get_ports uart_txd]
set_property PACKAGE_PIN N20 [get_ports {led[0]}]
set_property PACKAGE_PIN M20 [get_ports {led[1]}]
set_property PACKAGE_PIN N22 [get_ports {led[2]}]
set_property PACKAGE_PIN M22 [get_ports {led[3]}]

set_property IOSTANDARD LVCMOS33 [get_ports sys_clk]
set_property IOSTANDARD LVCMOS33 [get_ports sys_rst_n]
set_property IOSTANDARD LVCMOS33 [get_ports uart_txd]
set_property IOSTANDARD LVCMOS33 [get_ports {led[*]}]

set_false_path -from [get_ports sys_rst_n]
set_false_path -to [get_ports {uart_txd led[*]}]
