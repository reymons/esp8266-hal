#ifndef ADDR_H_
#define ADDR_H_

#include <stdint.h>

#define ADDR(x) *((volatile uint32_t *) (x))

#define BIT(x) (1<<(x))

#endif // ADDR_H_

