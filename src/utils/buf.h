#pragma once

#include <alloca.h>
#include <stdint.h>
#include <stdlib.h>

#include "array.h"
#include "print.h"
#include "types.h"

typedef struct __attribute__((packed, aligned(1)))
{
    size_t bytes;
    size_t _cap;
    union {
        uint8_t flags;
        struct
        {
            uint8_t is_const : 1;
            uint8_t is_stack : 1;
            uint8_t _rvsd : 6;
        } _flags;
    };
    uint8_t ptr[0];
} buf_t;

typedef const buf_t *const ptr_t;

typedef buf_t *mut_t;

static inline mut_t malloc_buf(size_t b)
{
    mut_t buf = malloc(sizeof(buf_t) + b);
    if (buf)
    {
        buf->bytes = 0;
        buf->_cap = b;
    }
    return buf;
}

static inline void free_buf(mut_t buf)
{
    return free(buf);
}

static inline mut_t calloc_buf(size_t b)
{
    mut_t buf = calloc(sizeof(buf_t) + b, 1);
    if (buf)
    {
        buf->bytes = 0;
        buf->_cap = b;
    }
    return buf;
}

static inline mut_t realloc_buf(mut_t buf, size_t b)
{
    mut_t buf = realloc(buf, sizeof(buf_t) + b);
    if (buf)
    {
        buf->bytes = 0;
        buf->_cap = b;
    }
    return buf;
}

#define ALLOCA_BUF(b)                                                                              \
    ({                                                                                             \
        mut_t _buf = alloca(sizeof(buf_t) + (b));                                                  \
        if (_buf)                                                                                  \
        {                                                                                          \
            _buf->bytes = 0;                                                                       \
            _buf->_cap = b;                                                                        \
        }                                                                                          \
        _buf;                                                                                      \
    })

#define PRINT_BUF(buf, n...)                                                                       \
    do                                                                                             \
    {                                                                                              \
        STATIC_ASSERT(IS_SAME_TYPE(buf, mut_t));                                                   \
        PRINT_PTR((buf)->ptr, DEFAULT((buf)->bytes, n));                                           \
    } while (0)
