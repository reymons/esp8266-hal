#ifndef IOMUX_H_
#define IOMUX_H_

#define IOMUX_BASE 0x60000800

#define IOMUX_CONF ADDR(IOMUX_BASE + 0x00)
#define IOMUX_MAPPED_ADDR(i) ADDR(IOMUX_BASE + 0x04 + 0x04 * i)

#define IOMUX_PIN_OUTPUT_ENABLE        BIT(0)
#define IOMUX_PIN_OUTPUT_ENABLE_SLEEP  BIT(1)
#define IOMUX_PIN_PULLDOWN_SLEEP       BIT(2)
#define IOMUX_PIN_PULLUP_SLEEP         BIT(3)
#define IOMUX_PIN_FUNC_LOW_M           0x00000003
#define IOMUX_PIN_FUNC_LOW_S           4
#define IOMUX_PIN_PULLDOWN             BIT(6)
#define IOMUX_PIN_PULLUP               BIT(7)
#define IOMUX_PIN_FUNC_HIGH_M          0x00000004
#define IOMUX_PIN_FUNC_HIGH_S          6

#define IOMUX_GPIO0   IOMUX_MAPPED_ADDR(12)
#define IOMUX_GPIO1   IOMUX_MAPPED_ADDR(5)
#define IOMUX_GPIO2   IOMUX_MAPPED_ADDR(13)
#define IOMUX_GPIO3   IOMUX_MAPPED_ADDR(4)
#define IOMUX_GPIO4   IOMUX_MAPPED_ADDR(14)
#define IOMUX_GPIO5   IOMUX_MAPPED_ADDR(15)
#define IOMUX_GPIO6   IOMUX_MAPPED_ADDR(6)
#define IOMUX_GPIO7   IOMUX_MAPPED_ADDR(7)
#define IOMUX_GPIO8   IOMUX_MAPPED_ADDR(8)
#define IOMUX_GPIO9   IOMUX_MAPPED_ADDR(9)
#define IOMUX_GPIO10  IOMUX_MAPPED_ADDR(10)
#define IOMUX_GPIO11  IOMUX_MAPPED_ADDR(11)
#define IOMUX_GPIO12  IOMUX_MAPPED_ADDR(0)
#define IOMUX_GPIO13  IOMUX_MAPPED_ADDR(1)
#define IOMUX_GPIO14  IOMUX_MAPPED_ADDR(2)
#define IOMUX_GPIO15  IOMUX_MAPPED_ADDR(3)

#define IOMUX_GPIO1_FUNC_UART0_TXD         IOMUX_FUNC(0)

#define IOMUX_GPIO3_FUNC_UART0_RXD         IOMUX_FUNC(0)

typedef union {
    uint32_t value;

    struct {
        uint32_t func1            : 2;
        uint32_t pullup           : 1;
        uint32_t pulldown         : 1;
        uint32_t func0            : 2;
        uint32_t pullup_sleep     : 1;
        uint32_t pulldown_sleep   : 1;
        uint32_t output_en_sleep  : 1;
        uint32_t output_en        : 1;
    };
} iomux_pin_t;

void iomux_set_func();

#endif // IOMUX_H_
