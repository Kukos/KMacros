#ifndef KBUILTINS_IMPLEMENTATION_H
#define KBUILTINS_IMPLEMENTATION_H

/*
    This is the private header for the KMacros.

    This header constains my simple implementation of gcc and clang builtins

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kbuiltins-implementation.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "kprimitives.h"
#include "kcompiler-detect.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

/* Cannot implement it, so paste normal condition */
#define kbuiltin_expect_impl(cond, value) ((cond) == value)
#define kbuiltin_expect_with_probability_impl(cond, value, prob) kbuiltin_expect_impl(cond, value)

/* Cannot implement it, so paste normal terary operator */
#define kbuiltin_choose_expr_impl(expr, tstate, fstate) (expr ? tstate : fstate)

/* It can be implemented only a little, because we cannot get compiler error just only true / false */
#define kbuiltin_types_compatible_p_impl(type1, type2) (KPRIMITIVES_GET_ENUM_FROM_TYPE(type1) == KPRIMITIVES_GET_ENUM_FROM_TYPE(type2) && sizeof(type1) == sizeof(type2))

/* It cannot be implemented, assume that this is not const */
#define kbuiltin_constant_p_impl(expr) (0)

/* Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero. */
#define kbuiltin_ffs_impl(x)   __kffs(x)
#define kbuiltin_ffsl_impl(x)  __kffsl(x)
#define kbuiltin_ffsll_impl(x) __kffsll(x)

/* Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined. */
#define kbuiltin_clz_impl(x)   __kclz(x)
#define kbuiltin_clzl_impl(x)  __kclzl(x)
#define kbuiltin_clzll_impl(x) __kclzll(x)

/* Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined. */
#define kbuiltin_ctz_impl(x)   __kctz(x)
#define kbuiltin_ctzl_impl(x)  __kctzl(x)
#define kbuiltin_ctzll_impl(x) __kctzll(x)

/* Returns the number of leading redundant sign bits in x, i.e. the number of bits following the most significant bit that are identical to it. There are no special cases for 0 or other values. */
#define kbuiltin_clrsb_impl(x)   __kclrsb(x)
#define kbuiltin_clrsbl_impl(x)  __kclrsbl(x)
#define kbuiltin_clrsbll_impl(x) __kclrsbll(x)

/* Returns the number of 1-bits in x. */
#define kbuiltin_popcount_impl(x)   __kpopcount(x)
#define kbuiltin_popcountl_impl(x)  __kpopcountl(x)
#define kbuiltin_popcountll_impl(x) __kpopcountll(x)

/* Returns the parity of x, i.e. the number of 1-bits in x modulo 2. */
#define kbuiltin_parity_impl(x)   __kparity(x)
#define kbuiltin_parityl_impl(x)  __kparityl(x)
#define kbuiltin_parityll_impl(x) __kparityll(x)

/* Returns x with the order of the bytes reversed; for example, 0xaabb becomes 0xbbaa. Byte here always means exactly 8 bits. */
#define kbuiltin_bswap16_impl(x)  __kbswap16(x)
#define kbuiltin_bswap32_impl(x)  __kbswap32(x)
#define kbuiltin_bswap64_impl(x)  __kbswap64(x)

#define kbuiltin_add_overflow_impl(x, y, res)    kadd_overflow_generic(x, y, res)
#define kbuiltin_uadd_overflow_impl(x, y, res)   __kuadd_overflow(x, y, res)
#define kbuiltin_uaddl_overflow_impl(x, y, res)  __kuaddl_overflow(x, y, res)
#define kbuiltin_uaddll_overflow_impl(x, y, res) __kuaddll_overflow(x, y, res)
#define kbuiltin_sadd_overflow_impl(x, y, res)   __ksadd_overflow(x, y, res)
#define kbuiltin_saddl_overflow_impl(x, y, res)  __ksaddl_overflow(x, y, res)
#define kbuiltin_saddll_overflow_impl(x, y, res) __ksaddll_overflow(x, y, res)

#define kbuiltin_sub_overflow_impl(x, y, res)    ksub_overflow_generic(x, y, res)
#define kbuiltin_usub_overflow_impl(x, y, res)   __kusub_overflow(x, y, res)
#define kbuiltin_usubl_overflow_impl(x, y, res)  __kusubl_overflow(x, y, res)
#define kbuiltin_usubll_overflow_impl(x, y, res) __kusubll_overflow(x, y, res)
#define kbuiltin_ssub_overflow_impl(x, y, res)   __kssub_overflow(x, y, res)
#define kbuiltin_ssubl_overflow_impl(x, y, res)  __kssubl_overflow(x, y, res)
#define kbuiltin_ssubll_overflow_impl(x, y, res) __kssubll_overflow(x, y, res)

