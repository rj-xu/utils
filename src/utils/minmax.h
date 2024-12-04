#pragma once

#define MAX(a, b) (((a) > (b) ? (a) : (b)))
#define MIN(a, b) (((a) < (b) ? (a) : (b)))

#ifndef MAX
#define MAX(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (void)(&_a == &_b);                                                                        \
        _a > _b ? _a : _b;                                                                         \
    })
#endif

#ifndef MIN
#define MIN(a, b)                                                                                  \
    ({                                                                                             \
        typeof(a) _a = (a);                                                                        \
        typeof(b) _b = (b);                                                                        \
        (void)(&_a == &_b);                                                                        \
        _a < _b ? _a : _b;                                                                         \
    })
#endif
