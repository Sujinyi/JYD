# Digilent Genesys 2, XC7K325T-2FFG900C
# 200MHz differential system clock, bank 33
create_clock -period 5.000 -name sys_clk [get_ports sys_clk_p]

set_property PACKAGE_PIN AD12 [get_ports sys_clk_p]
set_property PACKAGE_PIN AD11 [get_ports sys_clk_n]
set_property IOSTANDARD LVDS [get_ports sys_clk_p]
set_property IOSTANDARD LVDS [get_ports sys_clk_n]

# CPU RESET button (active low)
set_property PACKAGE_PIN R19 [get_ports sys_rst_n]
set_property IOSTANDARD LVCMOS33 [get_ports sys_rst_n]

# USB-UART bridge: FPGA TX -> FT232R RXD -> PC
set_property PACKAGE_PIN Y23 [get_ports uart_txd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_txd]

# User LEDs LD0-3
set_property PACKAGE_PIN T28 [get_ports {led[0]}]
set_property PACKAGE_PIN V19 [get_ports {led[1]}]
set_property PACKAGE_PIN U30 [get_ports {led[2]}]
set_property PACKAGE_PIN U29 [get_ports {led[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led[*]}]

set_false_path -from [get_ports sys_rst_n]
set_false_path -to [get_ports {uart_txd led[*]}]
