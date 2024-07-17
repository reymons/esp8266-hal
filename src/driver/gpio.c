#include "gpio.h"

void gpio_enable(uint8_t gpio_num)
{
    GPIO_ENABLE_OUT_SET |= BIT(gpio_num);
}

void gpio_disable(uint8_t gpio_num)
{
    GPIO_ENABLE_OUT_CLEAR |= BIT(gpio_num);
}

void gpio_set(uint8_t gpio_num, uint8_t level)
{
    if (level) {
        GPIO_OUT_SET |= BIT(gpio_num);
    } else {
        GPIO_OUT_CLEAR |= BIT(gpio_num);
    }
}

