# 假设你想挑战 100MHz (周期 10.0ns)
create_clock -period 9.840 -name vloop_clk -waveform {0.000 4.920} [get_ports w_cpu_clk]

# 因为没有真正的 IO 物理引脚（现在是虚设的顶层），
# 为了避免 IO 延时报告太乱，可以加一句（可选）：
# set_property HD.CLK_SRC BUFGCTRL_X0Y0 [get_ports w_cpu_clk]

