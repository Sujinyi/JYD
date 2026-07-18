// Verilator testbench: difftest DUT vs golden ISS + tohost monitor
#include "Vtop.h"
#include "Vtop___024root.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "golden.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <deque>

static constexpr size_t MEM_WORDS = 1 << 14;
static constexpr uint32_t BASE = 0x80000000u;

struct CommitRec {
    uint32_t pc, instr, wdata;
    uint8_t rd;
    bool wen;
};

// CPI attribution: classify every lost issue slot (2 slots/cycle)
struct Perf {
    uint64_t cycles = 0, dual_cyc = 0, single_cyc = 0;
    uint64_t lost_mstall = 0, lost_loaduse = 0, lost_fetch = 0;
    uint64_t lost_br = 0, lost_jalr = 0, lost_fencei = 0, lost_cold = 0;
    uint64_t s1_nov1 = 0, s1_ctrl = 0, s1_struct = 0, s1_dep = 0, s1_hz = 0;
    uint64_t ev_mispred = 0, ev_jalr = 0, ev_fencei = 0, ev_cold = 0;
    int pending = 0; // flush-recovery cause: 1 br, 2 jalr, 3 fencei, 4 cold-jal/btfn

    void tick(uint16_t p) {
        bool issue0 = p & 1,   issue1 = p & 2,    v0 = p & 4,     v1 = p & 8;
        bool hz0 = p & 16,     hz1 = p & 32,      ms = p & 64,    rfl = p & 128;
        bool exmis = p & 256,  exjr = p & 512,    exfen = p & 1024, idred = p & 2048;
        bool i1simple = p & 4096, i0ctrl = p & 8192, dep01 = p & 16384;

        cycles++;
        if (issue1) dual_cyc++;
        else if (issue0) single_cyc++;
        if (issue0) pending = 0; // pipeline resumed: clear stale recovery tag
        if (exmis) { ev_mispred++; pending = 1; }
        else if (exjr) { ev_jalr++; pending = 2; }
        else if (exfen) { ev_fencei++; pending = 3; }
        if (idred) { ev_cold++; if (!pending) pending = 4; }

        int lost = 2 - (int)issue0 - (int)issue1;
        if (lost == 0) return;

        if (ms) lost_mstall += lost;
        else if (exmis || exjr || exfen || rfl || (!v0 && pending)) {
            int c = exmis ? 1 : exjr ? 2 : exfen ? 3 : pending;
            if (c == 1) lost_br += lost;
            else if (c == 2) lost_jalr += lost;
            else if (c == 3) lost_fencei += lost;
            else if (c == 4) lost_cold += lost;
            else lost_fetch += lost;
        }
        else if (!v0) lost_fetch += lost;
        else if (hz0) lost_loaduse += lost;
        else { // issue0 only: one slot lost, why did slot1 not go?
            if (!v1) s1_nov1 += lost;
            else if (i0ctrl) s1_ctrl += lost;
            else if (!i1simple) s1_struct += lost;
            else if (dep01) s1_dep += lost;
            else if (hz1) s1_hz += lost;
            else lost_fetch += lost;
        }
    }

