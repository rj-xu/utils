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
        int: s "%+d" e,                                                                            \
        unsigned int: s "%u" e,                                                                    \
        char: s "%c" e,                                                                            \
        bool: s "%d" e,                                                                            \
        void *: s "%p (void *)" e,                                                                 \
        const void *: s "%p (const void *)" e,                                                     \
        uint32_t *: s "%p (uint32_t *)" e,                                                         \
        const uint32_t *: s "%p (const uint32_t *)" e,                                             \
        uint8_t *: s "%p (uint8_t *)" e,                                                           \
        const uint8_t *: s "%p (const uint8_t *)" e,                                               \
        default: s "%d (Unkown Type)" e)

#define HELLO_WORLD()                                                                              \
    do                                                                                             \
    {                                                                                              \
        printf("Hello World! (compiled by GCC %d at %s on %s)\r\n", __GNUC__, __TIME__, __DATE__); \
        LOG_TRACE("This is TRACE");                                                                \
        LOG_DEBUG("This is DEBUG");                                                                \
        LOG_INFO("This is INFO");                                                                  \
        LOG_WARN("This is WARN");                                                                  \
        LOG_ERROR("This is ERROR");                                                                \
    } while (0)

#define LOG_FUNC(lv)                                                                               \
    do                                                                                             \
    {                                                                                              \
        LOG(lv, "%s() in %s(%d)", __func__, __FILE__, __LINE__);                                   \
    } while (0)
#define LOG_DEBUG_FUNC() LOG_FUNC(DEBUG)

#define LOG_VAL(lv, val) LOG(lv, PRI(#val " = ", val, ""), val)

#define LOG_TRACE_VAL(val) LOG_VAL(TRACE, val)
#define LOG_DEBUG_VAL(val) LOG_VAL(DEBUG, val)
#define LOG_INFO_VAL(val) LOG_VAL(INFO, val)
#define LOG_WARN_VAL(val) LOG_VAL(WARN, val)
#define LOG_ERROR_VAL(val) LOG_VAL(ERROR, val)
