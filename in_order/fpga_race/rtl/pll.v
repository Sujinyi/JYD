// PLL wrapper, port-compatible with the JYD Vivado clocking-wizard IP.
// 200MHz LVDS input -> clk_out1 = 50MHz (peripherals / ms counter / uart),
//                      clk_out2 = 200MHz CPU clock.
module pll (
    input  wire clk_in1_p,
    input  wire clk_in1_n,
    output wire clk_out1,
    output wire clk_out2,
    output wire locked
);
`ifdef VERILATOR
    // Verilator sim drives student_top clocks directly; pll unused.
    assign clk_out1 = clk_in1_p;
    assign clk_out2 = clk_in1_p;
    assign locked   = 1'b1;
`else
    wire clk_ibuf, clk_fb;
    wire clk0_raw, clk1_raw;

    IBUFDS u_ibufds (
        .I (clk_in1_p),
        .IB(clk_in1_n),
        .O (clk_ibuf)
    );

    MMCME2_BASE #(
        .CLKIN1_PERIOD   (5.000),    // 200MHz in
        .CLKFBOUT_MULT_F (5.500),    // VCO = 1100MHz
        .CLKOUT0_DIVIDE_F(22.000),   // 1100/22 = 50MHz  peripheral clock
        .CLKOUT1_DIVIDE  (5),        // 1100/5  = 220MHz cpu clock
        .DIVCLK_DIVIDE   (1)
    ) u_mmcm (
        .CLKIN1  (clk_ibuf),
        .CLKFBIN (clk_fb),
        .CLKFBOUT(clk_fb),
        .CLKOUT0 (clk0_raw),
        .CLKOUT1 (clk1_raw),
        .CLKOUT0B(), .CLKOUT1B(), .CLKOUT2(), .CLKOUT2B(),
        .CLKOUT3(), .CLKOUT3B(), .CLKOUT4(), .CLKOUT5(), .CLKOUT6(),
        .CLKFBOUTB(),
        .LOCKED  (locked),
        .PWRDWN  (1'b0),
        .RST     (1'b0)
    );

    BUFG u_bufg0 (.I(clk0_raw), .O(clk_out1));
    BUFG u_bufg1 (.I(clk1_raw), .O(clk_out2));
`endif
endmodule
