#pragma once

#include <limits.h>
#include <stdint.h>

#include "args.h"

// #define BITS CHAR_BIT // 1 Byte = 8 Bits
#define BITS 8UL // 1 Byte = 8 Bits

#define KB 1024UL      // 1 KB = 1024 Bytes
#define MB (1024 * KB) // 1 MB = 1024 KB
#define GB (1024 * MB) // 1 GB = 1024 MB

#define WORD 4UL         // 1 Word = 4 Bytes (for 32-bit machine)
#define DWORD (2 * WORD) // 1 DWord = 8 Bytes
#define QWORD (4 * WORD) // 1 QWord = 16 Bytes

#define PAGE 16UL  // 1 Page = 16 Bytes
#define BLOCK 16UL // 1 Block = 16 Bytes (for AES-128)

// Use compiler optimize option
#define DIV(x, y) {(x) / (y) * (y), (x) % (y)}
#define DIV_FLOOR(n, d) ((n) / (d))
#define DIV_ROUND(n, d) (((n) + (d) - 1) / (d))
#define ROUND_UP(x, y) (DIV_ROUND(x, y) * (y))

#define ENABLE 1
#define DISABLE 0

#define BIT(bit) (1UL << (bit))
#define MASK(x, n) (((1UL << (n)) - 1) << (x))
#define BYTE(x, n...) MASK((x) * 8, DEFAULT(1, n) * 8)
#define ALL_MASK (-1UL) // 0xFFFFFFFF

#define BIT_FIELD(val, x, n...) (((val) & MASK(x, DEFAULT(1, n))) >> (x))
#define BYTE_FIELD(val, x, n...) BIT_FIELD(val, (x) * 8, (DEFAULT(1, n) * 8))

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

#define ASSIGN(reg, x, n, val)                                                                     \
    do                                                                                             \
    {                                                                                              \
        (reg) = ((reg) & ~MASK(x, n)) | (((val) << (x)) & MASK(x, n));                             \
    } while (0)

#define _TRIGGER(reg, en)                                                                          \
    do                                                                                             \
    {                                                                                              \
        (reg) = (en);                                                                              \
        (reg) = 0;                                                                                 \
    } while (0)
#define TRIGGER(reg, en...) _TRIGGER(reg, DEFAULT(ENABLE, en))

#define _CLEAR_TRIGGER(reg, en)                                                                    \
    do                                                                                             \
    {                                                                                              \
        (reg) = 0;                                                                                 \
        (reg) = (en);                                                                              \
    } while (0)
#define CLEAR_TRIGGER(reg, en...) _CLEAR_TRIGGER(reg, DEFAULT(ENABLE, en))
