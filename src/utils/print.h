#pragma once

#include <stdbool.h>

#include "log.h"

// #include <inttypes.h>
// #define PRI(x)
//     _Generic((x),
//         uint32_t: "0x%08" PRIX32,
//         uint16_t: "0x%04" PRIX16,
//         uint8_t: "0x%02" PRIX8,
//         default: "0x%X\r\n")

#define PRI(s, val, e)                                                                             \
    _Generic((val),                                                                                \
        uint32_t: s "0x%08lx" e,                                                                   \
        uint16_t: s "0x%04x" e,                                                                    \
        uint8_t: s "0x%02x" e,                                                                     \
        int: s "%d" e,                                                                             \
        char: s "%c" e,                                                                            \
        bool: s "%d" e,                                                                            \
        void *: s "%p" e,                                                                          \
        default: "UNKOWN TYPE\r\n")

#define _PRINT_FUNC(lv)                                                                            \
    do                                                                                             \
    {                                                                                              \
        LOG(lv, LINE);                                                                             \
        LOG(lv, " %s() in %s(%d) ", __func__, __FILE__, __LINE__);                                 \
        LOG(lv, LINE);                                                                             \
    } while (0)

#define PRINT_FUNC(...) _PRINT_FUNC(DEFAULT(DEBUG, __VA_ARGS__))

#define PRINT_VAL(lv, val) LOG(lv, PRI("", val, ""), val)
