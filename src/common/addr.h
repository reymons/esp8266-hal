#ifndef ADDR_H_
#define ADDR_H_

#include <stdint.h>
#include <stddef.h>

#define APB_FREQ 52000000

#define ADDR(x) *((volatile uint32_t *) (x))
#define BIT(x) (1 << (x))

#define SET_BITS(bits, val, mask, shift) \
    ( (bits) = ( (bits) & ~( (mask) << (shift) )) | ( (val) << (shift) ))

#define BITSVAL(bits, mask, shift) ( (bits) >> (shift) & (mask) )

#endif // ADDR_H_

