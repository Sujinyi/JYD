#include "runtime.h"
#include "board.h"

#define STEP 2000000u

int main(void) {
    rt_puts("RV32I on Artix-7: LED marquee\n");
    uint32_t pat = 1;
    for (;;) {
        LED_REG = pat;
        delay(STEP);
        pat = (pat == 8) ? 1 : (pat << 1);
    }
}
