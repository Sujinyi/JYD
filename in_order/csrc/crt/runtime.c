#include "runtime.h"

void rt_puts(const char *s) {
    while (*s) rt_putc(*s++);
}

void rt_puthex(uint32_t v) {
    rt_puts("0x");
    for (int i = 28; i >= 0; i -= 4) {
        uint32_t d = (v >> i) & 0xF;
        rt_putc((char)(d < 10 ? '0' + d : 'a' + d - 10));
    }
}

void rt_putdec(int32_t v) {
    char buf[12];
    int i = 0;
    uint32_t u = (uint32_t)v;
    if (v < 0) { rt_putc('-'); u = (uint32_t)(-v); }
    do { buf[i++] = (char)('0' + u % 10); u /= 10; } while (u);
    while (i) rt_putc(buf[--i]);
}

void *memset(void *dst, int c, unsigned long n) {
    char *d = (char *)dst;
    while (n--) *d++ = (char)c;
    return dst;
}

void *memcpy(void *dst, const void *src, unsigned long n) {
    char *d = (char *)dst;
    const char *s = (const char *)src;
    while (n--) *d++ = *s++;
    return dst;
}

// ---- soft mul/div (rv32i has no M extension) ----
uint32_t __mulsi3(uint32_t a, uint32_t b) {
    uint32_t r = 0;
    while (b) {
        if (b & 1) r += a;
        a <<= 1;
        b >>= 1;
    }
    return r;
}

uint32_t __udivsi3(uint32_t n, uint32_t d) {
    if (d == 0) return 0xFFFFFFFFu;
    uint32_t q = 0;
    for (int i = 31; i >= 0; i--) {
        if ((n >> i) >= d) {
            n -= d << i;
            q |= 1u << i;
        }
    }
    return q;
}

uint32_t __umodsi3(uint32_t n, uint32_t d) {
    return n - (uint32_t)(__mulsi3(__udivsi3(n, d), d));
}

int32_t __divsi3(int32_t n, int32_t d) {
    int neg = (n < 0) ^ (d < 0);
    uint32_t q = __udivsi3(n < 0 ? (uint32_t)-n : (uint32_t)n,
                           d < 0 ? (uint32_t)-d : (uint32_t)d);
    return neg ? -(int32_t)q : (int32_t)q;
}

int32_t __modsi3(int32_t n, int32_t d) {
    uint32_t r = __umodsi3(n < 0 ? (uint32_t)-n : (uint32_t)n,
                           d < 0 ? (uint32_t)-d : (uint32_t)d);
    return n < 0 ? -(int32_t)r : (int32_t)r;
}
