// Optimization-sizing statistics on the competition platform (irom-v2):
// ret dynamic frequency, idr bubble cycles, ldhz split (mul / EX-load /
// M1-load-miss), lui+addi fusable pairs. Reads perf_probe3.
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();
    uint64_t max_cycles = 520000000;
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

    uint64_t cy = 0, inst = 0;
    uint64_t ret_iss = 0, idr_cyc = 0, hz_mul = 0, hz_lde = 0, hz_ldm = 0;
    uint64_t fuse_cyc = 0, ret_head = 0, hz_any = 0, mul2mul = 0;

    for (uint64_t c = 0; c < max_cycles; c++) {
        dut->w_cpu_clk = 0;
        dut->eval();
        uint16_t pr  = dut->rootp->student_top__DOT__u_core__DOT__perf_probe;
        uint8_t  pr3 = dut->rootp->student_top__DOT__u_core__DOT__perf_probe3;
        cy++;
        if (pr & 1) inst++;
        if (pr & 2) inst++;
        if (pr & 16) hz_any++;          // hz0
        if (pr3 & 1)   ret_iss++;
        if (pr3 & 2)   idr_cyc++;
        if (pr3 & 4)   hz_mul++;
        if (pr3 & 8)   hz_lde++;
        if (pr3 & 16)  hz_ldm++;
        if (pr3 & 32)  mul2mul++;
        if (pr3 & 64)  fuse_cyc++;
        if (pr3 & 128) ret_head++;
        dut->w_cpu_clk = 1;
        if ((c & 1) == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();
    }

    double di = (double)inst;
    printf("cycles=%lu instrs=%lu CPI=%.3f\n",
           (unsigned long)cy, (unsigned long)inst, (double)cy / di);
    printf("ret issued        : %10lu  (1 per %.0f instrs; ~2-bubble each -> %.4f CPI)\n",
           (unsigned long)ret_iss, di / ret_iss, 2.0 * ret_iss / di);
    printf("idr bubble cycles : %10lu  (%.4f CPI: ret + cold jal/btfn redirects)\n",
           (unsigned long)idr_cyc, 2.0 * idr_cyc / di);
    printf("hz0 cycles        : %10lu  (%.4f CPI raw)\n",
           (unsigned long)hz_any, 2.0 * hz_any / di);
    printf("  blocked by mul       : %8lu  (%.4f CPI)  -> D1 upper bound\n",
           (unsigned long)hz_mul, 2.0 * hz_mul / di);
    printf("    mul@M1 blocking a muldiv consumer: %8lu (%.4f CPI) -> E1 upper bound\n",
           (unsigned long)mul2mul, 2.0 * mul2mul / di);
    printf("  blocked by EX load   : %8lu  (%.4f CPI)  (inherent distance>=2)\n",
           (unsigned long)hz_lde, 2.0 * hz_lde / di);
    printf("  blocked by M1 miss   : %8lu  (%.4f CPI)  (DRAM-path loads)\n",
           (unsigned long)hz_ldm, 2.0 * hz_ldm / di);
    printf("lui+addi pair cycles: %9lu  (%.4f CPI if fused)  -> B1 upper bound\n",
           (unsigned long)fuse_cyc, 2.0 * fuse_cyc / di);
    printf("ret at queue head  : %10lu\n", (unsigned long)ret_head);
    delete dut;
    return 0;
}
