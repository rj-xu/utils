#pragma once

#include <stddef.h>

// #define OFFSETOF(type, member) ((size_t) &((type *)0)->member)
// #define OFFSETOF(type, member) __builtin_offsetof(type, member)
#define OFFSETOF(type, member) offsetof(type, member) // Use offsetof() instead

#define SIZEOF_MEMBER(T, m) sizeof(((T *)0)->m)
#define TYPEOF_MEMBER(T, m) typeof(((T *)0)->m)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 * WARNING: any const qualifier of @ptr is lost.
 */
#define CONTAINER_OF(ptr, type, member)                                                            \
    ({                                                                                             \
        void *__mptr = (void *)(ptr);                                                              \
        static_assert(__same_type(*(ptr), ((type *)0)->member) || __same_type(*(ptr), void),       \
                      "pointer type mismatch in container_of()");                                  \
        ((type *)(__mptr - offsetof(type, member)));                                               \
    })

/**
 * container_of_const - cast a member of a structure out to the containing
 *			structure and preserve the const-ness of the pointer
 * @ptr:		the pointer to the member
 * @type:		the type of the container struct this is embedded in.
 * @member:		the name of the member within the struct.
 */
#define CONTAINER_OF_CONST(ptr, type, member)                                                      \
    _Generic(ptr,                                                                                  \
        const typeof(*(ptr)) *: ((const type *)container_of(ptr, type, member)),                   \
        default: ((type *)container_of(ptr, type, member)))
