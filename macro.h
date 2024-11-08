#pragma once

#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>

#include "log.h"

// Type
typedef unsigned int uint;
#define let __auto_type const
#define let_mut __auto_type
#define any_t void *

typedef const char *str_t;

typedef struct
{
    uint8_t *data;
    int bytes;
} ptr_t;
#define PTR(data, bytes) ((ptr_t){.data = (uint8_t *)(data), .bytes = (bytes)})

#define ARR_TYPEDEF(Type_t)                                                                        \
    typedef struct                                                                                 \
    {                                                                                              \
        int len;                                                                                   \
        Type_t data[0];                                                                            \
    } Arr##Type_t

#define ARR_MALLOC(Type_t, len)                                                                    \
    ((Arr##Type_t *)malloc(sizeof(Type_t) * (len) + sizeof(Arr##Type_t)))

// Basic Unit
#define BITS_PER_BYTE __CHAR_BIT__

#define B 1
#define KB 1024
#define MB (1024 * 1024)
#define GB (1024 * 1024 * 1024)

// Attributes
#define __DEPRECATED __attribute__((deprecated))

#define __RO const
#define __WO
#define __RW

// Struct
#define OFFSETOF(type, member) __builtin_offsetof(type, member) // May use offsetof() directly

// Debug
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int : -!!(e); }))
#define _IS_SAME_TYPE(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define _MUST_SAME_TYPE(a, b) BUILD_BUG_ON_ZERO(_IS_SAME_TYPE(a, b))

// Math
#define MAX(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (void)&_a == &_b;                                                                          \
        _a > _b ? _a : _b;                                                                         \
    })

#define MIN(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (void)&_a == &_b;                                                                          \
        _a < _b ? _a : _b;                                                                         \
    })

// Array
#define _IS_ARRAY(arr) _IS_SAME_TYPE(arr, arr[0])
#define _MUST_BE_ARRAY(arr) _MUST_SAME_TYPE(arr, arr[0])
#define ARRAY_SIZE(arr) ((int)((sizeof(arr) / sizeof((arr)[0])) + _MUST_BE_ARRAY(arr)))
#define ARRAY_LAST(arr) (ARRAY_SIZE(arr) - 1)
#define ARRAY_INIT(arr, val) {[0 ... ARRAY_LAST(arr)] = (val)}
#define ARRAY_PTR(arr) PTR(arr, ARRAY_SIZE(arr))

// Trick
#define _ARGS_NUM_FIRST(count, args...) count
#define _ARGS_NUM(_, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, args...) _ARGS_NUM_FIRST(args)
#define ARGS_NUM(args...) _ARGS_NUM(_, ##args, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define DEFAULT(default_val, val) __builtin_choose_expr(ARGS_NUM(val) == 0, default_val, val + 0)

// Wait
#define TIMEOUT 100

#define LOOP_FOR(condition)                                                                        \
    do                                                                                             \
    {                                                                                              \
        while (!(condition))                                                                       \
        {                                                                                          \
        }                                                                                          \
    } while (0)

#define _WAIT_FOR(condition, timeout)                                                              \
    ({                                                                                             \
        bool _is_timeout = true;                                                                   \
        for (int _i = 0; _i < (timeout); _i++)                                                     \
        {                                                                                          \
            if (condition)                                                                         \
            {                                                                                      \
                _is_timeout = false;                                                               \
                break;                                                                             \
            }                                                                                      \
        }                                                                                          \
        _is_timeout;                                                                               \
    })
#define WAIT_FOR(condition, timeout...) _WAIT_FOR(condition, DEFAULT(TIMEOUT, timeout))

// Print
// #define PRIX(x)
//     _Generic((x),
//         uint32_t: "0x%08" PRIX32,
//         uint16_t: "0x%04" PRIX16,
//         uint8_t: "0x%02" PRIX8,
//         default: "0x%X\r\n")

#define PRIX(x)                                                                                    \
    _Generic((x),                                                                                  \
        uint32_t: "0x%08lx",                                                                       \
        uint16_t: "0x%04x",                                                                        \
        uint8_t: "0x%02x",                                                                         \
        char: "%c",                                                                                \
        default: "0x%x")

#define PRINT_LINE() printf("[%s() in %s(%d)]", __func__, __FILE__, __LINE__)
#define PRINT_VAL(val)                                                                             \
    do                                                                                             \
    {                                                                                              \
        printf(#val " = ");                                                                        \
        printf(PRIX(val), (val));                                                                  \
        printf("\r\n");                                                                            \
    } while (0)
#define PRINT_ARRAY(arr)                                                                           \
    do                                                                                             \
    {                                                                                              \
        for (int _i = 0; _i < ARRAY_SIZE(arr); _i++)                                               \
        {                                                                                          \
            printf(#arr "[%02d] = ", _i);                                                          \
            printf(PRIX(arr[0]), arr[_i]);                                                         \
            printf("\r\n");                                                                        \
        }                                                                                          \
    } while (0)
