#pragma once

#include "args.h"
#include "concat.h"

// clang-format off
#define _FOR_EACH_1( Func, a0, args...) Func(a0)
#define _FOR_EACH_2( Func, a0, args...) Func(a0); _FOR_EACH_1( Func, args)
#define _FOR_EACH_3( Func, a0, args...) Func(a0); _FOR_EACH_2( Func, args)
#define _FOR_EACH_4( Func, a0, args...) Func(a0); _FOR_EACH_3( Func, args)
#define _FOR_EACH_5( Func, a0, args...) Func(a0); _FOR_EACH_4( Func, args)
#define _FOR_EACH_6( Func, a0, args...) Func(a0); _FOR_EACH_5( Func, args)
#define _FOR_EACH_7( Func, a0, args...) Func(a0); _FOR_EACH_6( Func, args)
#define _FOR_EACH_8( Func, a0, args...) Func(a0); _FOR_EACH_7( Func, args)
#define _FOR_EACH_9( Func, a0, args...) Func(a0); _FOR_EACH_8( Func, args)
#define _FOR_EACH_10(Func, a0, args...) Func(a0); _FOR_EACH_9( Func, args)
#define _FOR_EACH_11(Func, a0, args...) Func(a0); _FOR_EACH_10(Func, args)
#define _FOR_EACH_12(Func, a0, args...) Func(a0); _FOR_EACH_11(Func, args)
#define _FOR_EACH_13(Func, a0, args...) Func(a0); _FOR_EACH_12(Func, args)
#define _FOR_EACH_14(Func, a0, args...) Func(a0); _FOR_EACH_13(Func, args)
#define _FOR_EACH_15(Func, a0, args...) Func(a0); _FOR_EACH_14(Func, args)
#define _FOR_EACH_16(Func, a0, args...) Func(a0); _FOR_EACH_15(Func, args)
#define _FOR_EACH_17(Func, a0, args...) Func(a0); _FOR_EACH_16(Func, args)
#define _FOR_EACH_18(Func, a0, args...) Func(a0); _FOR_EACH_17(Func, args)
#define _FOR_EACH_19(Func, a0, args...) Func(a0); _FOR_EACH_18(Func, args)
#define _FOR_EACH_20(Func, a0, args...) Func(a0); _FOR_EACH_19(Func, args)
#define _FOR_EACH_21(Func, a0, args...) Func(a0); _FOR_EACH_20(Func, args)
#define _FOR_EACH_22(Func, a0, args...) Func(a0); _FOR_EACH_21(Func, args)
#define _FOR_EACH_23(Func, a0, args...) Func(a0); _FOR_EACH_22(Func, args)
#define _FOR_EACH_24(Func, a0, args...) Func(a0); _FOR_EACH_23(Func, args)
#define _FOR_EACH_25(Func, a0, args...) Func(a0); _FOR_EACH_24(Func, args)
#define _FOR_EACH_26(Func, a0, args...) Func(a0); _FOR_EACH_25(Func, args)
#define _FOR_EACH_27(Func, a0, args...) Func(a0); _FOR_EACH_26(Func, args)
#define _FOR_EACH_28(Func, a0, args...) Func(a0); _FOR_EACH_27(Func, args)
#define _FOR_EACH_29(Func, a0, args...) Func(a0); _FOR_EACH_28(Func, args)
#define _FOR_EACH_30(Func, a0, args...) Func(a0); _FOR_EACH_29(Func, args)
#define _FOR_EACH_31(Func, a0, args...) Func(a0); _FOR_EACH_30(Func, args)
#define _FOR_EACH_32(Func, a0, args...) Func(a0); _FOR_EACH_31(Func, args)
// clang-format on

#define FOR_EACH(Func, args...)                                                                    \
    do                                                                                             \
    {                                                                                              \
        CONCAT(_FOR_EACH_, COUNT_ARGS(args))(Func, args);                                          \
    } while (0)

#define FOR_EACH_SEMI(Func, args...) CONCAT(_FOR_EACH_, COUNT_ARGS(args))(Func, args)

// FOR_EACH();
// FOR_EACH(Do);
// FOR_EACH(Do, a0);
// FOR_EACH(Do, a0, a1);
// FOR_EACH(Do, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
// FOR_EACH(Do, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
// FOR_EACH(Do, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);

// clang-format off
#define _FOR_EACH_COMMA_1( Func, a0, args...) Func(a0)
#define _FOR_EACH_COMMA_2( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_1(Func, args)
#define _FOR_EACH_COMMA_3( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_2(Func, args)
#define _FOR_EACH_COMMA_4( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_3(Func, args)
#define _FOR_EACH_COMMA_5( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_4(Func, args)
#define _FOR_EACH_COMMA_6( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_5(Func, args)
#define _FOR_EACH_COMMA_7( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_6(Func, args)
#define _FOR_EACH_COMMA_8( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_7(Func, args)
#define _FOR_EACH_COMMA_9( Func, a0, args...) Func(a0), _FOR_EACH_COMMA_8(Func, args)
#define _FOR_EACH_COMMA_10(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_9(Func, args)
#define _FOR_EACH_COMMA_11(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_10(Func, args)
#define _FOR_EACH_COMMA_12(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_11(Func, args)
#define _FOR_EACH_COMMA_13(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_12(Func, args)
#define _FOR_EACH_COMMA_14(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_13(Func, args)
#define _FOR_EACH_COMMA_15(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_14(Func, args)
#define _FOR_EACH_COMMA_16(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_15(Func, args)
#define _FOR_EACH_COMMA_17(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_16(Func, args)
#define _FOR_EACH_COMMA_18(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_17(Func, args)
#define _FOR_EACH_COMMA_19(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_18(Func, args)
#define _FOR_EACH_COMMA_20(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_19(Func, args)
#define _FOR_EACH_COMMA_21(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_20(Func, args)
#define _FOR_EACH_COMMA_22(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_21(Func, args)
#define _FOR_EACH_COMMA_23(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_22(Func, args)
#define _FOR_EACH_COMMA_24(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_23(Func, args)
#define _FOR_EACH_COMMA_25(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_24(Func, args)
#define _FOR_EACH_COMMA_26(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_25(Func, args)
#define _FOR_EACH_COMMA_27(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_26(Func, args)
#define _FOR_EACH_COMMA_28(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_27(Func, args)
#define _FOR_EACH_COMMA_29(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_28(Func, args)
#define _FOR_EACH_COMMA_30(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_29(Func, args)
#define _FOR_EACH_COMMA_31(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_30(Func, args)
#define _FOR_EACH_COMMA_32(Func, a0, args...) Func(a0), _FOR_EACH_COMMA_31(Func, args)
// clang-format on

#define FOR_EACH_COMMA(Func, args...) CONCAT(_FOR_EACH_COMMA_, COUNT_ARGS(args))(Func, args)

// FOR_EACH_COMMA(Do, a0, a1, a2)
