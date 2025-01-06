#pragma once

#define auto __auto_type
#define AUTO(Type, Func) Type __attribute__((cleanup(Func)))

#define let const auto
#define let_mut auto

typedef void *any;
typedef const char *str_t;

typedef unsigned int uint;

typedef __uint128_t uint128_t;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
