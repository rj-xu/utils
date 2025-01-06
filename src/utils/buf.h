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

typedef const _buf_t *buf_t;
typedef _buf_t *mbuf_t;

typedef __PACKED_STRUCT
{
    int bytes;
    uint8_t *ptr;
}
_ptr_t;

typedef const _ptr_t *ptr_t;
typedef _ptr_t *mptr_t;

#define PTR(p, b) ((ptr_t) & (_ptr_t){.ptr = (void *)(p), .bytes = (b)})
#define MPTR(p, b...) ((mptr_t) & (_ptr_t){.ptr = (void *)(p), .bytes = DEFAULT(0, b)})
static inline void memset_ptr(mptr_t p, int e)
{
    return memset(p->ptr, e, p->bytes);
}

#define LOG_PTRX(lv, p, n...)                                                                      \
    do                                                                                             \
    {                                                                                              \
        STATIC_ASSERT(IS_SAME_TYPE(p, ptr_t) || IS_SAME_TYPE(p, mptr_t));                          \
        LOG_PTR(lv, (p)->ptr, DEFAULT((p)->bytes, n));                                             \
    } while (0)
#define LOG_DEBUG_PTRX(ptr, n...) LOG_PTRX(DEBUG, ptr, ##n)
#define LOG_TRACE_PTRX(ptr, n...) LOG_PTRX(TRACE, ptr, ##n)

#define BUF_TO_PTR(b) PTR(b->ptr, b->bytes)
#define PTR_TO_BUF(p) BufNewByPtr(p->ptr, p->bytes)

typedef struct
{
    uint8_t is_buf;
    union {
        buf_t buf;
        ptr_t ptr;
    };
} ubuf_t;

#define LOG_BUF(lv, buf, n...)                                                                     \
    do                                                                                             \
    {                                                                                              \
        STATIC_ASSERT(IS_SAME_TYPE(buf, mbuf_t) || IS_SAME_TYPE(buf, buf_t));                      \
        LOG_PTR(lv, (buf)->ptr, DEFAULT((buf)->bytes, n));                                         \
    } while (0)
#define LOG_DEBUG_BUF(buf, n...) LOG_BUF(DEBUG, buf, ##n)
#define LOG_TRACE_BUF(buf, n...) LOG_BUF(TRACE, buf, ##n)

static inline mbuf_t malloc_buf(size_t b)
{
    mbuf_t buf = malloc(sizeof(_buf_t) + b);
    if (buf)
    {
        buf->bytes = 0;
        buf->_cap = b;
    }
    return buf;
}
static inline mbuf_t calloc_buf(size_t b)
{
    mbuf_t buf = calloc(sizeof(_buf_t) + b, 1);
    if (buf)
    {
        buf->bytes = b;
        buf->_cap = b;
    }
    return buf;
}

static inline mbuf_t realloc_buf(mbuf_t buf, size_t b)
{
    if (buf->_cap >= b)
        return buf;

    mbuf_t buf2 = realloc(buf, sizeof(_buf_t) + b);
    if (buf2)
    {
        buf2->_cap = b;
    }
    return buf2;
}

static inline void memset_buf(mbuf_t buf, uint8_t c)
{
    return memset(buf->ptr, c, buf->bytes);
}

#define alloca_buf(b)                                                                              \
    ({                                                                                             \
        size_t _b = (b);                                                                           \
        mbuf_t _buf = alloca(sizeof(_buf_t) + _b);                                                 \
        if (_buf)                                                                                  \
        {                                                                                          \
            _buf->bytes = 0;                                                                       \
            _buf->_cap = _b;                                                                       \
        }                                                                                          \
        _buf;                                                                                      \
    })

static inline void _free_mbuf(mbuf_t *buf)
{
    LOG_TRACE("Free %p", *buf);
    return free(*buf);
}

static inline void _free_buf(buf_t *buf)
{
    LOG_TRACE("Free %p", *buf);
    return free((mbuf_t)*buf);
}

// #define _FREE_BUF(x) _Generic(x, mbuf_t: _free_mut, buf_t: _free_buf)(&x)
#define auto_buf_t buf_t __CLEANUP(_free_buf)
#define auto_mbuf_t mbuf_t __CLEANUP(_free_mbuf)

mbuf_t BufNewByHex(str_t hex);
mbuf_t BufNewByPtr(const void *ptr, size_t bytes);
mbuf_t BufMerge(mbuf_t dest, buf_t src0, buf_t src1);
mbuf_t BufCopy(mbuf_t dest, uint8_t *ptr, size_t bytes);
bool BufIsSame(buf_t src0, buf_t src1);
