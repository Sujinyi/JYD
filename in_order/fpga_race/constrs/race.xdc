# Genesys 2 competition constraints - identical pin map to the JYD
# Genesys_riscv_10s.xdc; only the clock definitions are adapted to the
# RTL MMCM inside pll.v (the reference used a clocking-wizard IP).

create_clock -period 5.000 -name sys_clk [get_ports i_sys_clk_p]

# clk_out1 (50MHz peripheral) and clk_out2 (200MHz cpu) are asynchronous
set_clock_groups -asynchronous \
  -group [get_clocks -of_objects [get_pins pll_inst/u_mmcm/CLKOUT0]] \
  -group [get_clocks -of_objects [get_pins pll_inst/u_mmcm/CLKOUT1]]
  
set_property -dict { PACKAGE_PIN AD11  IOSTANDARD LVDS     } [get_ports { i_sys_clk_n }]; #IO_L12N_T1_MRCC_33 Sch=sysclk_n
set_property -dict { PACKAGE_PIN AD12  IOSTANDARD LVDS     } [get_ports { i_sys_clk_p }]; #IO_L12P_T1_MRCC_33 Sch=sysclk_p

# XADC Header
set_property -dict { PACKAGE_PIN J23   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[30] }]; #IO_L1P_T0_AD0P_15 Sch=xadc0r_p
set_property -dict { PACKAGE_PIN K23   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[31] }]; #IO_L3P_T0_DQS_AD1P_15 Sch=xadc1r_p
set_property -dict { PACKAGE_PIN L22   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[35] }]; #IO_L2P_T0_AD8P_15 Sch=xadc8r_p
set_property -dict { PACKAGE_PIN L21   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[34] }]; #IO_L4P_T0_AD9P_15 Sch=xadc9r_p
set_property -dict { PACKAGE_PIN J24   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[32] }]; #IO_L1N_T0_AD0N_15 Sch=xadc0r_n
set_property -dict { PACKAGE_PIN K24   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[37] }]; #IO_L3N_T0_DQS_AD1N_15 Sch=xadc1r_n
set_property -dict { PACKAGE_PIN L23   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[33] }]; #IO_L2N_T0_AD8N_15 Sch=xadc8r_n
set_property -dict { PACKAGE_PIN K21   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[36] }]; #IO_L4N_T0_AD9N_15 Sch=xadc9r_n

# PMOD Header JA

set_property -dict { PACKAGE_PIN U27   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[20] }]; #IO_L13P_T2_MRCC_14 Sch=ja_p[1]
set_property -dict { PACKAGE_PIN U28   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[21] }]; #IO_L13N_T2_MRCC_14 Sch=ja_n[1]
set_property -dict { PACKAGE_PIN T26   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[25] }]; #IO_L12P_T1_MRCC_14 Sch=ja_p[2]
set_property -dict { PACKAGE_PIN T27   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[24] }]; #IO_L12N_T1_MRCC_14 Sch=ja_n[2]
set_property -dict { PACKAGE_PIN T22   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[22] }]; #IO_L5P_T0_D06_14 Sch=ja_p[3]
set_property -dict { PACKAGE_PIN T23   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[27] }]; #IO_L5N_T0_D07_14 Sch=ja_n[3]
set_property -dict { PACKAGE_PIN T20   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[23] }]; #IO_L4P_T0_D04_14 Sch=ja_p[4]
set_property -dict { PACKAGE_PIN T21   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[26] }]; #IO_L4N_T0_D05_14 Sch=ja_n[4]

# PMOD Header JC
set_property -dict { PACKAGE_PIN AC26  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[10] }]; #IO_L19P_T3_13 Sch=jc[1]
set_property -dict { PACKAGE_PIN AJ27  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[11] }]; #IO_L20P_T3_13 Sch=jc[2]
set_property -dict { PACKAGE_PIN AH30  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[15] }]; #IO_L18N_T2_13 Sch=jc[3]
set_property -dict { PACKAGE_PIN AK29  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[14] }]; #IO_L15P_T2_DQS_13 Sch=jc[4]
set_property -dict { PACKAGE_PIN AD26  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[12] }]; #IO_L19N_T3_VREF_13 Sch=jc[7]
set_property -dict { PACKAGE_PIN AG30  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[17] }]; #IO_L18P_T2_13 Sch=jc[8]
set_property -dict { PACKAGE_PIN AK30  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[13] }]; #IO_L15N_T2_DQS_13 Sch=jc[9]
set_property -dict { PACKAGE_PIN AK28  IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[16] }]; #IO_L20N_T3_13 Sch=jc[10]

