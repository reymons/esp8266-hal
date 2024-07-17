#ifndef GPIO_H_
#define GPIO_H_

#include "common/addr.h"

#define GPIO_BASE 0x60000300

#define GPIO_ADDR(x) ADDR(GPIO_BASE + (x))

#define GPIO_OUT_SET             GPIO_ADDR(0x04)
#define GPIO_OUT_CLEAR           GPIO_ADDR(0x08)
#define GPIO_ENABLE_OUT_SET      GPIO_ADDR(0x10)
#define GPIO_ENABLE_OUT_CLEAR    GPIO_ADDR(0x14)

void gpio_enable(uint8_t gpio_num);

void gpio_disable(uint8_t gpio_num);

void gpio_set(uint8_t gpio_num, uint8_t level);

#endif // GPIO_H_

