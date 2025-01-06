#include <string.h>

#include "buf.h"
#include "reg32.h"

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

__UNUSED static int HexLen(str_t hex)
{
    int len = 0;
    while (*hex++)
    {
        switch (*hex)
        {
        case '0' ... '9':
        case 'a' ... 'f':
        case 'A' ... 'F':
            len++;
        default:
            break;
        }
    }
    return len;
}

mbuf_t BufNewByHex(str_t hex)
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

__UNUSED mbuf_t BufNewByHexWithPad(str_t hex)
{
    let len = strlen(hex);
    let_mut buf = malloc_buf((len / 2) + BLOCK);
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

mbuf_t BufNewByPtr(const void *ptr, size_t bytes)
{
    let_mut buf = malloc_buf(bytes);
    if (buf)
    {
        memcpy(buf->ptr, ptr, bytes);
        buf->bytes = bytes;
    }
    return buf;
}

mbuf_t BufMerge(mbuf_t dest, buf_t src0, buf_t src1)
{
    if (dest == src0)
    {
        memcpy(dest->ptr + src0->bytes, src1->ptr, src1->bytes);
        dest->bytes += src1->bytes;
    }
    else if (dest == src1)
    {
        memmove(dest->ptr + src0->bytes, src1->ptr, src1->bytes);
        memcpy(dest->ptr, src0->ptr, src0->bytes);
        dest->bytes += src0->bytes;
    }
    else
    {
        memcpy(dest->ptr, src0->ptr, src0->bytes);
        memcpy(dest->ptr + src0->bytes, src1->ptr, src1->bytes);
        dest->bytes = src0->bytes + src1->bytes;
    }

    return dest;
}

mbuf_t BufCopy(mbuf_t dest, uint8_t *ptr, size_t bytes)
{
    memcpy(dest->ptr, ptr, bytes);
    dest->bytes += bytes;
    return dest;
}

bool BufIsSame(buf_t src0, buf_t src1)
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
