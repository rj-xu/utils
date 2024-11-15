#pragma once

#include "buf.h"
#include "types.h"

int CharToInt(char c);
int HexToBuf(mut_t buf, str_t hex);

mut_t MallocBufFromHex(str_t hex);
mut_t MallocBufFromPtr(uint8_t *ptr, size_t size);
