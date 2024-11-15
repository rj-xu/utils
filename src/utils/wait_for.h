#pragma once

#include <stdbool.h>

#define TIMEOUT 100

#define LOOP_FOR(condition)                                                                        \
    do                                                                                             \
    {                                                                                              \
        while (!(condition))                                                                       \
        {                                                                                          \
        }                                                                                          \
    } while (0)
#define LOOP() LOOP_FOR(false)

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
