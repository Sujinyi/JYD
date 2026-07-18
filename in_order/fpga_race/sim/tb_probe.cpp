// Quick health probe: run N cycles, sample pc / counter / DRAM-write activity
// every 500k cycles to confirm the image is executing (not stuck/wild).
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();
    uint64_t max_cycles = 20000000;
    const char *p;
    if ((p = ctx->commandArgsPlusMatch("max=")) && *p)
        max_cycles = strtoull(p + 5, nullptr, 0);

    Vstudent_top *dut = new Vstudent_top;
    dut->virtual_sw = 0;
    dut->virtual_key = 0;
    dut->w_clk_rst = 1;
    dut->w_cpu_clk = 0;
    dut->w_clk_50Mhz = 0;
    for (int i = 0; i < 16; i++) {
        dut->w_cpu_clk = !dut->w_cpu_clk;
        if (i % 4 == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();
    }
    dut->w_clk_rst = 0;

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->w_cpu_clk = 0;
        dut->eval();
        dut->w_cpu_clk = 1;
        if ((cyc & 1) == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();

        if (cyc % 500000 == 0) {
            printf("[%9lu] pc=%08x run=%d ms=%u seg=%08x led=%08x\n",
                   (unsigned long)cyc,
                   dut->rootp->student_top__DOT__u_core__DOT__pc_f,
                   (int)dut->rootp->student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run,
                   dut->rootp->student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms,
                   dut->rootp->student_top__DOT__bridge_inst__DOT__seg_wdata_cpu,
                   dut->rootp->student_top__DOT__bridge_inst__DOT__LED_cpu);
        }
    }
    dut->final();
    delete dut;
    return 0;
}
