#pragma once

#include <limits.h>

#define BITS CHAR_BIT

#define B 1
#define KB 1024
#define MB (1024 * 1024)
#define GB (1024 * 1024 * 1024)

#define IS_POWER_OF_2(n) ((n) != 0 && (((n) & ((n) - 1)) == 0))
