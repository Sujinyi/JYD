#include "runtime.h"
#include "board.h"

static int fib(int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }

int main(void) {
    rt_puts("\nHello from RV32I 5-stage core on XC7A100T!\n");
    rt_puts("fib(20) = ");
    rt_putdec(fib(20));
    rt_putc('\n');
    uint32_t n = 0;
    for (;;) {
        LED_REG = n & 0xF;
        rt_puts("heartbeat ");
        rt_putdec((int32_t)n++);
        rt_putc('\n');
        delay(6000000u);
    }
}