#define kbuiltin_mul_overflow_impl(x, y, res)    kmul_overflow_generic(x, y, res)
#define kbuiltin_umul_overflow_impl(x, y, res)   __kumul_overflow(x, y, res)
#define kbuiltin_umull_overflow_impl(x, y, res)  __kumull_overflow(x, y, res)
#define kbuiltin_umulll_overflow_impl(x, y, res) __kumulll_overflow(x, y, res)
#define kbuiltin_smul_overflow_impl(x, y, res)   __ksmul_overflow(x, y, res)
#define kbuiltin_smull_overflow_impl(x, y, res)  __ksmull_overflow(x, y, res)
#define kbuiltin_smulll_overflow_impl(x, y, res) __ksmulll_overflow(x, y, res)

static inline int __kffs(int x)
{
    if (x == 0)
        return 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if (x & (1 << pos))
            return pos + 1;

    return 0;
}

static inline int __kffsl(long x)
{
    if (x == 0)
        return 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if (x & (1l << pos))
            return pos + 1;

    return 0;
}

static inline int __kffsll(long long x)
{
    if (x == 0)
        return 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if (x & (1ll << pos))
            return pos + 1;

    return 0;
}

static inline int __kclz(unsigned int x)
{
    /* undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 1); pos > 0; --pos)
        if ((x & (1u << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kclzl(unsigned long x)
{
    /* undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 1); pos > 0; --pos)
        if ((x & (1ul << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kclzll(unsigned long long x)
{
    /* undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 1); pos > 0; --pos)
        if ((x & (1ull << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kctz(unsigned int x)
{
    /* Undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1u << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kctzl(unsigned long x)
{
    /* Undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1ul << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kctzll(unsigned long long x)
{
    /* Undefined */
    if (x == 0)
        return -1;

    int zeros = 0;
    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1ull << pos)) == 0)
            zeros++;
        else
            return zeros;

    return zeros;
}

static inline int __kclrsb(int x)
{
    const int sign_bit = x < 0;
    int lrsb = 0;

    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 2); pos >= 0; --pos)
        if (((x & (1 << pos)) >> pos) == sign_bit)
            ++lrsb;
        else
            return lrsb;

    return lrsb;
}

static inline int __kclrsbl(long x)
{
    const int sign_bit = x < 0;
    int lrsb = 0;

    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 2); pos >= 0; --pos)
        if (((x & (1l << pos)) >> pos) == sign_bit)
            ++lrsb;
        else
            return lrsb;

    return lrsb;
}

static inline int __kclrsbll(long long x)
{
    const int sign_bit = x < 0;
    int lrsb = 0;

    for (int pos = (int)((sizeof(x) * CHAR_BIT) - 2); pos >= 0; --pos)
        if (((x & (1ll << pos)) >> pos) == sign_bit)
            ++lrsb;
        else
            return lrsb;

    return lrsb;
}

static inline int __kpopcount(unsigned int x)
{
    int ones = 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1u << pos)))
            ones++;

    return ones;
}

static inline int __kpopcountl(unsigned long x)
{
    int ones = 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1ul << pos)))
            ones++;

    return ones;
}

static inline int __kpopcountll(unsigned long long x)
{
    int ones = 0;

    for (int pos = 0; pos < (int)(sizeof(x) * CHAR_BIT); ++pos)
        if ((x & (1ull << pos)))
            ones++;

    return ones;
}

static inline int __kparity(unsigned int x)
{
    return __kpopcount(x) % 2;
}

static inline int __kparityl(unsigned long x)
{
    return __kpopcountl(x) % 2;
}

static inline int __kparityll(unsigned long long x)
{
    return __kpopcountll(x) % 2;
}

static inline uint16_t __kbswap16(uint16_t x)
{
    return (uint16_t)((x & 0x00FF) << 8) | (uint16_t)((x & 0xFF00) >> 8);
}

static inline uint32_t __kbswap32(uint32_t x)
{
    return  (uint32_t)((x & 0x000000FF) << 24) |
            (uint32_t)((x & 0x0000FF00) <<  8) |
            (uint32_t)((x & 0x00FF0000) >>  8) |
            (uint32_t)((x & 0xFF000000) >> 24);
}

static inline uint64_t __kbswap64(uint64_t x)
{
    return (uint64_t)((x & 0x00000000000000FFULL) << 56) |
           (uint64_t)((x & 0x000000000000FF00ULL) << 40) |
           (uint64_t)((x & 0x0000000000FF0000ULL) << 24) |
           (uint64_t)((x & 0x00000000FF000000ULL) <<  8) |
           (uint64_t)((x & 0x000000FF00000000ULL) >>  8) |
           (uint64_t)((x & 0x0000FF0000000000ULL) >> 24) |
           (uint64_t)((x & 0x00FF000000000000ULL) >> 40) |
           (uint64_t)((x & 0xFF00000000000000ULL) >> 56);
}

