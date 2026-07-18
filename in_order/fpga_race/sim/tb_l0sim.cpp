// L0 D$ potential: simulate direct-mapped word-line caches (2/4/8/16KB)
// on the dmem command stream (M1 stage), on top of the existing 4-entry
// store-forward buffer. Reports lw hit rates: total, and INCREMENTAL
// (L0 hit among sf-miss loads) -- the latter is the real gain.
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
#include <cstring>

struct L0 {
    uint32_t lines;          // number of word lines (power of 2)
    uint32_t *tag;           // word address >> log2(lines)
    bool *v;
    uint64_t hit = 0;
    uint64_t hit_sfmiss = 0;
    L0(uint32_t n) : lines(n) {
        tag = new uint32_t[n];
        v = new bool[n]();
    }
    uint32_t idx(uint32_t wa) const { return wa & (lines - 1); }
    uint32_t tg(uint32_t wa) const { return wa / lines; }
    bool look(uint32_t wa) const { return v[idx(wa)] && tag[idx(wa)] == tg(wa); }
    void fill(uint32_t wa) { v[idx(wa)] = true; tag[idx(wa)] = tg(wa); }
    void inval(uint32_t wa) { if (look(wa)) v[idx(wa)] = false; }
};

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

    // model of the existing 4-entry sf buffer (word stores, round-robin,
    // sb/sh flush) so we can measure the L0 gain on top of it
    uint32_t sf_addr[4] = {~0u, ~0u, ~0u, ~0u};
    int sf_wp = 0;

    L0 c512(512), c1k(1024), c2k(2048), c4k(4096); // 2/4/8/16KB
    L0 *cs[4] = {&c512, &c1k, &c2k, &c4k};

    uint64_t lw = 0, lw_sfhit = 0, ld_other = 0, stores = 0;

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->w_cpu_clk = 0;
        dut->eval();

        uint32_t wen  = dut->rootp->student_top__DOT__u_core__DOT__dmem_wen_r;
        bool     ren  = dut->rootp->student_top__DOT__u_core__DOT__mem_read_m0 &&
                        dut->rootp->student_top__DOT__u_core__DOT__valid_m0;
        uint32_t addr = dut->rootp->student_top__DOT__u_core__DOT__dmem_addr_r;
        uint32_t f3   = dut->rootp->student_top__DOT__u_core__DOT__mem_funct3_m0 & 7;
        bool dram = ((addr >> 20) == 0x801);
        uint32_t wa = (addr & ~3u) >> 2;

        if (ren && dram) {
            bool sfh = false;
            for (int k = 0; k < 4; k++) sfh |= (sf_addr[k] == wa);
            if (f3 == 2) {
                lw++;
                if (sfh) lw_sfhit++;
                for (auto *c : cs) {
                    if (c->look(wa)) {
                        c->hit++;
                        if (!sfh) c->hit_sfmiss++;
                    }
                }
            } else ld_other++;
            for (auto *c : cs) c->fill(wa); // any load fills (word line)
        } else if (wen && dram) {
            stores++;
            if (wen == 0xF) {
                sf_addr[sf_wp] = wa; sf_wp = (sf_wp + 1) & 3;
                for (auto *c : cs) c->fill(wa);        // store-allocate
            } else {
                for (int k = 0; k < 4; k++) sf_addr[k] = ~0u; // sf flush
                for (auto *c : cs) c->inval(wa);       // conservative line kill
            }
        }

        dut->w_cpu_clk = 1;
        dut->eval();
    }

    printf("lw=%lu  sf-hit=%.1f%%  other-loads=%lu  stores=%lu\n",
           (unsigned long)lw, 100.0 * lw_sfhit / (lw ? lw : 1),
           (unsigned long)ld_other, (unsigned long)stores);
    const char *nm[4] = {"2KB", "4KB", "8KB", "16KB"};
    for (int i = 0; i < 4; i++)
        printf("L0 %-4s: total %.1f%%   incremental(on sf-miss) %.1f%% of all lw\n",
               nm[i], 100.0 * cs[i]->hit / (lw ? lw : 1),
               100.0 * cs[i]->hit_sfmiss / (lw ? lw : 1));
    delete dut;
    return 0;
}
