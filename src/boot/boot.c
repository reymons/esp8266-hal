#include "common/addr.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define VEC __attribute__((weak, alias("_vec_default")))
#define BOOT __attribute__((section(".boot")))

extern void app();

extern char __sbss;
extern char __ebss;
extern char __etext;

extern void VEC gpio_isr_handler();
extern void VEC uart_isr_handler();

void _vec_default() {}

void _vec_user_excp()
{
    gpio_isr_handler();
    asm volatile ("wsr %0, intclear; esync" :: "a" ((uint32_t)BIT(4)));
}

void BOOT _boot()
{
    uint32_t ps;
    uint32_t ie;
    asm volatile ("rsr %0, ps" : "=a" (ps));
    asm volatile ("rsr %0, intenable" : "=a" (ie));
    SET_BITS(ps, 0, 0b1111, 0); // set intlevel to 0
    ps &= ~BIT(4);              // disable excm
    ie |= BIT(4) | BIT(5);      // enable GPIO and UART interrupts
    asm volatile ("wsr %0, ps" :: "a" (ps));
    asm volatile ("wsr %0, intenable" :: "a" (ie));

    for (char *i = &__sbss; i < &__ebss; i++) {
        *i = 0;
    }

    app();
}

