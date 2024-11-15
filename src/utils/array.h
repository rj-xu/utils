#pragma once

#include "print.h"
#include "types.h"

#define IS_ARRAY(arr) (!IS_SAME_TYPE(arr, &(arr)[0]))
#define MUST_BE_ARRAY(arr) BUILD_BUG_ON(IS_ARRAY(arr))

#define ARRAY_SIZE(arr) ((size_t)((sizeof(arr) / sizeof((arr)[0])) + MUST_BE_ARRAY(arr)))
#define ARRAY_LAST(arr) (ARRAY_SIZE(arr) - 1)
#define ARRAY_INIT(arr, val) {[0 ... ARRAY_LAST(arr)] = (val)}

#define _PRINT_ARRAY(lv, arr, n)                                                                   \
    do                                                                                             \
    {                                                                                              \
        for (size_t _i = 0; _i < (n); _i++)                                                        \
        {                                                                                          \
            if (_i % 4 == 0)                                                                       \
            {                                                                                      \
                LOG_TAG(lv, "[ %p] ", arr + _i);                                                   \
            }                                                                                      \
            printf(PRI("", arr[0], " "), arr[_i]);                                                 \
            if ((_i + 1) % 4 == 0 || _i == (n) - 1)                                                \
            {                                                                                      \
                printf(ENDL);                                                                      \
            }                                                                                      \
        }                                                                                          \
    } while (0)

#define PRINT_ARRAY(lv, arr, n...)                                                                 \
    do                                                                                             \
    {                                                                                              \
        const size_t _n = DEFAULT(ARRAY_SIZE(arr), n);                                             \
        LOG(lv, #arr "[%u] (%p, %u) =", ARRAY_SIZE(arr), arr, _n);                                 \
        _PRINT_ARRAY(lv, arr, _n);                                                                 \
    } while (0)

#define PRINT_PTR(lv, ptr, n)                                                                      \
    do                                                                                             \
    {                                                                                              \
        const size_t _n = (n);                                                                     \
        LOG(lv, #ptr " (%p, %u) =", ptr, _n);                                                      \
        _PRINT_ARRAY(lv, ptr, _n);                                                                 \
    } while (0)
