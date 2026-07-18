#include "runtime.h"
#include "board.h"

void rt_putc(char c) {
    while (UART_REG & 1) ;
    UART_REG = (uint32_t)(uint8_t)c;
}
