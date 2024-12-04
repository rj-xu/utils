#pragma once

#include <alloca.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "array.h"
#include "attribute.h"
#include "build_bug.h"
#include "operator.h"
#include "print.h"

typedef __PACKED_STRUCT
{
    size_t bytes;  // buffer data bytes
    size_t _cap;   // buffer capacity (0 for static data)
    uint8_t ptr[]; // buffer data
}
_buf_t;

typedef const _buf_t const_buf_t;
typedef const _buf_t *const buf_t;
typedef _buf_t *mut_t;

typedef __PACKED_STRUCT
{
    size_t bytes;
    uint8_t *ptr;
}
_ptr_t;
typedef const _ptr_t *const ptr_t;
typedef _ptr_t *mptr_t;

#define LOG_BUF(lv, buf, n...)                                                                     \
    do                                                                                             \
    {                                                                                              \
        STATIC_ASSERT(IS_SAME_TYPE(buf, mut_t) || IS_SAME_TYPE(buf, buf_t));                       \
        LOG_PTR(lv, (buf)->ptr, DEFAULT((buf)->bytes, n));                                         \
    } while (0)
#define LOG_DEBUG_BUF(buf, n...) LOG_BUF(DEBUG, buf, ##n)
#define LOG_TRACE_BUF(buf, n...) LOG_BUF(TRACE, buf, ##n)

static inline mut_t malloc_buf(size_t b)
{
    mut_t buf = malloc(sizeof(_buf_t) + b);
    if (buf)
    {
        buf->bytes = 0;
        buf->_cap = b;
    }
    return buf;
}
static inline mut_t calloc_buf(size_t b)
{
    mut_t buf = calloc(sizeof(_buf_t) + b, 1);
    if (buf)
    {
        buf->bytes = b;
        buf->_cap = b;
    }
    return buf;
}

static inline mut_t realloc_buf(mut_t buf, size_t b)
{
    mut_t buf2 = realloc(buf, sizeof(_buf_t) + b);
    if (buf2)
    {
        if (buf == NULL)
        {
            buf2->bytes = 0;
        }
        buf2->_cap = b;
    }
    return buf2;
}

#define alloca_buf(b)                                                                              \
    ({                                                                                             \
        size_t _b = (b);                                                                           \
        mut_t _buf = alloca(sizeof(_buf_t) + _b);                                                  \
        if (_buf)                                                                                  \
        {                                                                                          \
            _buf->bytes = 0;                                                                       \
            _buf->_cap = _b;                                                                       \
        }                                                                                          \
        _buf;                                                                                      \
    })

static inline void _free_mut(mut_t *buf)
{
    LOG_TRACE("Free %p", *buf);
    return free(*buf);
}

static inline void _free_buf(buf_t *buf)
{
    LOG_TRACE("Free %p", *buf);
    return free((mut_t)*buf);
}

// #define _FREE_BUF(x) _Generic(x, mut_t: _free_mut, buf_t: _free_buf)(&x)
#define auto_buf_t buf_t __CLEANUP(_free_buf)
#define auto_mut_t mut_t __CLEANUP(_free_mut)

mut_t BufNewByHex(str_t hex);
mut_t BufNewByPtr(const uint8_t *const ptr, size_t bytes);
mut_t BufMerge(mut_t dest, buf_t src0, buf_t src1);
mut_t BufCopy(mut_t dest, uint8_t *ptr, size_t bytes);
bool BufIsSame(buf_t src0, buf_t src1);
