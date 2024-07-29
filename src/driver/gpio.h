#ifndef GPIO_H_
#define GPIO_H_

#include "common/addr.h"
#include <stdbool.h>

#define GPIO_BASE       0x60000300
#define GPIO_PIN_BASE   0x28

#define GPIO_ADDR(x)        ADDR(GPIO_BASE + (x))
#define GPIO_PIN(x)         ADDR(GPIO_BASE + GPIO_PIN_BASE + (x) * 4)

#define GPIO_OUT                 GPIO_ADDR(0x00)
#define GPIO_OUT_SET             GPIO_ADDR(0x04)
#define GPIO_OUT_CLEAR           GPIO_ADDR(0x08)
#define GPIO_ENABLE_OUT_SET      GPIO_ADDR(0x10)
#define GPIO_ENABLE_OUT_CLEAR    GPIO_ADDR(0x14)
#define GPIO_INPUT               GPIO_ADDR(0x18)
#define GPIO_STATUS              GPIO_ADDR(0x1c)
#define GPIO_STATUS_CLEAR        GPIO_ADDR(0x24)

#define GPIO_OUT_M      0x0000ffff

typedef void (*gpio_isr_t)(void);

typedef enum {
    GPIO_INT_TYPE_DISABLE   = 0,
    GPIO_INT_TYPE_POSEDGE   = 1,
    GPIO_INT_TYPE_NEGEDGE   = 2,
    GPIO_INT_TYPE_BOTHEDGE  = 3,
    GPIO_INT_TYPE_LOWLEVEL  = 4,
    GPIO_INT_TYPE_HIGHLEVEL = 5,
} gpio_int_type_t;

typedef struct {
    uint32_t source:        1;
    uint32_t reserved1:     1;
    uint32_t driver:        1;
    uint32_t reserved2:     4;
    uint32_t int_type:      3;
    uint32_t wakeup_enable: 1;
    uint32_t reserved3:     21;
} gpio_pin_t;

void gpio_out(uint8_t num, bool enabled);

void gpio_out_write(uint8_t num, bool set);

bool gpio_in_read(uint8_t num);

void gpio_isr_add(uint8_t num, gpio_int_type_t int_type);

#endif // GPIO_H_

