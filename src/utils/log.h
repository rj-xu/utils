#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    LOG_LV_TRACE = 0,
    LOG_LV_DEBUG,
    LOG_LV_INFO,
    LOG_LV_WARN,
    LOG_LV_ERROR,
    // LOG_LV_FATAL,
} LogLv_t;

// #define LOG_LV LOG_LV_TRACE
#define LOG_LV LOG_LV_DEBUG

// clang-format off
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[00m"
// clang-format on

#define LINE "================================================================================"
#define ENDL ANSI_COLOR_RESET "\r\n"

#define LOG_PRINT(lv, tag, color, fmt, args...)                                                    \
    do                                                                                             \
    {                                                                                              \
        if (lv >= LOG_LV)                                                                          \
        {                                                                                          \
            printf(color "[%s] ", tag);                                                            \
            printf(fmt, ##args);                                                                   \
            printf(ENDL);                                                                          \
        }                                                                                          \
    } while (0)

#define LOG_PRINT_DEBUG(lv, tag, color, fmt, args...)                                              \
    do                                                                                             \
    {                                                                                              \
        if (lv >= LOG_LV)                                                                          \
        {                                                                                          \
            printf(color "[%s] ", tag);                                                            \
            printf(fmt, ##args);                                                                   \
            printf(ANSI_COLOR_MAGENTA " (%s(%d) in %s())" ENDL, __FILE__, __LINE__, __func__);     \
        }                                                                                          \
    } while (0)

#define LOG_PRINT_TAG(lv, tag, color)                                                              \
    do                                                                                             \
    {                                                                                              \
        if (lv >= LOG_LV)                                                                          \
        {                                                                                          \
            printf(color "[%s] ", tag);                                                            \
        }                                                                                          \
    } while (0)

// clang-format off
#define LOG_TRACE(fmt, args...) LOG_PRINT_DEBUG(LOG_LV_TRACE, "TRACE", ANSI_COLOR_CYAN  , fmt, ##args)
#define LOG_DEBUG(fmt, args...) LOG_PRINT(      LOG_LV_DEBUG, "DEBUG", ANSI_COLOR_BLUE  , fmt, ##args)
#define LOG_INFO( fmt, args...) LOG_PRINT(      LOG_LV_INFO , "INFO ", ANSI_COLOR_GREEN , fmt, ##args)
#define LOG_WARN( fmt, args...) LOG_PRINT(      LOG_LV_WARN , "WARN ", ANSI_COLOR_YELLOW, fmt, ##args)
#define LOG_ERROR(fmt, args...) LOG_PRINT_DEBUG(LOG_LV_ERROR, "ERROR", ANSI_COLOR_RED   , fmt, ##args)
// clang-format on

// clang-format off
#define LOG_TAG_TRACE(fmt, args...) LOG_PRINT_TAG(LOG_LV_TRACE, "TRACE", ANSI_COLOR_CYAN  )
#define LOG_TAG_DEBUG(fmt, args...) LOG_PRINT_TAG(LOG_LV_DEBUG, "DEBUG", ANSI_COLOR_BLUE  )
#define LOG_TAG_INFO( fmt, args...) LOG_PRINT_TAG(LOG_LV_INFO , "INFO ", ANSI_COLOR_GREEN )
#define LOG_TAG_WARN( fmt, args...) LOG_PRINT_TAG(LOG_LV_WARN , "WARN ", ANSI_COLOR_YELLOW)
#define LOG_TAG_ERROR(fmt, args...) LOG_PRINT_TAG(LOG_LV_ERROR, "ERROR", ANSI_COLOR_RED   )
// clang-format on

#define TRACE TRACE
#define DEBUG DEBUG
#define INFO INFO
#define WARN WARN
#define ERROR ERROR
#define FATAL FATAL

#define LOG(LV, fmt, args...) LOG_##LV(fmt, ##args)
#define LOG_TAG(LV) LOG_TAG_##LV()
#define LOG_PRINTF(LV, fmt, args...)                                                               \
    do                                                                                             \
    {                                                                                              \
        if (LOG_LV_##LV >= LOG_LV)                                                                 \
        {                                                                                          \
            printf(fmt, ##args);                                                                   \
        }                                                                                          \
    } while (0)
#define LOG_ENDL(lv) LOG_PRINTF(lv, ENDL)

void LogBanner();
