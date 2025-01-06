#include "args.h"
#include "concat.h"
#include "for_each.h"
#include "log.h"
#include "operator.h"

#define ENUM_CLASS(args...)                                                                      \
    typedef struct                                                                                 \
    {                                                                                              \
        enum                                                                                       \
        {                                                                                          \
            args                                                                                   \
        } val;                                                                                     \
    }

#define _ENUM_STR(e)                                                                               \
    case e:                                                                                        \
        return STRINGIZE(e)
#define ENUM_STR(Name, args...)                                                                    \
    static inline str_t Name##Str(Name##_t e)                                                      \
    {                                                                                              \
        switch (e)                                                                                 \
        {                                                                                          \
            FOR_EACH_SEMI(_ENUM_STR, args);                                                        \
        default:                                                                                   \
            return "Unknown Enum";                                                                 \
        }                                                                                          \
    }

#define _ENUM_LIST(Name, start, first, args...)                                                    \
    typedef enum                                                                                   \
    {                                                                                              \
        first = (start),                                                                           \
        args,                                                                                      \
        Name##_END,                                                                                \
        Name##_NUM = Name##_END - (start),                                                         \
    } Name##_t;                                                                                    \
    ENUM_STR(Name, first, args)
#define ENUM_LIST(Name, start, args...) _ENUM_LIST(Name, start, args)

#define ENUM_LIST_ALT(Name, args...)                                                               \
    typedef enum                                                                                   \
    {                                                                                              \
        args,                                                                                      \
        Name##_NUM,                                                                                \
    } Name##_t;                                                                                    \
    const str_t Name##Str[] = {FOR_EACH_COMMA(STRINGIZE, args)}

#define ERROR_LIST(Name, start, args...)                                                           \
    ENUM_LIST(Name, start, args)                                                                   \
    static inline void Log##Name(uint32_t err)                                                     \
    {                                                                                              \
        LOG_VAL(ERROR, err);                                                                       \
        for (int i = (start); i < Name##_END; i++)                                                 \
        {                                                                                          \
            if (err & (1 << i))                                                                    \
            {                                                                                      \
                LOG_ERROR("ERROR: %s", Name##Str(i));                                              \
            }                                                                                      \
        }                                                                                          \
    }

#define STATUS_LIST(Name, start, args...)                                                          \
    ENUM_LIST(Name, start, args)                                                                   \
    static inline void Log##Name(uint32_t stat)                                                    \
    {                                                                                              \
        LOG_VAL(DEBUG, stat);                                                                      \
        for (int i = (start); i < Name##_END; i++)                                                 \
        {                                                                                          \
            if (stat & (1 << i))                                                                   \
            {                                                                                      \
                LOG_DEBUG("STATUS: %s", Name##Str(i));                                             \
            }                                                                                      \
        }                                                                                          \
    }
