#pragma once

#include <limits.h>
#include <stdint.h>

#include "args.h"

#define BITS CHAR_BIT // 1 Byte = 8 Bits

#define B 1            // 1 B
#define KB (1024 * B)  // 1 KB = 1024 B
#define MB (1024 * KB) // 1 MB = 1024 KB
#define GB (1024 * MB) // 1 GB = 1024 MB

#define WORD 4           // 1 Word = 4 Bytes (for 32-bit machine)
#define DWORD (2 * WORD) // 1 DWord = 8 Bytes
#define QWORD (4 * WORD) // 1 QWord = 16 Bytes

#define PAGE 16  // 1 Page = 16 Bytes
#define BLOCK 16 // 1 Block = 16 Bytes (for AES-128)

#define ENABLE 1
#define DISABLE 0

#define BIT(bit) (1UL << (bit))
#define MASK(x, n) (((1UL << (n)) - 1) << (x))
#define MASK_ALL (-1UL) // 0xFFFFFFFF

#define BIT_MASK(x, n...) MASK(x, DEFAULT(1, n))
#define BYTE_MASK(x, n...) MASK((x) * 8, DEFAULT(1, n) * 8)

#define BIT_FIELD(val, x, n) (((val) & MASK(x, n)) >> (x))
#define BYTE_FIELD(val, x) ((uint8_t)BIT_FIELD(val, (x) * 8, 8))

// Find the first set bit (31-0), if 0 return -1
#define BIT_FFS(mask) (__builtin_ffs(mask) - 1)
// Find the last set bit (31-0)
#define BIT_FLS(mask) (31 - __builtin_clz(mask))
// Count set bits
#define BIT_COUNT(mask) __builtin__popcount(mask)
// Mask of the first set bit
#define BIT_MASK_OF_FIRST_SET(mask) ((mask) & -(mask))
// set bits is continuous
#define BIT_IS_CONTINUOUS(mask) ((BIT_FLS(mask) - BIT_FFS(mask) + 1) == BIT_CNT(mask))

#define REG(reg) (*(volatile uint32_t *)(reg))

#define GET(reg, mask) ((reg) & (mask))

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

static inline uint32_t EndianChange(uint32_t value)
{
    return ((value & 0xFF000000) >> 24) | ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) | ((value & 0x000000FF) << 24);
}
