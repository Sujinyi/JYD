#include "runtime.h"
// backward-taken loop: BTFN best case
int main(void) {
    volatile int s = 0;
    for (int i = 0; i < 20000; i++) s += i;
    return !(s == 199990000);
}
