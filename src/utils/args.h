#pragma once

#define _COUNT_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,     \
                    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,     \
                    _32, _n, ...)                                                                  \
    _n
#define COUNT_ARGS(args...)                                                                        \
    _COUNT_ARGS(, ##args, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15,  \
                14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define DEFAULT(default, val...) __builtin_choose_expr(COUNT_ARGS(val) == 0, default, val + 0)
#define DEFAULT_STR(default, val...) __builtin_choose_expr(COUNT_ARGS(val) == 0, default, val "")

// COUNT_ARGS()
// COUNT_ARGS(a0)
// COUNT_ARGS(a0, a1)
// COUNT_ARGS(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18,
// a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30)
// COUNT_ARGS(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18,
// a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31)
// COUNT_ARGS(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18,
// a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32)
// COUNT_ARGS(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18,
// a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a33)
