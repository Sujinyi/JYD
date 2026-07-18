#include "runtime.h"

volatile int32_t va = 12345, vb = -67;
volatile uint32_t ua = 0xFEDCBA98u, ub = 1000;

int main(void) {
    CHECK(va * vb == -827115);
    CHECK(va / vb == -184);
    CHECK(va % vb == 17);
    CHECK(ua / ub == 4275878u);
    CHECK(ua % ub == 552u);
    CHECK(ua * ua == 0xDD413A40u);
    CHECK(ua * ub == 0x8E38E1C0u);
    rt_puts("muldiv ok: 12345*-67 = ");
    rt_putdec(va * vb);
    rt_putc('\n');
    return 0;
}
