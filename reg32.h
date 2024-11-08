#pragma once

#include "macro.h"

#define ENABLE 1
#define DISABLE 0

#define BIT(bit) (1UL << (bit))

#define _MASK(x, n) (((1UL << (n)) - 1) << (x))
#define MASK(x, n...) _MASK(x, DEFAULT(1, n))
#define MASK_ALL (-1UL)

#define BIT_FIELD(val, x, n) ((val) & MASK(x, n) >> (x))

#define REG(reg) (*(volatile uint32_t *)(reg))

#define SET(reg, mask)                                                                             \
    do                                                                                             \
    {                                                                                              \
        (reg) |= (mask);                                                                           \
    } while (0)

#define CLEAR(reg, mask)                                                                           \
    do                                                                                             \
    {                                                                                              \
        (reg) &= ~(mask);                                                                          \
    } while (0)

#define TOGGLE(reg, mask)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (reg) ^= (mask);                                                                           \
    } while (0)

#define _TRIGGER(reg, en)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (reg) = (en);                                                                              \
        (reg) = !(en);                                                                             \
    } while (0)
#define TRIGGER(reg, en...) _TRIGGER(reg, DEFAULT(ENABLE, en))
#pragma once

#include "macro.h"

#define ENABLE 1
#define DISABLE 0

#define BIT(bit) (1UL << (bit))

#define _MASK(x, n) (((1UL << (n)) - 1) << (x))
#define MASK(x, n...) _MASK(x, DEFAULT(1, n))
#define MASK_ALL (-1UL)

#define BIT_FIELD(val, x, n) ((val) & MASK(x, n) >> (x))

#define REG(reg) (*(volatile uint32_t *)(reg))

#define SET(reg, mask)                                                                             \
    do                                                                                             \
    {                                                                                              \
        (reg) |= (mask);                                                                           \
    } while (0)

#define CLEAR(reg, mask)                                                                           \
    do                                                                                             \
    {                                                                                              \
        (reg) &= ~(mask);                                                                          \
    } while (0)

#define TOGGLE(reg, mask)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (reg) ^= (mask);                                                                           \
    } while (0)

#define _TRIGGER(reg, en)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (reg) = (en);                                                                              \
        (reg) = !(en);                                                                             \
    } while (0)
#define TRIGGER(reg, en...) _TRIGGER(reg, DEFAULT(ENABLE, en))
