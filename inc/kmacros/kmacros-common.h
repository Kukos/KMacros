#ifndef KMACROS_COMMON_H
#define KMACROS_COMMON_H

/*
    This is the private header for the KMacros.

    This file contains macros which dont need gnu c to be better

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kmacros-gnuc.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include <stdlib.h> /* free */
#include <stddef.h>
#include <stdint.h>
#include <string.h> /* memcpy */

#include "kmacros-common-implementation.h"
#include "kcompiler.h"
#include "kpreprocessor.h"

/**
 * Create static assertion (assertion for compile time expression) with pretty message
 */
#define KSTATIC_ASSERT_MSG(cond, msg) _Static_assert(cond, __FILE__  ":" KTOSTRING(__LINE__) " " msg)

/**
 * Create static assertion (assertion for compile time expression) with default message
 */
#define KSTATIC_ASSERT(cond) KSTATIC_ASSERT_MSG(cond, "KStatic assert failed")

/**
 * Return len of array if and only if when array is a compile time array (not pointer)
 */
#define KARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

/**
 * Deallocate memory in normal way (using free) + set pointer to NULL to avoid dangling pointer issue
 */
#define KFREE(ptr) \
    do { \
        free(ptr); \
        ptr = NULL; \
    } while (0)

/**
 * Some functions like scanf requires using retval. This macro is faking using return value for you.
 */
#define KUNUSED_RETVAL(func) \
    do { \
        if (func) \
        { \
            \
        } \
        else \
        { \
            \
        } \
    } while (0)

/**
 * In c every none 0 value is true (not only 1).
 * This macro map any values to true / false domain
 */
#define KCAST_TO_BOOL(val) (!!(val))

/**
 * Use this macro to inform compiler that cond will be moslty evaluates to true
 * This is only for performance speedup (pipeline).
 * Nothing wrong happend (except little slow down) when cond will be false
 */
#define KLIKELY(cond) KEXPECT(cond, 1)

/**
 * Use this macro to inform compiler that cond will be moslty evaluates to false
 * This is only for performance speedup (pipeline).
 * Nothing wrong happend (except little slow down) when cond will be true
 */
#define KUNLIKELY(cond) KEXPECT(cond, 0)

/**
 * Create alomost unique name from prefix using __LINE__ as a unique key
 */
#define KVAR_ALMOST_UNIQUE_NAME(prefix) KCONCAT(prefix, __LINE__)

/**
 * This macro allows you to go up in structures.
 * In C we are using . and -> to go down in structure hierarchy
 * But if structure is a member (not pointer to strucutre).
 * You can use this macro to go upper
 *
 * @param[in] ptr - pointer (address) of struct member from base struct
 * @param[in] type - type of base struct
 * @param[in] member - name of member struct in base struct
 *
 * Example:
 *
 * struct Member
 * {
 *     int a;
 *     int b;
 * };
 *
 * struct Base
 * {
 *     int a;
 *     struct Member b;
 *     int c;
 * };
 * struct Base base = {.a = 10, .b = {.a = 100, .b = 200}, .c = 30};
 * struct Member* member_ptr = &base.b;
 * struct Base* base_ptr = KCONTAINER_OF(member_ptr, struct Base, b);
 */
#define KCONTAINER_OF(ptr, type, member) (void *)((char *)ptr - offsetof(type, member))

/**
 * This macro calls printf with your params (fmt and ...) but add by itself some pretty info
 * like __FILE__, __func__ and __LINE__
 */
#define KPRINT_PRETTY(...) KPRINT_PRETTY_PRIV(KPRINT_PRETTY_PRIV_HEAD(__VA_ARGS__), KPRINT_PRETTY_PRIV_TAIL(__VA_ARGS__))

/**
 * This macro works as memcpy.
 * But it is better (faster) for little primitive types.
 * I.e for integer it will be 3x faster than normal memcpy
 */
#define KWRITE_SIZE_PTR(dst, src, size) \
    do{ \
        KCOMPILER_DIAG_PUSH() \
        KCOMPILER_DIAG_IGNORE("-Wstrict-aliasing") \
        KCOMPILER_DIAG_IGNORE("-Wcast-align") \
        switch (size) \
        { \
            case 1: *(uint8_t *)dst  = *(uint8_t *)src; break; \
            case 2: *(uint16_t *)dst = *(uint16_t *)src; break; \
            case 4: *(uint32_t *)dst = *(uint32_t *)src; break; \
            case 8: *(uint64_t *)dst = *(uint64_t *)src; break; \
            default: (void)memcpy(dst, src, (size_t)(size)); \
        } \
        KCOMPILER_DIAG_POP() \
    } while (0)

/**
 * Works in the same way that KWRITE_SIZE_PTR
 * But it works on variables (not pointers)
 */
#define KWRITE_SIZE_VAR(dst, src, size) KWRITE_SIZE_PTR(&dst, &src, size)

/**
 * Works as KWRITE_SIZE_PTR
 * But it is deducting size from dst pointer type
 */
#define KWRITE_PTR(dst, src) KWRITE_SIZE_PTR(dst, src, sizeof(*dst))

/**
 * Works as KWRITE_SIZE_VAR
 * But it is deducting size from dst variable type
 */
#define KWRITE_VAR(dst, src) KWRITE_SIZE_VAR(dst, src, sizeof(dst))

/**
 * This is only an alias to KWRITE_VAR
 */
#define KWRITE(dst, src) KWRITE_VAR(dst, src)

/**
 * SWAPS values of variables a and b
 * So if you pass pointers then KSWAP will swap pointer values not variables point by pointers
 *
 * KSWAP works only if a and b have the same type
 */
#define KSWAP(a, b) KSWAP_PRIV(a, b, KVAR_ALMOST_UNIQUE_NAME(KCONCAT(a, b)))

/**
 * Check if n is power of 2
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KIS_POWER2(n) KIS_POWER2_TYPE(n)

/**
 * Calculate floor(log2(n)) but without coprocessor
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KLOG2_FLOOR(n) KLOG2_FLOOR_TYPE(n)

/**
 * Calculate ceil(log2(n)) but without coprocessor
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KLOG2_CEIL(n) KLOG2_CEIL_TYPE(n)

/**
 * This is only an alias to KLOG2_FLOOR
 */
#define KLOG2(n) KLOG2_FLOOR(n)

/**
 * Find first power of 2 >= than n
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KROUND_POWER2_UP(n) KROUND_POWER2_UP_TYPE(n)

/**
 * Find first power of 2 <= than n
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KROUND_POWER2_DOWN(n) KROUND_POWER2_DOWN_TYPE(n)

/**
 * Allign n to power of 2.
 * So it returns first power of 2 >= than n
 *
 * Works for:
 * unsigned int
 * unsigned long
 * unsigned long long
 */
#define KALLIGN_POWER2(n) KROUND_POWER2_UP(n)

#endif
