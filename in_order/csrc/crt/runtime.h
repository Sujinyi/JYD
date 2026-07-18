#pragma once
#include <stdint.h>

void rt_putc(char c);
void rt_puts(const char *s);
void rt_puthex(uint32_t v);
void rt_putdec(int32_t v);

#define CHECK(cond) do { \
    if (!(cond)) { rt_puts("CHECK FAIL: " #cond "\n"); return __LINE__; } \
} while (0)
