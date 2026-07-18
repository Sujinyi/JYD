#include "runtime.h"

#define N 128
static uint32_t arr[N];

static uint32_t xorshift(uint32_t *s) {
    uint32_t x = *s;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return *s = x;
}

static void qsort_u32(uint32_t *a, int lo, int hi) {
    if (lo >= hi) return;
    uint32_t p = a[(lo + hi) / 2];
    int i = lo, j = hi;
    while (i <= j) {
        while (a[i] < p) i++;
        while (a[j] > p) j--;
        if (i <= j) {
            uint32_t t = a[i]; a[i] = a[j]; a[j] = t;
            i++; j--;
        }
    }
    qsort_u32(a, lo, j);
    qsort_u32(a, i, hi);
}

int main(void) {
    uint32_t seed = 0xDEADBEEF;
    uint32_t sum_before = 0, sum_after = 0;
    for (int i = 0; i < N; i++) {
        arr[i] = xorshift(&seed);
        sum_before += arr[i];
    }
    qsort_u32(arr, 0, N - 1);
    for (int i = 1; i < N; i++)
        CHECK(arr[i - 1] <= arr[i]);
    for (int i = 0; i < N; i++)
        sum_after += arr[i];
    CHECK(sum_before == sum_after);
    rt_puts("sorted 128 elems, checksum ");
    rt_puthex(sum_after);
    rt_putc('\n');
    return 0;
}
