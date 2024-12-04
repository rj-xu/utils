#include <string.h>

#include "buf.h"

static int CharToInt(char c)
{
    switch (c)
    {
    case '0' ... '9':
        return c - '0';
    case 'a' ... 'f':
        return c - 'a' + 10;
    case 'A' ... 'F':
        return c - 'A' + 10;
    default:
        return -1;
    }
}

mut_t BufNewByHex(str_t hex)
{
    let len = strlen(hex);
    let_mut buf = malloc_buf(len / 2);
    if (buf == NULL)
    {
        return buf;
    }

    int i = 0;
    int j = 0;
    while (hex[i])
    {
        if (hex[i] == ' ')
        {
            i++;
            continue;
        }

        int a = CharToInt(hex[i]);
        int b = CharToInt(hex[i + 1]);
        buf->ptr[j] = (a << 4) | b;

        i += 2;
        j++;
    }
    buf->bytes = j;
    return buf;
}

mut_t BufNewByPtr(const uint8_t *const ptr, size_t bytes)
{
    let_mut buf = malloc_buf(bytes);
    if (buf)
    {
        memcpy(buf->ptr, ptr, bytes);
        buf->bytes = bytes;
    }
    return buf;
}

inline mut_t BufMerge(mut_t dest, buf_t src0, buf_t src1)
{
    if (dest != src0)
    {
        memcpy(dest->ptr, src0->ptr, src0->bytes);
    }
    memcpy(dest->ptr + src0->bytes, src1->ptr, src1->bytes);
    dest->bytes = src0->bytes + src1->bytes;
    return dest;
}

inline mut_t BufCopy(mut_t dest, uint8_t *ptr, size_t bytes)
{
    memcpy(dest->ptr, ptr, bytes);
    dest->bytes += bytes;
    return dest;
}

inline bool BufIsSame(buf_t src0, buf_t src1)
{
    if (src0->bytes != src1->bytes)
    {
        return false;
    }

    for (int i = 0; i < src0->bytes; i++)
    {
        if (src0->ptr[i] != src1->ptr[i])
        {
            return false;
        }
    }

    return true;
}
