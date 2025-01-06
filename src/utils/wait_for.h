#pragma once

#include <stdbool.h>

#include "args.h"

#define TIMEOUT 100

#define LOOP_FOR(condition)                                                                        \
    do                                                                                             \
    {                                                                                              \
        while (!(condition))                                                                       \
        {                                                                                          \
        }                                                                                          \
    } while (0)

#define LOOP() LOOP_FOR(false)

#define WAIT_FOR(condition, timeout...)                                                            \
    ({                                                                                             \
        bool _is_timeout = true;                                                                   \
        int _timeout = DEFAULT(TIMEOUT, ##timeout);                                                \
        while (_timeout--)                                                                         \
        {                                                                                          \
            if (condition)                                                                         \
            {                                                                                      \
                _is_timeout = false;                                                               \
                break;                                                                             \
            }                                                                                      \
        }                                                                                          \
        _is_timeout;                                                                               \
    })

#define WAIT(timeout...)                                                                           \
    do                                                                                             \
    {                                                                                              \
        int _timeout = DEFAULT(TIMEOUT, ##timeout);                                                \
        while (_timeout--)                                                                         \
        {                                                                                          \
            __asm__ volatile("nop");                                                               \
        }                                                                                          \
    } while (0)
