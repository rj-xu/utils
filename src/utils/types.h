#pragma once

#define let __auto_type const // NOLINT(readability-identifier-naming)
#define let_mut __auto_type   // NOLINT(readability-identifier-naming)

typedef unsigned int uint;

typedef void *any;

typedef const char *const str_t;

#define IS_SAME_TYPE(val_0, val_1) __builtin_types_compatible_p(typeof(val_0), typeof(val_1))
#define IS_TYPE(val, type) __builtin_types_compatible_p(typeof(a), type)
