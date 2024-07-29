#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/iomux.h"

#define UNUM 0

void gpio_isr_handler()
{
    // !!!IMPORTANT!!! Otherwise infinite interrupts!!! >:(
    GPIO_STATUS_CLEAR = GPIO_STATUS;
    // Some code
}

void app()
{
    IOMUX_GPIO5 |= IOMUX_PIN_PULLUP;

    gpio_out(4, true);
    gpio_out(5, false);
    gpio_isr_add(5, GPIO_INT_TYPE_POSEDGE);
    
    uart_config_t config = {
        .stop_bit = UART_STOP_BIT_1,
        .data_bits = UART_DATA_BITS_8,
        .parity = UART_PARITY_EVEN,
        .parity_en = true,
    };

    uart_enable(UNUM, UART_BAUD_115200, &config);
    
    while (true) {
        switch (uart_getc(UNUM)) {
        case '+':
            gpio_out_write(4, 1);
            break;
        case '-':
            gpio_out_write(4, 0);
            break;
        }
    }
}

