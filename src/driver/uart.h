#ifndef UART_H_
#define UART_H_

#include "common/addr.h"

#define UART_BASE 0x60000000

#define UART0_BASE UART_BASE
#define UART1_BASE (UART_BASE + 0xf00)

#define UART_ADDR(i, addr) ADDR(UART_BASE + (addr) + 0xf00 * (i))

#define UART_MAX_LEN 128

#define UART_FIFO(i)          UART_ADDR((i), 0x00)
#define UART_INT_RAW(i)       UART_ADDR((i), 0x04)
#define UART_INT_STATUS(i)    UART_ADDR((i), 0x08)
#define UART_INT_ENABLE(i)    UART_ADDR((i), 0x0c)
#define UART_INT_CLEAR(i)     UART_ADDR((i), 0x10)
#define UART_CLOCK_DIV(i)     UART_ADDR((i), 0x14)
#define UART_AUTOBAUD(i)      UART_ADDR((i), 0x18)
#define UART_STATUS(i)        UART_ADDR((i), 0x1c)
#define UART_CONF0(i)         UART_ADDR((i), 0x20)
#define UART_CONF1(i)         UART_ADDR((i), 0x24)
#define UART_LOW_PULSE(i)     UART_ADDR((i), 0x28)
#define UART_HIGH_PULSE(i)    UART_ADDR((i), 0x2c)
#define UART_RXD_CNT(i)       UART_ADDR((i), 0x30)
#define UART_DATE(i)          UART_ADDR((i), 0x78)
#define UART_ID(i)            UART_ADDR((i), 0x7c)

#define UART_CONF0_RST_TX            BIT(18)
#define UART_CONF0_RST_RX            BIT(17)

#define UART_STATUS_TXFIFO_CNT_S     16
#define UART_STATUS_TXFIFO_CNT_M     0xff
#define UART_STATUS_RXFIFO_CNT_S     0
#define UART_STATUS_RXFIFO_CNT_M     0xff

typedef int uart_num_t;

typedef enum {
    UART_PARITY_EVEN = 0,
    UART_PARITY_ODD  = 1,
} uart_parity_t;

typedef enum {
    UART_DATA_BITS_5 = 0,
    UART_DATA_BITS_6 = 1,
    UART_DATA_BITS_7 = 2,
    UART_DATA_BITS_8 = 3,
} uart_data_bits_t;

typedef enum {
    UART_STOP_BIT_1   = 1,
    UART_STOP_BIT_1_5 = 2,
    UART_STOP_BIT_2   = 3,
} uart_stop_bit_t;

typedef enum {
    UART_BAUD_9600   = (APB_FREQ / 9600),   // 5417
    UART_BAUD_115200 = (APB_FREQ / 115200), // 451
    UART_BAUD_AUTO   = 0
} uart_baud_t;

typedef union {
    uint8_t value;

    struct {
        uint8_t reserved : 2;
        uart_stop_bit_t stop_bit : 2;
        uart_data_bits_t data_bits : 2;
        bool parity_en : 1;
        uart_parity_t parity : 1;
    };
} uart_config_t;

void uart_enable(uart_num_t n, uart_baud_t baud, uart_config_t *config);

char uart_getc(uart_num_t n);

void uart_putc(uart_num_t n, char c);

int uart_read(uart_num_t n, void *dst, int len);

int uart_write(uart_num_t n, const void *src, int len);

#endif // UART_H_