# PMOD Header JD
set_property -dict { PACKAGE_PIN V27   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[0] }]; #IO_L16N_T2_A15_D31_14 Sch=jd[1]
set_property -dict { PACKAGE_PIN Y30   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[1] }]; #IO_L8P_T1_13 Sch=jd[2]
set_property -dict { PACKAGE_PIN V24   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[5] }]; #IO_L23N_T3_A02_D18_14 Sch=jd[3]
set_property -dict { PACKAGE_PIN W22   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[4] }]; #IO_L24N_T3_A00_D16_14 Sch=jd[4]
set_property -dict { PACKAGE_PIN U24   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[2] }]; #IO_L23P_T3_A03_D19_14 Sch=jd[7]
set_property -dict { PACKAGE_PIN Y26   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[7] }]; #IO_L1P_T0_13 Sch=jd[8]
set_property -dict { PACKAGE_PIN V22   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[3] }]; #IO_L22N_T3_A04_D20_14 Sch=jd[9]
set_property -dict { PACKAGE_PIN W21   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[6] }]; #IO_L24P_T3_A01_D17_14 Sch=jd[10]


# PMOD Header JB
set_property -dict { PACKAGE_PIN V29   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[39] }]; #IO_L17P_T2_A14_D30_14 Sch=jb_p[1]
set_property -dict { PACKAGE_PIN V30   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[29] }]; #IO_L17N_T2_A13_D29_14 Sch=jb_n[1]
set_property -dict { PACKAGE_PIN V25   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[19] }]; #IO_L18P_T2_A12_D28_14 Sch=jb_p[2]
set_property -dict { PACKAGE_PIN W26   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[9] }]; #IO_L18N_T2_A11_D27_14 Sch=jb_n[2]
set_property -dict { PACKAGE_PIN T25   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[38] }]; #IO_L14P_T2_SRCC_14 Sch=jb_p[3]
set_property -dict { PACKAGE_PIN U25   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[28] }]; #IO_L14N_T2_SRCC_14 Sch=jb_n[3]
set_property -dict { PACKAGE_PIN U22   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[18] }]; #IO_L21P_T3_DQS_14 Sch=jb_p[4]
set_property -dict { PACKAGE_PIN U23   IOSTANDARD LVCMOS33 } [get_ports { virtual_seg[8] }]; #IO_L21N_T3_DQS_A06_D22_14 Sch=jb_n[4]


#set_property -dict { PACKAGE_PIN C27   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[0] }]; #IO_L13N_T2_MRCC_16 Sch=fmc_la_n[00]
#set_property -dict { PACKAGE_PIN D27   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[1] }]; #IO_L13P_T2_MRCC_16 Sch=fmc_la_p[00]
set_property -dict { PACKAGE_PIN C26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[2] }]; #IO_L11N_T1_SRCC_16 Sch=fmc_la_n[01]
set_property -dict { PACKAGE_PIN D26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[3] }]; #IO_L11P_T1_SRCC_16 Sch=fmc_la_p[01]
set_property -dict { PACKAGE_PIN G30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[4] }]; #IO_L24N_T3_16 Sch=fmc_la_n[02]
set_property -dict { PACKAGE_PIN H30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[5] }]; #IO_L24P_T3_16 Sch=fmc_la_p[02]
set_property -dict { PACKAGE_PIN E30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[6] }]; #IO_L18N_T2_16 Sch=fmc_la_n[03]
set_property -dict { PACKAGE_PIN E29   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[7] }]; #IO_L18P_T2_16 Sch=fmc_la_p[03]
#set_property -dict { PACKAGE_PIN H27   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[8] }]; #IO_L23N_T3_16 Sch=fmc_la_n[04]
set_property -dict { PACKAGE_PIN H26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[9] }]; #IO_L23P_T3_16 Sch=fmc_la_p[04]
set_property -dict { PACKAGE_PIN A30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[10] }]; #IO_L17N_T2_16 Sch=fmc_la_n[05]
set_property -dict { PACKAGE_PIN B30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[11] }]; #IO_L17P_T2_16 Sch=fmc_la_p[05]
set_property -dict { PACKAGE_PIN C30   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[12] }]; #IO_L16N_T2_16 Sch=fmc_la_n[06]
set_property -dict { PACKAGE_PIN D29   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[13] }]; #IO_L16P_T2_16 Sch=fmc_la_p[06]
set_property -dict { PACKAGE_PIN E25   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[14] }]; #IO_L3N_T0_DQS_16 Sch=fmc_la_n[07]
set_property -dict { PACKAGE_PIN F25   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[15] }]; #IO_L3P_T0_DQS_16 Sch=fmc_la_p[07]
set_property -dict { PACKAGE_PIN B29   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[16] }]; #IO_L15N_T2_DQS_16 Sch=fmc_la_n[08]
#set_property -dict { PACKAGE_PIN C29   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[17] }]; #IO_L15P_T2_DQS_16 Sch=fmc_la_p[08]
set_property -dict { PACKAGE_PIN A28   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[18] }]; #IO_L9N_T1_DQS_16 Sch=fmc_la_n[09]
set_property -dict { PACKAGE_PIN B28   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[19] }]; #IO_L9P_T1_DQS_16 Sch=fmc_la_p[09]
set_property -dict { PACKAGE_PIN A27   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[20] }]; #IO_L7N_T1_16 Sch=fmc_la_n[10]
set_property -dict { PACKAGE_PIN B27   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[21] }]; #IO_L7P_T1_16 Sch=fmc_la_p[10]
set_property -dict { PACKAGE_PIN A26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[22] }]; #IO_L10N_T1_16 Sch=fmc_la_n[11]
set_property -dict { PACKAGE_PIN A25   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[23] }]; #IO_L10P_T1_16 Sch=fmc_la_p[11]

