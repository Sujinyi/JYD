// TB for fpga_top: clock/reset, UART decoder, LED monitor
#include "Vfpga_top.h"
#include "verilated.h"
#include <cstdio>
#include <cstdint>
#include <cstdlib>

static constexpr int DIV = 200000000 / 115200; // core clock 200MHz

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    auto *ctx = Verilated::threadContextp();

    uint64_t max_cycles = 30000000;
    const char *p;
    if ((p = ctx->commandArgsPlusMatch("cycles=")) && *p)
        max_cycles = strtoull(p + 8, nullptr, 0);

    Vfpga_top *dut = new Vfpga_top;

    dut->sys_rst_n = 0;
    dut->sys_clk_p = 0;
    for (int i = 0; i < 10; i++) {
        dut->sys_clk_p ^= 1;
        dut->eval();
    }
    dut->sys_rst_n = 1;

    // UART RX decoder state
    int state = 0;       // 0 idle, 1 receiving
    int cnt = 0, bit = 0;
    uint8_t sh = 0;
    uint8_t led_prev = 0xFF;

    for (uint64_t cyc = 0; cyc < max_cycles; cyc++) {
        dut->sys_clk_p = 0; dut->eval();
        dut->sys_clk_p = 1; dut->eval();

        if (dut->led != led_prev) {
            led_prev = dut->led;
            printf("[LED] %c%c%c%c  (cycle %lu)\n",
                   (led_prev & 8) ? '*' : '.', (led_prev & 4) ? '*' : '.',
                   (led_prev & 2) ? '*' : '.', (led_prev & 1) ? '*' : '.',
                   (unsigned long)cyc);
            fflush(stdout);
        }

        if (state == 0) {
            if (dut->uart_txd == 0) { state = 1; cnt = DIV + DIV / 2; bit = 0; sh = 0; }
        } else {
            if (--cnt == 0) {
                if (bit < 8) {
                    sh |= (dut->uart_txd & 1) << bit;
                    bit++;
                    cnt = DIV;
                } else {
                    putchar(sh);
                    fflush(stdout);
                    state = 0;
                }
            }
        }
    }
    dut->final();
    delete dut;
    return 0;
}
