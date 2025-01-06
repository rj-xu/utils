#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "attribute.h"

static inline bool IsLittleEndian()
{
    union {
        char c;
        int i;
    } x = {.i = 1};
    return x.c == 1;
}

static inline uint32_t SwapEndian(uint32_t value)
{
    return ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) | ((value & 0x000000FF) << 24);
    // return __builtin_bswap32(value);
}
