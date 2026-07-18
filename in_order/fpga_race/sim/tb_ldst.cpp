// Measure store-to-load forwarding potential: fraction of loads whose address
// matches one of the last N committed stores (N = 1/2/4/8), plus the
// store->load distance histogram. Peeks the dmem command stream (M1 stage).
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();
    uint64_t max_cycles = 150000000;
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

    uint32_t st_addr[16];
    uint64_t st_age[16];
    int st_head = 0;
    for (int i = 0; i < 16; i++) { st_addr[i] = 0xffffffff; st_age[i] = 0; }

    uint64_t loads = 0, hit1 = 0, hit2 = 0, hit4 = 0, hit8 = 0, hit16 = 0;
    uint64_t stores = 0;
    uint64_t dist_hist[6] = {0}; // cycle-distance of hit: 1-2, 3-4, 5-8, 9-16, 17-64, >64

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->w_cpu_clk = 0;
        dut->eval();

        uint32_t wen = dut->rootp->student_top__DOT__u_core__DOT__dmem_wen_r;
        bool ren = dut->rootp->student_top__DOT__u_core__DOT__mem_read_m0 && dut->rootp->student_top__DOT__u_core__DOT__valid_m0;
        uint32_t addr = dut->rootp->student_top__DOT__u_core__DOT__dmem_addr_r & ~3u;

        if (ren) {
            loads++;
            for (int k = 0; k < 16; k++) {
                int idx = (st_head - 1 - k + 32) % 16;
                if (st_addr[idx] == addr) {
                    if (k < 1) hit1++;
                    if (k < 2) hit2++;
                    if (k < 4) hit4++;
                    if (k < 8) hit8++;
                    hit16++;
                    uint64_t d = cyc - st_age[idx];
                    int b = d <= 2 ? 0 : d <= 4 ? 1 : d <= 8 ? 2 : d <= 16 ? 3 : d <= 64 ? 4 : 5;
                    dist_hist[b]++;
                    break;
                }
            }
        }
        if (wen != 0) {
            stores++;
            st_addr[st_head] = addr;
            st_age[st_head] = cyc;
            st_head = (st_head + 1) % 16;
        }

        dut->w_cpu_clk = 1;
        if ((cyc & 1) == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();
    }

    printf("loads=%lu stores=%lu\n", (unsigned long)loads, (unsigned long)stores);
    printf("load addr hits last-N stores:  N=1 %.1f%%  N=2 %.1f%%  N=4 %.1f%%  N=8 %.1f%%  N=16 %.1f%%\n",
           100.0 * hit1 / loads, 100.0 * hit2 / loads, 100.0 * hit4 / loads,
           100.0 * hit8 / loads, 100.0 * hit16 / loads);
    printf("hit distance (cycles): <=2 %.1f%%  3-4 %.1f%%  5-8 %.1f%%  9-16 %.1f%%  17-64 %.1f%%  >64 %.1f%%\n",
           100.0 * dist_hist[0] / hit16, 100.0 * dist_hist[1] / hit16,
           100.0 * dist_hist[2] / hit16, 100.0 * dist_hist[3] / hit16,
           100.0 * dist_hist[4] / hit16, 100.0 * dist_hist[5] / hit16);
    dut->final();
    delete dut;
    return 0;
}
