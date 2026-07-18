#include "runtime.h"

static int fib_rec(int n) {
    return n < 2 ? n : fib_rec(n - 1) + fib_rec(n - 2);
}

static int fib_iter(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        int t = a + b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    CHECK(fib_rec(15) == 610);
    CHECK(fib_iter(15) == 610);
    for (int i = 0; i < 20; i++)
        CHECK(fib_rec(i) == fib_iter(i));
    rt_puts("fib(15) = ");
    rt_putdec(fib_rec(15));
    rt_putc('\n');
    return 0;
}
