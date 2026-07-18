// Per-test CPI attribution for the withM48 competition image.
// Segments by fetch pc (pc_f) against the smoke8 symbol map; decodes the
// core's perf_probe every cycle into a per-segment loss stack.
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
#include <cstring>

struct Seg {
    const char *name;
    uint32_t lo, hi;
    uint64_t cycles = 0, i0 = 0, i1 = 0;
    uint64_t l_ms = 0, l_hz = 0, l_br = 0, l_jr = 0, l_cold = 0, l_fetch = 0;
    uint64_t s_nov1 = 0, s_ctrl = 0, s_struct = 0, s_dep = 0, s_hz1 = 0;
    uint64_t st_ldst = 0, st_md = 0, dep_ld = 0, dep_alu = 0;
};

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();
    uint64_t max_cycles = 120000000;
    const char *p;
    if ((p = ctx->commandArgsPlusMatch("max=")) && *p)
        max_cycles = strtoull(p + 5, nullptr, 0);

    Seg segs[] = {
        {"matrix_80x80",  0x80001088, 0x80001373},
        {"crc16",         0x80001374, 0x8000150b},
        {"bubble_sort",   0x8000150c, 0x80001797},
        {"prime_count",   0x80001798, 0x800018ab},
        {"state_machine", 0x800018ac, 0x80001acb},
        {"array_transf",  0x80001acc, 0x80001c6f},
        {"linked_walk",   0x80001c70, 0x80001dfb},
        {"bit_mix",       0x80001dfc, 0x80001edf},
        {"other",         0x00000000, 0xffffffff},
    };
    const int NSEG = sizeof(segs) / sizeof(segs[0]);

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

    int pending = 0;
    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->w_cpu_clk = 0;
        dut->eval();

        uint32_t pc = dut->rootp->student_top__DOT__u_core__DOT__pc_f;
        uint16_t pr = dut->rootp->student_top__DOT__u_core__DOT__perf_probe;
        Seg *sg = &segs[NSEG - 1];
        for (int i = 0; i < NSEG; i++)
            if (pc >= segs[i].lo && pc <= segs[i].hi) { sg = &segs[i]; break; }

        bool issue0 = pr & 1, issue1 = pr & 2, v0 = pr & 4, v1 = pr & 8;
        bool hz0 = pr & 16, hz1 = pr & 32, ms = pr & 64, rfl = pr & 128;
        bool exmis = pr & 256, exjr = pr & 512, exfen = pr & 1024, idred = pr & 2048;
        bool i1simple = pr & 4096, i0ctrl = pr & 8192, dep01 = pr & 16384;
        bool i1_ldst = pr & 32768;
        uint8_t pr2 = dut->rootp->student_top__DOT__u_core__DOT__perf_probe2;
        bool raw_ld = pr2 & 1, i1_md = pr2 & 2;

        sg->cycles++;
        if (issue0) sg->i0++;
        if (issue1) sg->i1++;
        if (issue0) pending = 0;
        if (exmis) pending = 1;
        else if (exjr) pending = 2;
        else if (exfen) pending = 3;
        if (idred && !pending) pending = 4;

        int lost = 2 - (int)issue0 - (int)issue1;
        if (lost) {
            if (ms) sg->l_ms += lost;
            else if (exmis || exjr || exfen || rfl || (!v0 && pending)) {
                int c = exmis ? 1 : exjr ? 2 : exfen ? 3 : pending;
                if (c == 1) sg->l_br += lost;
                else if (c == 2) sg->l_jr += lost;
                else if (c == 4) sg->l_cold += lost;
                else sg->l_fetch += lost;
            } else if (!v0) sg->l_fetch += lost;
            else if (hz0) sg->l_hz += lost;
            else {
                if (!v1) sg->s_nov1 += lost;
                else if (i0ctrl) sg->s_ctrl += lost;
                else if (!i1simple) {
                    sg->s_struct += lost;
                    if (i1_ldst) sg->st_ldst += lost;
                    else if (i1_md) sg->st_md += lost;
                }
                else if (dep01) {
                    sg->s_dep += lost;
                    if (raw_ld) sg->dep_ld += lost;
                    else sg->dep_alu += lost;
                }
                else if (hz1) sg->s_hz1 += lost;
                else sg->l_fetch += lost;
            }
        }

        dut->w_cpu_clk = 1;
        if ((cyc & 1) == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();
    }

    printf("%-14s %10s %8s %6s | %6s %6s %6s %6s | %6s %6s %6s %6s\n",
           "segment", "cycles", "instrs", "CPI",
           "ldhz", "strct", "dep", "rest",
           "st:ls", "st:md", "dep:ld", "dep:alu");
    for (int i = 0; i < NSEG; i++) {
        Seg &s = segs[i];
        uint64_t inst = s.i0 + s.i1;
        if (!s.cycles || !inst) continue;
        double di = 2.0 * (double)inst;
        printf("%-14s %10lu %8lu %6.3f | %6.3f %6.3f %6.3f %6.3f | %6.3f %6.3f %6.3f %6.3f\n",
               s.name, (unsigned long)s.cycles, (unsigned long)inst,
               (double)s.cycles / (double)inst,
               s.l_hz / di, s.s_struct / di, s.s_dep / di,
               (s.l_ms + s.l_br + s.l_jr + s.l_fetch + s.l_cold + s.s_nov1 + s.s_ctrl + s.s_hz1) / di,
               s.st_ldst / di, s.st_md / di, s.dep_ld / di, s.dep_alu / di);
    }
    dut->final();
    delete dut;
    return 0;
}
