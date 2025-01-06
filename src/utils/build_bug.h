#pragma once

#include <assert.h>

// '_Static_assert' with no message is a C23 extension
#define STATIC_ASSERT(e) static_assert(e, "")

#define BUILD_BUG_ON_ZERO(e) ((int)(sizeof(struct { int : (-!!(e)); })))
#define BUILD_BUG_ON_TRUE(e) BUILD_BUG_ON_ZERO(!(e))

#define IS_SAME_TYPE(val_0, val_1) __builtin_types_compatible_p(typeof(val_0), typeof(val_1))
#define IS_TYPE(val, type) __builtin_types_compatible_p(typeof(a), type)

// #define IS_CONSTANT(n) ((n) == (n))
#define IS_CONSTANT(n) __builtin_constant_p(n)
// #define IS_ODD(n) (((n) & 1) != 0)
#define ID_ODD(n) __builtin_parity(n)
#define IS_POWER_OF_2(n) ((n) != 0 && ((n) & ((n) - 1)) == 0)
#define IS_DEVIDED(n, x) ((n) % (x) == 0)

#define NUM_POWER_OF_2(n) ((n) + BUILD_BUG_ON_TRUE(IS_POWER_OF_2(n) && IS_CONSTANT(n)))
#define NUM_DEVIDED_BY_4(n, x) ((n) + BUILD_BUG_ON_TRUE(IS_DEVIDED(n, 4) && IS_CONSTANT(n)))