# set_property -dict { PACKAGE_PIN E26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[24] }]; #IO_L5N_T0_16 Sch=fmc_la_n[12]
set_property -dict { PACKAGE_PIN T28   IOSTANDARD LVCMOS33 } [get_ports { virtual_led[26] }]; #IO_L11N_T1_SRCC_14 Sch=led[0]

set_property -dict { PACKAGE_PIN F26   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[25] }]; #IO_L5P_T0_16 Sch=fmc_la_p[12]

# set_property -dict { PACKAGE_PIN D24   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[26] }]; #IO_L4N_T0_16 Sch=fmc_la_n[13]
set_property -dict { PACKAGE_PIN W23   IOSTANDARD LVCMOS33 } [get_ports { virtual_led[28] }]; #IO_L20P_T3_A08_D24_14 Sch=led[7]

set_property -dict { PACKAGE_PIN V19   IOSTANDARD LVCMOS33 } [get_ports { virtual_led[0] }]; #IO_L19P_T3_A10_D26_14 Sch=led[1]
set_property -dict { PACKAGE_PIN U30   IOSTANDARD LVCMOS33 } [get_ports { virtual_led[1] }]; #IO_L15N_T2_DQS_DOUT_CSO_B_14 Sch=led[2]
set_property -dict { PACKAGE_PIN U29   IOSTANDARD LVCMOS33 } [get_ports { virtual_led[8] }]; #IO_L15P_T2_DQS_RDWR_B_14 Sch=led[3]
set_property -dict { PACKAGE_PIN V20   IOSTANDARD LVCMOS33 } [get_ports {virtual_led[17] }]; #IO_L19N_T3_A09_D25_VREF_14 Sch=led[4]
    
set_property -dict { PACKAGE_PIN E24   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[27] }]; #IO_L4P_T0_16 Sch=fmc_la_p[13]
set_property -dict { PACKAGE_PIN B24   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[24] }]; #IO_L8N_T1_16 Sch=fmc_la_n[14]
set_property -dict { PACKAGE_PIN C24   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[29] }]; #IO_L8P_T1_16 Sch=fmc_la_p[14]
set_property -dict { PACKAGE_PIN A23   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[30] }]; #IO_L1N_T0_16 Sch=fmc_la_n[15]
set_property -dict { PACKAGE_PIN B23   IOSTANDARD LVCMOS12 } [get_ports { virtual_led[31] }]; #IO_L1P_T0_16 Sch=fmc_la_p[15]

set_property -dict { PACKAGE_PIN D23   IOSTANDARD LVCMOS12 } [get_ports  i_uart_rx ]; #IO_L2N_T0_16 Sch=fmc_la_n[16]
set_property -dict { PACKAGE_PIN E23   IOSTANDARD LVCMOS12 } [get_ports  o_uart_tx ]; #IO_L2P_T0_16 Sch=fmc_la_p[16]

# set_property -dict { PACKAGE_PIN E21   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[20] }]; #IO_L11N_T1_SRCC_17 Sch=fmc_la_n[17]
# set_property -dict { PACKAGE_PIN F21   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[21] }]; #IO_L11P_T1_SRCC_17 Sch=fmc_la_p[17]
# set_property -dict { PACKAGE_PIN D18   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[22] }]; #IO_L13N_T2_MRCC_17 Sch=fmc_la_n[18]
# set_property -dict { PACKAGE_PIN D17   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[23] }]; #IO_L13P_T2_MRCC_17 Sch=fmc_la_p[18]
# set_property -dict { PACKAGE_PIN H22   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[24] }]; #IO_L7N_T1_17 Sch=fmc_la_n[19]
# set_property -dict { PACKAGE_PIN H21   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[25] }]; #IO_L7P_T1_17 Sch=fmc_la_p[19]
# set_property -dict { PACKAGE_PIN F22   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[26] }]; #IO_L9N_T1_DQS_17 Sch=fmc_la_n[20]
# set_property -dict { PACKAGE_PIN G22   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[27] }]; #IO_L9P_T1_DQS_17 Sch=fmc_la_p[20]
# set_property -dict { PACKAGE_PIN L18   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[28] }]; #IO_L5N_T0_17 Sch=fmc_la_n[21]
# set_property -dict { PACKAGE_PIN L17   IOSTANDARD LVCMOS12 } [get_ports { virtual_seg[29] }]; #IO_L5P_T0_17 Sch=fmc_la_p[21]

# ---- [7] floorplan: confine student_top to a compact 2x2 clock-region
# window. Y3Y4 won the 220MHz window lottery: Y2Y3 -0.265 / Y1Y2 -0.405 /
# Y4Y5 -0.419 / 2x1 -0.405 / Y3Y4 -0.249 (Default directive).
create_pblock pb_cpu
add_cells_to_pblock [get_pblocks pb_cpu] [get_cells student_top_inst]
resize_pblock [get_pblocks pb_cpu] -add {CLOCKREGION_X0Y3:CLOCKREGION_X1Y4}
