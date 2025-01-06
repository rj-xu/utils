#pragma once

// NOLINTBEGIN(bugprone-reserved-identifier, readability-identifier-naming)

// __attribute__((attr...))
// [[gnu::attr]]
// [[attr...]]

#ifndef __ASM
#define __ASM __asm__
#endif

#ifndef __FORCE_INLINE
#define __FORCE_INLINE __attribute__((always_inline)) inline
#endif
#ifndef __STATIC_FORCE_INLINE
#define __STATIC_FORCE_INLINE __attribute__((always_inline)) static inline
#endif

#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((noreturn))
#endif
#ifndef __DEPRECATED
#define __DEPRECATED __attribute__((deprecated))
#endif

#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __UNUSED
#define __UNUSED __attribute__((unused))
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
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif

#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif
#ifndef __COMPILER_BARRIER
#define __COMPILER_BARRIER() __ASM volatile("" :: : "memory")
#endif
#ifndef __NO_INIT
#define __NO_INIT __attribute__((section(".noinit")))
#endif
#ifndef __ALIAS
#define __ALIAS(x) __attribute__((alias(x)))
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

#ifndef __CLEANUP
#define __CLEANUP(Func) __attribute__((cleanup(Func)))
#endif

/**
  \brief   No Operation
  \details No Operation does nothing. This instruction can be used for code alignment purposes.
 */
#ifndef __NOP
#define __NOP() __ASM volatile("nop")
#endif

/**
  \brief   Wait For Interrupt
  \details Wait For Interrupt is a hint instruction that suspends execution until one of a number of
  events occurs.
 */
#ifndef __WFI
#define __WFI() __ASM volatile("wfi" :: : "memory")
#endif

/**
  \brief   Wait For Event
  \details Wait For Event is a hint instruction that permits the processor to enter
           a low-power state until one of a number of events occurs.
 */
#ifndef __WFE
#define __WFE() __ASM volatile("wfe" :: : "memory")
#endif

/**
  \brief   Send Event
  \details Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
#ifndef __SEV
#define __SEV() __ASM volatile("sev")
#endif

#if 0
/**
  \brief   Instruction Synchronization Barrier
  \details Instruction Synchronization Barrier flushes the pipeline in the processor,
           so that all instructions following the ISB are fetched from cache or memory,
           after the instruction has been completed.
 */
__STATIC_FORCEINLINE void __ISB(void)
{
    __ASM volatile("isb 0xF" :: : "memory");
}

/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
__STATIC_FORCEINLINE void __DSB(void)
{
    __ASM volatile("dsb 0xF" :: : "memory");
}

/**
  \brief   Data Memory Barrier
  \details Ensures the apparent order of the explicit memory operations before
           and after the instruction, without ensuring their completion.
 */
__STATIC_FORCEINLINE void __DMB(void)
{
    __ASM volatile("dmb 0xF" :: : "memory");
}

/**
  \brief   Reverse byte order (32 bit)
  \details Reverses the byte order in unsigned integer value. For example, 0x12345678 becomes
  0x78563412.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV(uint32_t value)
{
    return __builtin_bswap32(value);
}

/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order within each halfword of a word. For example, 0x12345678 becomes
  0x34127856.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __REV16(uint32_t value)
{
    uint32_t result;

    __ASM("rev16 %0, %1" : __CMSIS_GCC_OUT_REG(result) : __CMSIS_GCC_USE_REG(value));
    return (result);
}

/**
  \brief   Reverse byte order (16 bit)
  \details Reverses the byte order in a 16-bit value and returns the signed 16-bit result. For
  example, 0x0080 becomes 0x8000.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE int16_t __REVSH(int16_t value)
{
    return (int16_t)__builtin_bswap16(value);
}

/**
  \brief   Rotate Right in unsigned value (32 bit)
  \details Rotate Right (immediate) provides the value of the contents of a register rotated by a
  variable number of bits.
  \param [in]    op1  Value to rotate
  \param [in]    op2  Number of Bits to rotate
  \return               Rotated value
 */
__STATIC_FORCEINLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
    op2 %= 32U;
    if (op2 == 0U)
    {
        return op1;
    }
    return (op1 >> op2) | (op1 << (32U - op2));
}

/**
  \brief   Breakpoint
  \details Causes the processor to enter Debug state.
           Debug tools can use this to investigate system state when the instruction at a particular
  address is reached.
  \param [in]    value  is ignored by the processor.
                 If required, a debugger can use it to store additional information about the
  breakpoint.
 */
#define __BKPT(value) __ASM volatile("bkpt " #value)

/**
  \brief   Reverse bit order of value
  \details Reverses the bit order of the given value.
  \param [in]    value  Value to reverse
  \return               Reversed value
 */
__STATIC_FORCEINLINE uint32_t __RBIT(uint32_t value)
{
    uint32_t result;

    uint32_t s = (4U /*sizeof(v)*/ * 8U) - 1U; /* extra shift needed at end */

    result = value; /* r will be reversed bits of v; first get LSB of v */
    for (value >>= 1U; value != 0U; value >>= 1U)
    {
        result <<= 1U;
        result |= value & 1U;
        s--;
    }
    result <<= s; /* shift when v's highest bits are zero */

    return (result);
}

/**
  \brief   Count leading zeros
  \details Counts the number of leading zeros of a data value.
  \param [in]  value  Value to count the leading zeros
  \return             number of leading zeros in value
 */
__STATIC_FORCEINLINE uint8_t __CLZ(uint32_t value)
{
    /* Even though __builtin_clz produces a CLZ instruction on ARM, formally
       __builtin_clz(0) is undefined behaviour, so handle this case specially.
       This guarantees ARM-compatible results if happening to compile on a non-ARM
       target, and ensures the compiler doesn't decide to activate any
       optimisations using the logic "value was passed to __builtin_clz, so it
       is non-zero".
       ARM GCC 7.3 and possibly earlier will optimise this test away, leaving a
       single CLZ instruction.
     */
    if (value == 0U)
    {
        return 32U;
    }
    return __builtin_clz(value);
}
#endif

// NOLINTEND(bugprone-reserved-identifier, readability-identifier-naming)
