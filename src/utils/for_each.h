#pragma once

#define _FE_CALL_00(A, B) A##B
#define _FE_CALL_01(A, B) A##B
#define _FE_CALL_02(A, B) A##B
#define _FE_CALL_03(A, B) A##B
#define _FE_CALL_04(A, B) A##B
#define _FE_CALL_04(A, B) A##B
#define _FE_CALL_05(A, B) A##B
#define _FE_CALL_06(A, B) A##B
#define _FE_CALL_07(A, B) A##B
#define _FE_CALL_08(A, B) A##B
#define _FE_CALL_09(A, B) A##B
#define _FE_CALL_10(A, B) A##B
#define _FE_CALL_11(A, B) A##B
#define _FE_CALL_12(A, B) A##B
#define _FE_CALL_13(A, B) A##B
#define _FE_CALL_14(A, B) A##B
#define _FE_CALL_15(A, B) A##B
#define _FE_CALL_16(A, B) A##B

// clang-format off
#define _FE_N00()
#define _FE_N01(Func, A, args...) Func(A);
#define _FE_N02(Func, A, args...) Func(A); _FE_CALL_01(_FE_N01, (Func, ##args))
#define _FE_N03(Func, A, args...) Func(A); _FE_CALL_02(_FE_N02, (Func, ##args))
#define _FE_N04(Func, A, args...) Func(A); _FE_CALL_03(_FE_N03, (Func, ##args))
#define _FE_N05(Func, A, args...) Func(A); _FE_CALL_04(_FE_N04, (Func, ##args))
#define _FE_N06(Func, A, args...) Func(A); _FE_CALL_05(_FE_N05, (Func, ##args))
#define _FE_N07(Func, A, args...) Func(A); _FE_CALL_06(_FE_N06, (Func, ##args))
#define _FE_N08(Func, A, args...) Func(A); _FE_CALL_07(_FE_N07, (Func, ##args))
#define _FE_N09(Func, A, args...) Func(A); _FE_CALL_08(_FE_N08, (Func, ##args))
#define _FE_N10(Func, A, args...) Func(A); _FE_CALL_09(_FE_N09, (Func, ##args))
#define _FE_N11(Func, A, args...) Func(A); _FE_CALL_10(_FE_N10, (Func, ##args))
#define _FE_N12(Func, A, args...) Func(A); _FE_CALL_11(_FE_N11, (Func, ##args))
#define _FE_N13(Func, A, args...) Func(A); _FE_CALL_12(_FE_N12, (Func, ##args))
#define _FE_N14(Func, A, args...) Func(A); _FE_CALL_13(_FE_N13, (Func, ##args))
#define _FE_N15(Func, A, args...) Func(A); _FE_CALL_14(_FE_N14, (Func, ##args))
#define _FE_N16(Func, A, args...) Func(A); _FE_CALL_15(_FE_N15, (Func, ##args))
#define _FE_N17(...) "ERROR: FOR_EACH ONLY supports up to 16 args"
// clang-format on

#define _FE_NUM(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17,    \
                NUM, args...)                                                                      \
    NUM
#define FOR_EACH(Func, args...)                                                                    \
    do                                                                                             \
    {                                                                                              \
        _FE_CALL_00(_FE_NUM(_0, ##args, _FE_N17, _FE_N16, _FE_N15, _FE_N14, _FE_N13, _FE_N12,      \
                            _FE_N11, _FE_N10, _FE_N09, _FE_N08, _FE_N07, _FE_N06, _FE_N05,         \
                            _FE_N04, _FE_N03, _FE_N02, _FE_N01, _FE_N00),                          \
                    (Func, ##args))                                                                \
    } while (0)

// FOR_EACH();
// FOR_EACH(DO);
// FOR_EACH(DO,0);
// FOR_EACH(DO,0,1);
// FOR_EACH(DO,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
// FOR_EACH(DO,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
// FOR_EACH(DO,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17);