#ifdef KCOMPILER_GNUC

#define kadd_overflow_generic(x, y, res) \
    __extension__ ({ \
        const __typeof__(x) __kbuiltint_x = (x); \
        const __typeof__(y) __kbuiltint_y = (y); \
        (void)(&__kbuiltint_x - &__kbuiltint_y); \
        (void)(&__kbuiltint_x - res); \
        _Generic((__kbuiltint_x), \
             int: __ksadd_overflow((int)__kbuiltint_x, (int)__kbuiltint_y, (void *)res), \
             unsigned int: __kuadd_overflow((unsigned int)__kbuiltint_x, (unsigned int)__kbuiltint_y, (void *)res), \
             long: __ksaddl_overflow((long)__kbuiltint_x, (long)__kbuiltint_y, (void *)res), \
             unsigned long: __kuaddl_overflow((unsigned long)__kbuiltint_x, (unsigned long)__kbuiltint_y, (void *)res), \
             long long: __ksaddll_overflow((long long)__kbuiltint_x, (long long)__kbuiltint_y, (void *)res), \
             unsigned long long: __kuaddll_overflow((unsigned long long)__kbuiltint_x, (unsigned long long)__kbuiltint_y, (void *)res) \
        ); \
    })

#define ksub_overflow_generic(x, y, res) \
    __extension__ ({ \
        const __typeof__(x) __kbuiltint_x = (x); \
        const __typeof__(y) __kbuiltint_y = (y); \
        (void)(&__kbuiltint_x - &__kbuiltint_y); \
        (void)(&__kbuiltint_x - res); \
        _Generic((__kbuiltint_x), \
             int: __kssub_overflow((int)__kbuiltint_x, (int)__kbuiltint_y, (void *)res), \
             unsigned int: __kusub_overflow((unsigned int)__kbuiltint_x, (unsigned int)__kbuiltint_y, (void *)res), \
             long: __kssubl_overflow((long)__kbuiltint_x, (long)__kbuiltint_y, (void *)res), \
             unsigned long: __kusubl_overflow((unsigned long)__kbuiltint_x, (unsigned long)__kbuiltint_y, (void *)res), \
             long long: __kssubll_overflow((long long)__kbuiltint_x, (long long)__kbuiltint_y, (void *)res), \
             unsigned long long: __kusubll_overflow((unsigned long long)__kbuiltint_x, (unsigned long long)__kbuiltint_y, (void *)res) \
        ); \
    })

#define kmul_overflow_generic(x, y, res) \
    __extension__ ({ \
        const __typeof__(x) __kbuiltint_x = (x); \
        const __typeof__(y) __kbuiltint_y = (y); \
        (void)(&__kbuiltint_x - &__kbuiltint_y); \
        (void)(&__kbuiltint_x - res); \
        _Generic((__kbuiltint_x), \
             int: __ksmul_overflow((int)__kbuiltint_x, (int)__kbuiltint_y, (void *)res), \
             unsigned int: __kumul_overflow((unsigned int)__kbuiltint_x, (unsigned int)__kbuiltint_y, (void *)res), \
             long: __ksmull_overflow((long)__kbuiltint_x, (long)__kbuiltint_y, (void *)res), \
             unsigned long: __kumull_overflow((unsigned long)__kbuiltint_x, (unsigned long)__kbuiltint_y, (void *)res), \
             long long: __ksmulll_overflow((long long)__kbuiltint_x, (long long)__kbuiltint_y, (void *)res), \
             unsigned long long: __kumulll_overflow((unsigned long long)__kbuiltint_x, (unsigned long long)__kbuiltint_y, (void *)res) \
        ); \
    })

#else

#define kadd_overflow_generic(x, y, res) \
    _Generic((x), \
             int: __ksadd_overflow((int)x, (int)y, (void *)res), \
             unsigned int: __kuadd_overflow((unsigned int)x, (unsigned int)y, (void *)res), \
             long: __ksaddl_overflow((long)x, (long)y, (void *)res), \
             unsigned long: __kuaddl_overflow((unsigned long)x, (unsigned long)y, (void *)res), \
             long long: __ksaddll_overflow((long long)x, (long long)y, (void *)res), \
             unsigned long long: __kuaddll_overflow((unsigned long long)x, (unsigned long long)y, (void *)res) \
        )

