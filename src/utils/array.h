#pragma once

#include "build_bug.h"
#include "print.h"

#define IS_ARR(arr) (!IS_SAME_TYPE(arr, &(arr)[0]))
#define MUST_BE_ARR(arr) BUILD_BUG_ON_TRUE(IS_ARR(arr))

#define ARR_SIZE(arr) ((size_t)((sizeof(arr) / sizeof((arr)[0])) + MUST_BE_ARR(arr)))
#define ARR_MEMBER_SIZE(arr) (sizeof((arr)[0]))
#define ARR_LAST(arr) (ARR_SIZE(arr) - 1)
#define ARR_INIT(num, val) {[0 ...((num) - 1)] = (val)}

#define _LOG_ARR_TABLE(x)                                                                          \
    _Generic((x),                                                                                  \
        uint32_t: "[            ]         00         04         08         0A",                    \
        uint16_t: "[            ]     00     02     04     06",                                    \
        uint8_t: "[            ]   00   01   02   03",                                             \
        default: "[            ]")

#define _LOG_ARR(lv, arr, n)                                                                       \
    do                                                                                             \
    {                                                                                              \
        if (arr == NULL)                                                                           \
        {                                                                                          \
            LOG_WARN("NULL Pointer");                                                              \
            break;                                                                                 \
        }                                                                                          \
        LOG(lv, _LOG_ARR_TABLE(arr[0]));                                                           \
        for (size_t _i = 0; _i < (n); _i++)                                                        \
        {                                                                                          \
            if (_i % 4 == 0)                                                                       \
            {                                                                                      \
                LOG_TAG(lv);                                                                       \
                LOG_PRINTF(lv, "[ %p ] ", arr + _i);                                               \
            }                                                                                      \
            LOG_PRINTF(lv, PRI("", arr[0], " "), arr[_i]);                                         \
            if ((_i + 1) % 4 == 0 || _i == (n) - 1)                                                \
            {                                                                                      \
                LOG_ENDL(lv);                                                                      \
            }                                                                                      \
        }                                                                                          \
    } while (0)

#define LOG_ARR(lv, arr, n...)                                                                     \
    do                                                                                             \
    {                                                                                              \
        const size_t _n = DEFAULT(ARR_SIZE(arr), n);                                               \
        LOG(lv, #arr "[%u] (%p, %u) =", ARR_SIZE(arr), arr, _n);                                   \
        _LOG_ARR(lv, arr, _n);                                                                     \
    } while (0)
#define LOG_DEBUG_ARR(arr, n...) LOG_ARR(DEBUG, arr, ##n)

#define LOG_PTR(lv, ptr, n)                                                                        \
    do                                                                                             \
    {                                                                                              \
        const size_t _n = (n);                                                                     \
        LOG(lv, #ptr " (%p, %u) =", ptr, _n);                                                      \
        _LOG_ARR(lv, ptr, _n);                                                                     \
    } while (0)
#define LOG_DEBUG_PTR(ptr, n) LOG_PTR(DEBUG, ptr, n)
