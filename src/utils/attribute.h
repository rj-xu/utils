#pragma once

// NOLINTBEGIN(bugprone-reserved-identifier, readability-identifier-naming)

#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __FORCE_INLINE
#define __FORCE_INLINE __attribute__((always_inline)) inline
#endif
#ifndef __STATIC_FORCE_INLINE
#define __STATIC_FORCE_INLINE __attribute__((always_inline)) static inline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((__noreturn__))
#endif
#ifndef __DEPRECATED
#define __DEPRECATED __attribute__((deprecated))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif

#ifndef __RO
#define __RO volatile const
#endif
#ifndef __WO
#define __WO volatile
#endif
#ifndef __RW
#define __RW volatile
#endif

#ifndef __HOT
#define __HOT __attribute__((hot))
#endif
#ifndef __COLD
#define __COLD __attribute__((cold))
#endif
#ifndef __UNUSED
#define __UNUSED __attribute__((unused))
#endif

// NOLINTEND(bugprone-reserved-identifier, readability-identifier-naming)
