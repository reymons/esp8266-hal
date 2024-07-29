#include "gpio.h"

void gpio_out(uint8_t num, bool enabled)
{
    if (enabled) {
        GPIO_ENABLE_OUT_SET |= BIT(num) & GPIO_OUT_M;
    } else {
        GPIO_ENABLE_OUT_CLEAR |= BIT(num) & GPIO_OUT_M;
    }
}

void gpio_out_write(uint8_t num, bool set)
{
    if (set) {
        GPIO_OUT_SET = BIT(num) & GPIO_OUT_M;
    } else {
        GPIO_OUT_CLEAR = BIT(num) & GPIO_OUT_M;
    }
}

bool gpio_in_read(uint8_t num)
{
    return GPIO_INPUT & BIT(num);
}

void gpio_isr_add(uint8_t num, gpio_int_type_t int_type)
{
    SET_BITS(GPIO_PIN(num), int_type, 0b111, 7);
}

