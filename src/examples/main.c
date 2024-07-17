#include "driver/gpio.h"

void app()
{
    gpio_enable(5);

    int i = 0;

    while (i++ < 3) {
        gpio_set(5, 1);
        for (int i = 0; i < 800000; i++);
        gpio_set(5, 0);
        for (int i = 0; i < 800000; i++);
    }

    gpio_set(5, 1);
    gpio_disable(5);

    while (1);
}

