#pragma once

#define let __auto_type const
#define let_mut __auto_type

#define AUTO(Type, Func) Type __attribute__((cleanup(Func)))

typedef unsigned int uint;

typedef void *any;

typedef const char *const str_t;
