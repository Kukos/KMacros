#ifndef KMACROS_COMMON_IMPLEMENTATION_H
#define KMACROS_COMMON_IMPLEMENTATION_H

#include <limits.h>
#include <stdio.h>

#include "kcompiler.h"
#include "kpreprocessor.h"

#define KPRINT_PRETTY_PRIV_HEAD_HELPER(X, ...) X
#define KPRINT_PRETTY_PRIV_HEAD(...) KPRINT_PRETTY_PRIV_HEAD_HELPER(__VA_ARGS__, "")

#define KPRINT_PRETTY_PRIV_TAIL_HELPER(X, ...) __VA_ARGS__
#define KPRINT_PRETTY_PRIV_TAIL(...) KPRINT_PRETTY_PRIV_TAIL_HELPER(__VA_ARGS__, "")

#define KPRINT_PRETTY_PRIV(fmt, ...) printf("%s:%s.%d " fmt "%s", __FILE__, __func__, __LINE__, __VA_ARGS__)

#define KSWAP_PRIV(a, b, var) \
    do { \
        (void)(&a - &b); \
        char var[sizeof(a)]; \
        KWRITE_VAR(var, a); \
        KWRITE_VAR(a, b); \
        KWRITE_VAR(b, var); \
    } while(0)

static inline bool kis_power2_uint(unsigned int n);
static inline bool kis_power2_ulong(unsigned long n);
static inline bool kis_power2_ulonglong(unsigned long long n);

static inline int klog2_ceil_uint(unsigned int n);
static inline long klog2_ceil_ulong(unsigned long n);
static inline long long klog2_ceil_ulonglong(unsigned long long n);

static inline int klog2_floor_uint(unsigned int n);
static inline long klog2_floor_ulong(unsigned long n);
static inline long long klog2_floor_ulonglong(unsigned long long n);

static inline unsigned int kround_power2_up_uint(unsigned int n);
static inline unsigned long kround_power2_up_ulong(unsigned long n);
static inline unsigned long long kround_power2_up_ulonglong(unsigned long long n);

static inline unsigned int kround_power2_down_uint(unsigned int n);
static inline unsigned long kround_power2_down_ulong(unsigned long n);
static inline unsigned long long kround_power2_down_ulonglong(unsigned long long n);

static inline bool kis_power2_uint(unsigned int n)
{
    return KPOPCOUNT(n) == 1;
}

static inline bool kis_power2_ulong(unsigned long n)
{
    return KPOPCOUNTL(n) == 1;
}

static inline bool kis_power2_ulonglong(unsigned long long n)
{
    return KPOPCOUNTLL(n) == 1;
}

static inline int klog2_ceil_uint(unsigned int n)
{
    return n == 0? -1 : klog2_floor_uint(n) + !kis_power2_uint(n);
}

static inline long klog2_ceil_ulong(unsigned long n)
{
    return n == 0? -1 : klog2_floor_ulong(n) + !kis_power2_ulong(n);
}

static inline long long klog2_ceil_ulonglong(unsigned long long n)
{
    return n == 0? -1 : klog2_floor_ulonglong(n) + !kis_power2_ulonglong(n);
}

static inline int klog2_floor_uint(unsigned int n)
{
    return n == 0? -1 : (int)sizeof(n) * CHAR_BIT - 1 - KCLZ(n);
}

static inline long klog2_floor_ulong(unsigned long n)
{
    return n == 0? -1 : (int)sizeof(n) * CHAR_BIT - 1 - KCLZL(n);
}

static inline long long klog2_floor_ulonglong(unsigned long long n)
{
    return n == 0? -1 : (int)sizeof(n) * CHAR_BIT - 1 - KCLZLL(n);
}

static inline unsigned int kround_power2_up_uint(unsigned int n)
{
    return n == 0? 0 : 1u << klog2_ceil_uint(n);
}

static inline unsigned long kround_power2_up_ulong(unsigned long n)
{
    return n == 0? 0 : 1ul << klog2_ceil_ulong(n);
}

static inline unsigned long long kround_power2_up_ulonglong(unsigned long long n)
{
    return n == 0? 0 : 1ull << klog2_ceil_ulonglong(n);
}

static inline unsigned int kround_power2_down_uint(unsigned int n)
{
    return n == 0? 0 : 1u << klog2_floor_uint(n);
}

static inline unsigned long kround_power2_down_ulong(unsigned long n)
{
    return n == 0? 0 : 1ul << klog2_floor_ulong(n);
}

static inline unsigned long long kround_power2_down_ulonglong(unsigned long long n)
{
    return n == 0? 0 : 1ull << klog2_floor_ulonglong(n);
}

#define KIS_POWER2_TYPE(n) \
    _Generic((n), \
        unsigned int:       kis_power2_uint((unsigned int)n), \
        unsigned long:      kis_power2_ulong((unsigned long)n), \
        unsigned long long: kis_power2_ulonglong((unsigned long long)n) \
    )

#define KLOG2_FLOOR_TYPE(n) \
    _Generic((n), \
        unsigned int:       klog2_floor_uint((unsigned int)n), \
        unsigned long:      klog2_floor_ulong((unsigned long)n), \
        unsigned long long: klog2_floor_ulonglong((unsigned long long)n) \
    )

#define KLOG2_CEIL_TYPE(n) \
    _Generic((n), \
        unsigned int:       klog2_ceil_uint((unsigned int)n), \
        unsigned long:      klog2_ceil_ulong((unsigned long)n), \
        unsigned long long: klog2_ceil_ulonglong((unsigned long long)n) \
    )

#define KROUND_POWER2_UP_TYPE(n) \
    _Generic((n), \
        unsigned int:       kround_power2_up_uint((unsigned int)n), \
        unsigned long:      kround_power2_up_ulong((unsigned long)n), \
        unsigned long long: kround_power2_up_ulonglong((unsigned long long)n) \
    )

#define KROUND_POWER2_DOWN_TYPE(n) \
    _Generic((n), \
        unsigned int:       kround_power2_down_uint((unsigned int)n), \
        unsigned long:      kround_power2_down_ulong((unsigned long)n), \
        unsigned long long: kround_power2_down_ulonglong((unsigned long long)n) \
    )

#endif
