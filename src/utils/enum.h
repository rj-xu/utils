#include "args.h"
#include "concat.h"
#include "for_each.h"
#include "operator.h"

#define TYPEDEF_ENUM_LIST(EnumName, args...)                                                       \
    typedef enum                                                                                   \
    {                                                                                              \
        args,                                                                                      \
        _##EnumName##_MAX                                                                          \
    } EnumName##_t;                                                                                \
                                                                                                   \
    str_t EnumName##List[] = {FOR_EACH_ALT(STRINGIZE, args)}
