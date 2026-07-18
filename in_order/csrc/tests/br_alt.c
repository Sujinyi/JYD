#include "runtime.h"
// alternating taken/not-taken forward branches: static prediction worst case
int main(void) {
    volatile int s = 0;
    for (int i = 0; i < 20000; i++) {
        if (i & 1) s += i;
        else s -= i;
    }
    return !(s == 10000);
}