    void report(uint64_t instrs) const {
        if (!instrs) return;
        double di = 2.0 * (double)instrs;
        auto cpi = [&](uint64_t slots) { return (double)slots / di; };
        double total = (double)cycles / (double)instrs;
        printf("---- CPI stack (%lu cycles, %lu instrs, CPI=%.3f) ----\n",
               (unsigned long)cycles, (unsigned long)instrs, total);
        printf("  base (ideal dual-issue)      0.500\n");
        printf("  branch mispredict            %.3f  (%lu ev, %.1f cyc/ev)\n",
               cpi(lost_br), (unsigned long)ev_mispred,
               ev_mispred ? (double)lost_br / 2.0 / (double)ev_mispred : 0.0);
        printf("  jalr (no prediction)         %.3f  (%lu ev, %.1f cyc/ev)\n",
               cpi(lost_jalr), (unsigned long)ev_jalr,
               ev_jalr ? (double)lost_jalr / 2.0 / (double)ev_jalr : 0.0);
        printf("  cold JAL/BTFN (1-bubble)     %.3f  (%lu ev)\n",
               cpi(lost_cold), (unsigned long)ev_cold);
        printf("  fence.i flush                %.3f  (%lu ev)\n",
               cpi(lost_fencei), (unsigned long)ev_fencei);
        printf("  load-use stall               %.3f\n", cpi(lost_loaduse));
        printf("  muldiv stall                 %.3f\n", cpi(lost_mstall));
        printf("  fetch supply (queue empty)   %.3f\n", cpi(lost_fetch));
        printf("  single-issue: q has 1 entry  %.3f\n", cpi(s1_nov1));
        printf("  single-issue: slot0 is ctrl  %.3f\n", cpi(s1_ctrl));
        printf("  single-issue: i1 not ALU     %.3f\n", cpi(s1_struct));
        printf("  single-issue: RAW/WAW dep    %.3f\n", cpi(s1_dep));
        printf("  single-issue: i1 load-use    %.3f\n", cpi(s1_hz));
        double acc = 0.5 + cpi(lost_br + lost_jalr + lost_fencei + lost_cold +
                               lost_loaduse + lost_mstall + lost_fetch +
                               s1_nov1 + s1_ctrl + s1_struct + s1_dep + s1_hz);
        printf("  sum=%.3f | dual %.1f%% / single %.1f%% / idle %.1f%% of cycles\n",
               acc, 100.0 * dual_cyc / cycles, 100.0 * single_cyc / cycles,
               100.0 * (cycles - dual_cyc - single_cyc) / cycles);
    }
};

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();

    std::string bin_path;
    uint32_t tohost_addr = 0;
    uint64_t max_cycles = 2000000;
    bool do_vcd = false;

    const char *p;
    if ((p = ctx->commandArgsPlusMatch("bin=")) && *p) bin_path = p + 5;
    if ((p = ctx->commandArgsPlusMatch("tohost=")) && *p) tohost_addr = strtoul(p + 8, nullptr, 16);
    if ((p = ctx->commandArgsPlusMatch("max=")) && *p) max_cycles = strtoull(p + 5, nullptr, 0);
    if ((p = ctx->commandArgsPlusMatch("vcd")) && *p) do_vcd = true;
    std::string clog_path;
    if ((p = ctx->commandArgsPlusMatch("commitlog=")) && *p) clog_path = p + 11;
    uint32_t putc_addr = 0;
    if ((p = ctx->commandArgsPlusMatch("putc=")) && *p) putc_addr = strtoul(p + 6, nullptr, 16);
    bool do_perf = false;
    if ((p = ctx->commandArgsPlusMatch("perf")) && *p) do_perf = true;

    if (bin_path.empty() || tohost_addr == 0) {
        fprintf(stderr, "usage: %s +bin=prog.bin +tohost=hexaddr [+max=N] [+vcd]\n", argv[0]);
        return 2;
    }

    Vtop *dut = new Vtop;
    Golden golden(MEM_WORDS);
    FILE *clog = nullptr;
    if (!clog_path.empty()) {
        clog = fopen(clog_path.c_str(), "w");
        if (!clog) { fprintf(stderr, "cannot open %s\n", clog_path.c_str()); return 2; }
    }

    // load binary into both memories
    FILE *f = fopen(bin_path.c_str(), "rb");
    if (!f) { fprintf(stderr, "cannot open %s\n", bin_path.c_str()); return 2; }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::vector<uint8_t> buf(sz);
    if (fread(buf.data(), 1, sz, f) != (size_t)sz) { fprintf(stderr, "read error\n"); return 2; }
    fclose(f);
    for (long i = 0; i < sz; i++) {
        uint32_t w = (uint32_t)(i >> 2);
        uint32_t sh = 8 * (i & 3);
        golden.mem[w] = (golden.mem[w] & ~(0xFFu << sh)) | ((uint32_t)buf[i] << sh);
    }
    for (size_t i = 0; i < MEM_WORDS; i++) {
        if (i & 1) dut->rootp->top__DOT__mem1[i >> 1] = golden.mem[i];
        else       dut->rootp->top__DOT__mem0[i >> 1] = golden.mem[i];
    }

    VerilatedVcdC *vcd = nullptr;
    if (do_vcd) {
        Verilated::traceEverOn(true);
        vcd = new VerilatedVcdC;
        dut->trace(vcd, 99);
        vcd->open("dump.vcd");
    }

    // reset
    uint64_t t = 0;
    dut->rst = 1;
    dut->clk = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 0; dut->eval(); if (vcd) vcd->dump(t++);
        dut->clk = 1; dut->eval(); if (vcd) vcd->dump(t++);
    }
    dut->rst = 0;

    std::deque<CommitRec> history;
    uint64_t commits = 0;
    int exit_code = 1;
    Perf perf;

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->clk = 0;
        dut->eval();
        if (vcd) vcd->dump(t++);
        if (do_perf) perf.tick(dut->rootp->top__DOT__u_core__DOT__perf_probe);

        // sample pre-edge state (dual commit: slot0 older)
        CommitRec recs[2] = {
            {dut->commit0_pc, dut->commit0_instr, dut->commit0_rd_wdata,
             dut->commit0_rd, (bool)dut->commit0_rd_wen},
            {dut->commit1_pc, dut->commit1_instr, dut->commit1_rd_wdata,
             dut->commit1_rd, (bool)dut->commit1_rd_wen}};
        bool cvs[2] = {(bool)dut->commit0_valid, (bool)dut->commit1_valid};
        bool tohost_hit = (dut->mon_wen != 0) &&
                          ((dut->mon_waddr & ~3u) == (tohost_addr & ~3u));
        uint32_t tohost_val = dut->mon_wdata;
        if (putc_addr && (dut->mon_wen != 0) &&
            ((dut->mon_waddr & ~3u) == (putc_addr & ~3u))) {
            putchar((int)(dut->mon_wdata & 0xFF));
            fflush(stdout);
        }

        dut->clk = 1;
        dut->eval();
        if (vcd) vcd->dump(t++);

        for (int s = 0; s < 2; s++) {
            if (!cvs[s]) continue;
            CommitRec &rec = recs[s];
            commits++;
            history.push_back(rec);
            if (history.size() > 16) history.pop_front();
            if (clog) {
                if (rec.wen && rec.rd != 0)
                    fprintf(clog, "%08x %08x x%d %08x\n", rec.pc, rec.instr, rec.rd, rec.wdata);
                else
                    fprintf(clog, "%08x %08x -\n", rec.pc, rec.instr);
            }

            // golden step + compare
            if (golden.pc != rec.pc) {
                printf("[DIFFTEST] PC mismatch at commit #%lu: dut=%08x golden=%08x\n",
                       (unsigned long)commits, rec.pc, golden.pc);
                goto mismatch;
            }
            golden.step();
        }
        if (cvs[0] || cvs[1]) {
            for (int r = 0; r < 32; r++) {
                uint32_t dv = dut->rootp->top__DOT__u_core__DOT__u_rf__DOT__lvt[r]
                                  ? dut->rootp->top__DOT__u_core__DOT__u_rf__DOT__rfb[r]
                                  : dut->rootp->top__DOT__u_core__DOT__u_rf__DOT__rfa[r];
                if (dv != golden.x[r]) {
                    printf("[DIFFTEST] x%d mismatch after cycle %lu: dut=%08x golden=%08x\n",
                           r, (unsigned long)cyc, dv, golden.x[r]);
                    goto mismatch;
                }
            }
        }

        if (tohost_hit) {
            if (tohost_val == 1) {
                printf("PASS (%lu commits, %lu cycles)\n",
                       (unsigned long)commits, (unsigned long)cyc);
                exit_code = 0;
                if (do_perf) perf.report(commits);
            } else {
                printf("FAIL tohost=%u (test #%u), %lu commits\n",
                       tohost_val, tohost_val >> 1, (unsigned long)commits);
                exit_code = 1;
            }
            goto done;
        }
    }
    printf("TIMEOUT after %lu cycles (%lu commits)\n",
           (unsigned long)max_cycles, (unsigned long)commits);
    goto done;

mismatch:
    printf("--- last commits (newest last) ---\n");
    for (auto &h : history)
        printf("  pc=%08x instr=%08x rd=%2u wen=%d wdata=%08x\n",
               h.pc, h.instr, h.rd, h.wen, h.wdata);
    printf("--- golden regs ---\n");
    for (int r = 0; r < 32; r++) {
        printf("x%-2d=%08x%s", r, golden.x[r], (r % 4 == 3) ? "\n" : "  ");
    }
    exit_code = 1;

done:
    if (clog) fclose(clog);
    if (vcd) vcd->close();
    dut->final();
    delete dut;
    return exit_code;
}
