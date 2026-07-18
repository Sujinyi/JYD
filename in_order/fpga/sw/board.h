#pragma once
#include <stdint.h>

#define UART_REG    (*(volatile uint32_t *)0x40000000u)
#define LED_REG     (*(volatile uint32_t *)0x40000008u)
#define CYCLE_REG   (*(volatile uint32_t *)0x40000010u)
#define INSTRET_REG (*(volatile uint32_t *)0x40000014u)

static inline void delay(uint32_t n) {
    for (volatile uint32_t i = 0; i < n; i++) ;
}
