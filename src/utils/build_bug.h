#pragma once

#include <assert.h>

#define STATIC_ASSERT(e)                                                                           \
    static_assert(e, "static_assert") // '_Static_assert' with no message is a C23 extension

#define BUILD_BUG_ON_ZERO(e)                                                                       \
    ((int)(sizeof(struct { int : (-!!(e)); }))) // May use static_assert() instead
#define BUILD_BUG_ON(e) BUILD_BUG_ON_ZERO(!e)   // May use static_assert() instead
