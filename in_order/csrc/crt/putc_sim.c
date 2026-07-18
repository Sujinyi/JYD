#include "runtime.h"

extern volatile uint32_t putchar_mmio;

void rt_putc(char c) { putchar_mmio = (uint32_t)(uint8_t)c; }
