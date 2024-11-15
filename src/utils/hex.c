#include <string.h>

#include "hex.h"

int CharToInt(char c)
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

    return -1;
}

int HexToBuf(mut_t buf, str_t hex)
{
    let len = strlen(hex);

    if (len % 2)
    {
        return -1;
    }

    for (int i = 0; i < len; i += 2)
    {
        int a = CharToInt(hex[i]);
        int b = CharToInt(hex[i + 1]);

        buf->ptr[i / 2] = (a << 4) | b;
    }
    buf->bytes = len / 2;

    return 0;
}

mut_t MallocBufFromHex(str_t hex)
{
    let len = strlen(hex);

    if (len % 2)
    {
        return NULL;
    }

    let bytes = len / 2;
    let_mut buf = MALLOC_BUF(bytes);

    for (int i = 0; i < len; i += 2)
    {
        int a = CharToInt(hex[i]);
        int b = CharToInt(hex[i + 1]);
        buf->ptr[i / 2] = (a << 4) | b;
    }

    buf->bytes = bytes;

    return buf;
}
