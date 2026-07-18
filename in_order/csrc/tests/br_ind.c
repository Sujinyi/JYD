#include "runtime.h"
// indirect jumps via switch table: BTB/jalr stress
int main(void) {
    volatile int s = 0;
    for (int i = 0; i < 20000; i++) {
        switch (i & 7) {
        case 0: s += 1; break;
        case 1: s += 3; break;
        case 2: s -= 2; break;
        case 3: s ^= 5; break;
        case 4: s += 7; break;
        case 5: s -= 1; break;
        case 6: s ^= 9; break;
        default: s += 2; break;
        }
    }
    return 0;
}
