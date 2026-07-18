#include "runtime.h"
// deep call/return chains: RAS stress
static int rec(int n) {
    if (n <= 1) return 1;
    return rec(n - 1) + (n & 3);
}
int main(void) {
    volatile int s = 0;
    for (int i = 0; i < 100; i++) s += rec(200);
    return 0;
}