#define ksub_overflow_generic(x, y, res) \
    _Generic((x), \
             int: __kssub_overflow((int)x, (int)y, (void *)res), \
             unsigned int: __kusub_overflow((unsigned int)x, (unsigned int)y, (void *)res), \
             long: __kssubl_overflow((long)x, (long)y, (void *)res), \
             unsigned long: __kusubl_overflow((unsigned long)x, (unsigned long)y, (void *)res), \
             long long: __kssubll_overflow((long long)x, (long long)y, (void *)res), \
             unsigned long long: __kusubll_overflow((unsigned long long)x, (unsigned long long)y, (void *)res) \
        )

#define kmul_overflow_generic(x, y, res) \
    _Generic((x), \
             int: __ksmul_overflow((int)x, (int)y, (void *)res), \
             unsigned int: __kumul_overflow((unsigned int)x, (unsigned int)y, (void *)res), \
             long: __ksmull_overflow((long)x, (long)y, (void *)res), \
             unsigned long: __kumull_overflow((unsigned long)x, (unsigned long)y, (void *)res), \
             long long: __ksmulll_overflow((long long)x, (long long)y, (void *)res), \
             unsigned long long: __kumulll_overflow((unsigned long long)x, (unsigned long long)y, (void *)res) \
        )

#endif

static inline bool __kuadd_overflow(unsigned int x, unsigned int y, unsigned int* res)
{
    *res = x + y;

    return (x > UINT_MAX - y);
}

static inline bool __kuaddl_overflow(unsigned long x, unsigned long y, unsigned long* res)
{
    *res = x + y;

    return (x > ULONG_MAX - y);
}

static inline bool __kuaddll_overflow(unsigned long long x, unsigned long long y, unsigned long long* res)
{
    *res = x + y;

    return (x > ULLONG_MAX - y);
}

static inline bool __ksadd_overflow(int x, int y, int* res)
{
    *res = x + y;

    return (y > 0 && (x > INT_MAX - y)) || (y < 0 && (x < INT_MIN - y));
}

static inline bool __ksaddl_overflow(long x, long y, long* res)
{
    *res = x + y;

    return (y > 0 && (x > LONG_MAX - y)) || (y < 0 && (x < LONG_MIN - y));
}

static inline bool __ksaddll_overflow(long long x, long long y, long long* res)
{
    *res = x + y;

    return (y > 0 && (x > LLONG_MAX - y)) || (y < 0 && (x < LLONG_MIN - y));
}

static inline bool __kusub_overflow(unsigned int x, unsigned int y, unsigned int* res)
{
    *res = x - y;

    return x < y;
}

static inline bool __kusubl_overflow(unsigned long x, unsigned long y, unsigned long* res)
{
    *res = x - y;

    return x < y;
}

static inline bool __kusubll_overflow(unsigned long long x, unsigned long long y, unsigned long long* res)
{
    *res = x - y;

    return x < y;
}

static inline bool __kssub_overflow(int x, int y, int* res)
{
    *res = x - y;

    return (y > 0 && (x < INT_MIN + y)) || (y < 0 && (x > INT_MAX + y));
}

static inline bool __kssubl_overflow(long x, long y, long* res)
{
    *res = x - y;

    return (y > 0 && (x < LONG_MIN + y)) || (y < 0 && (x > LONG_MAX + y));
}

static inline bool __kssubll_overflow(long long x, long long y, long long* res)
{
    *res = x - y;

    return (y > 0 && (x < LLONG_MIN + y)) || (y < 0 && (x > LLONG_MAX + y));
}

static inline bool __kumul_overflow(unsigned int x, unsigned int y, unsigned int* res)
{
    *res = x * y;
    return x > UINT_MAX / y;
}

static inline bool __kumull_overflow(unsigned long x, unsigned long y, unsigned long* res)
{
    *res = x * y;
    return x > ULONG_MAX / y;
}

static inline bool __kumulll_overflow(unsigned long long x, unsigned long long y, unsigned long long* res)
{
    *res = x * y;
    return x > ULLONG_MAX / y;
}

static inline bool __ksmul_overflow(int x, int y, int* res)
{
    *res = x * y;
    return  (x == -1 && y == INT_MIN) ||
            (y == -1 && x == INT_MIN) ||
            (x > INT_MAX / y) ||
            (x < INT_MIN / y);
}

static inline bool __ksmull_overflow(long x, long y, long* res)
{
    *res = x * y;
    return  (x == -1 && y == LONG_MIN) ||
            (y == -1 && x == LONG_MIN) ||
            (x > LONG_MAX / y) ||
            (x < LONG_MIN / y);
}

static inline bool __ksmulll_overflow(long long x, long long y, long long* res)
{
    *res = x * y;
    return  (x == -1 && y == LLONG_MIN) ||
            (y == -1 && x == LLONG_MIN) ||
            (x > LLONG_MAX / y) ||
            (x < LLONG_MIN / y);
}

#endif
