#pragma once

#include <stdarg.h>

#include "log.h"

extern LogLv_t g_log_lv;

const char *const LOG2_COLOR[] = {
    ANSI_COLOR_CYAN, ANSI_COLOR_BLUE, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, ANSI_COLOR_RED,
};
const char *const LOG2_TAG[] = {
    "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR",
};

static inline void log(LogLv_t lv, const char *fmt, ...)
{

    printf(fmt, g_log_lv);

    if (lv >= LOG_LV)
    {
        printf("%s[%s] ", LOG2_COLOR[lv], LOG2_TAG[lv]);

        va_list args;
        va_start(args, fmt);
        printf(fmt, args);
        va_end(args);

        printf(ENDL);
    }
}
