#pragma once

// clang-format off
#define LOG_LV_TRACE 0
#define LOG_LV_DEBUG 1
#define LOG_LV_INFO  2
#define LOG_LV_WARN  3
#define LOG_LV_ERROR 4
#define LOG_LV_CRIT  5

#define LOG_LV LOG_LV_TRACE

#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
// clang-format on

#define LOG_PRINT(tag, color, fmt, args...)                                                        \
    do                                                                                             \
    {                                                                                              \
        printf(color);                                                                             \
        printf("[%s] " fmt, tag, ##args);                                                          \
        printf(ANSI_COLOR_RESET "\r\n");                                                           \
    } while (0)

#define LOG_PRINT_DEBUG(tag, color, fmt, args...)                                                  \
    LOG_PRINT(tag, color, fmt " (%s(%d) in %s())", ##args, __FILE__, __LINE__, __func__)

#if LOG_LV_TRACE >= LOG_LV
#define LOG_TRACE(args...) LOG_PRINT_DEBUG("TRACE", ANSI_COLOR_CYAN, args)
#else
#define LOG_TRACE(...)
#endif

#if LOG_LV_DEBUG >= LOG_LV
#define LOG_DEBUG(args...) LOG_PRINT("DEBUG", ANSI_COLOR_BLUE, args)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LV_INFO >= LOG_LV
#define LOG_INFO(args...) LOG_PRINT("INFO ", ANSI_COLOR_GREEN, args)
#else
#define LOG_INFO(...)
#endif

#if LOG_LV_WARN >= LOG_LV
#define LOG_WARN(args...) LOG_PRINT("WARN ", ANSI_COLOR_YELLOW, args)
#else
#define LOG_WARN(...)
#endif

#if LOG_LV_ERROR >= LOG_LV
#define LOG_ERROR(args...) LOG_PRINT_DEBUG("ERROR", ANSI_COLOR_RED, args)
#else
#define LOG_ERROR(...)
#endif
