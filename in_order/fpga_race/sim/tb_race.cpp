// Verilator testbench for the competition platform (student_top level).
// Drives w_cpu_clk (200MHz) and w_clk_50Mhz (50MHz, 1:4 ratio) so the
// ms counter advances exactly as on the board: simulated ms == board ms.
// Prints SEG/LED writes as they happen and decodes the final scoreboard.
#include "Vstudent_top.h"
#include "Vstudent_top___024root.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();

    uint64_t max_cycles = 3000000000ULL;
    const char *p;
    if ((p = ctx->commandArgsPlusMatch("max=")) && *p)
        max_cycles = strtoull(p + 5, nullptr, 0);

    Vstudent_top *dut = new Vstudent_top;
    dut->virtual_sw = 0;
    dut->virtual_key = 0;

    // reset: hold for 8 cpu cycles
    dut->w_clk_rst = 1;
    dut->w_cpu_clk = 0;
    dut->w_clk_50Mhz = 0;
    for (int i = 0; i < 16; i++) {
        dut->w_cpu_clk = !dut->w_cpu_clk;
        if (i % 4 == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();
    }
    dut->w_clk_rst = 0;

    uint32_t last_seg = 0, last_led = 0;
    uint64_t halt_streak = 0;
    bool seg_written = false, led_written = false;

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        // 200MHz cpu clock: one full cycle per iteration
        dut->w_cpu_clk = 0;
        dut->eval();
        dut->w_cpu_clk = 1;
        // 50MHz clock: one edge every 2 cpu cycles (period = 4 cpu cycles)
        if ((cyc & 1) == 0) dut->w_clk_50Mhz = !dut->w_clk_50Mhz;
        dut->eval();

        uint32_t seg = dut->rootp->student_top__DOT__bridge_inst__DOT__seg_wdata_cpu;
        uint32_t led = dut->rootp->student_top__DOT__bridge_inst__DOT__LED_cpu;
        if (seg != last_seg) {
            printf("[%12lu cyc] SEG <= %08x\n", (unsigned long)cyc, seg);
            last_seg = seg;
            seg_written = true;
        }
        if (led != last_led) {
            printf("[%12lu cyc] LED <= %08x\n", (unsigned long)cyc, led);
            last_led = led;
            led_written = true;
        }

        // halt detection: fetch parked on the loop_halt spin (0x80000014)
        uint32_t iaddr = dut->rootp->student_top__DOT__u_core__DOT__pc_f;
        if (iaddr >= 0x80000010 && iaddr <= 0x80000018) halt_streak++;
        else halt_streak = 0;
        if (halt_streak > 20000) {
            printf("HALT at cycle %lu (loop_halt reached)\n", (unsigned long)cyc);
            break;
        }
    }

    // final scoreboard decode (SEG BCD: [31:24] rv32i, [23:20] m, [19:0] ms)
    printf("\n==== competition scoreboard ====\n");
    printf("SEG = %08x  -> RV32I %x%x/37, M %x/8, time %x%x%x%x%x ms\n",
           last_seg,
           (last_seg >> 28) & 0xF, (last_seg >> 24) & 0xF,
           (last_seg >> 20) & 0xF,
           (last_seg >> 16) & 0xF, (last_seg >> 12) & 0xF,
           (last_seg >> 8) & 0xF, (last_seg >> 4) & 0xF, last_seg & 0xF);
    printf("LED = %08x  (expect 078b7323 all-pass)\n", last_led);
    bool pass = led_written && seg_written && (last_led == 0x078b7323u);
    printf("%s\n", pass ? "RESULT: ALL PASS" : "RESULT: INCOMPLETE/FAIL");

    dut->final();
    delete dut;
    return pass ? 0 : 1;
}
