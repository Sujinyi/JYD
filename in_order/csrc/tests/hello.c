#include "runtime.h"

int main(void) {
    rt_puts("Hello, RV32I 5-stage pipeline!\n");
    rt_puts("pc starts at ");
    rt_puthex(0x80000000u);
    rt_putc('\n');
    return 0;
}
