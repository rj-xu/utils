#pragma once

#define _COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _n, ...) \
    _n
#define COUNT_ARGS(args...)                                                                        \
    _COUNT_ARGS(, ##args, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define DEFAULT(default_val, val) __builtin_choose_expr(COUNT_ARGS(val) == 0, default_val, val + 0)
