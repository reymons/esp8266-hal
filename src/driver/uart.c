#include "uart.h"

void uart_enable(uart_num_t n, uart_baud_t baud, uart_config_t *config)
{
    config->reserved = 0;
    UART_CONF0(n) |= config->value;

    if (baud == UART_BAUD_AUTO) {
        UART_AUTOBAUD(n) |= BIT(0);
    } else {
        UART_CLOCK_DIV(n) = baud;
    }
}

char uart_getc(uart_num_t n)
{
    while (BITSVAL(UART_STATUS(n), UART_STATUS_RXFIFO_CNT_M, UART_STATUS_RXFIFO_CNT_S) < 1);
    return UART_FIFO(n);
}

void uart_putc(uart_num_t n, char c)
{
    while (BITSVAL(UART_STATUS(n), UART_STATUS_TXFIFO_CNT_M, UART_STATUS_TXFIFO_CNT_S) == UART_MAX_LEN);
    UART_FIFO(n) = c;
}

int uart_read(uart_num_t n, void *dst, int len)
{   
    int i = 0;
    
    for (int i = 0; i < len; i++) {
        ((char *)dst)[i] = uart_getc(n);
    }
    
    return i;
}

int uart_write(uart_num_t n, const void *src, int len)
{
    int i;

    for (i = 0; i < len; i++) {
        uart_putc(n, ((char *)src)[i]);
    }

    return i;
}

