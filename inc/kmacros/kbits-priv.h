#ifndef KBITS_PRIV_H
#define KBITS_PRIV_H

/*
    This is the private header for the Kbits.

    This header constains all macros connected with bits (except builtins)

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kbits-priv.h> directly, use <kmacros/kbits.h> instead."
#endif

#include <stddef.h>
#include <limits.h>

#include "kcompiler-detect.h"
#include "kcompiler.h"

#define KMASK_PRIV(s, e, type)           ((type)(((1ull << ((e) - (s) + 1)) - 1) << (s)))
#define KMASK_PRIV_GET(n, s, e, type)    ((type)(((n) & (KMASK_PRIV(s, e, type))) >> s))
#define KMASK_PRIV_SET(n, s, e, type)    ((type)((n) | (KMASK_PRIV(s, e, type))))
#define KMASK_PRIV_CLEAR(n, s, e, type)  ((type)((n) & ~(KMASK_PRIV(s, e, type))))
#define KMASK_PRIV_TOGGLE(n, s, e, type) ((type)((n) ^ (KMASK_PRIV(s, e, type))))

#ifdef KCOMPILER_GNUC

#define KMASK_PRIV_TYPE(s, e)           KMASK_PRIV(s, e, unsigned long long)
#define KMASK_PRIV_TYPE_GET(n, s, e)    KMASK_PRIV_GET(n, s, e, __typeof__(n))
#define KMASK_PRIV_TYPE_SET(n, s, e)    KMASK_PRIV_SET(n, s, e, __typeof__(n))
#define KMASK_PRIV_TYPE_CLEAR(n, s, e)  KMASK_PRIV_CLEAR(n, s, e, __typeof__(n))
#define KMASK_PRIV_TYPE_TOGGLE(n, s, e) KMASK_PRIV_TOGGLE(n, s, e, __typeof__(n))

#else /* #ifdef KCOMPILER_GNUC */

#define KMASK_PRIV_TYPE(s, e)           KMASK_PRIV(s, e, unsigned long long)

#define KMASK_PRIV_CREATE_FUNCTION_TYPE(name, type, func_suffix) \
static inline type __kmask_priv_function_type_ ## name ## _ ## func_suffix(type n, unsigned s, unsigned e); \
static inline type __kmask_priv_function_type_ ## name ## _ ## func_suffix(type n, unsigned s, unsigned e) \
{ \
    return KMASK_PRIV_ ## name(n, s, e, type); \
}

KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, char, char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, signed char, signed_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, unsigned char, unsigned_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, short, short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, unsigned short, unsigned_short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, int, int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, unsigned int, unsigned_int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, long, long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, unsigned long, unsigned_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, long long, long_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(GET, unsigned long long, unsigned_long_long)


#define KMASK_PRIV_TYPE_GET(n, s, e) \
    _Generic((n), \
        char:               __kmask_priv_function_type_GET_char((char)n, s, e), \
        signed char:        __kmask_priv_function_type_GET_signed_char((signed char)n, s, e), \
        unsigned char:      __kmask_priv_function_type_GET_unsigned_char((unsigned char)n, s, e), \
        short:              __kmask_priv_function_type_GET_short((short)n, s, e), \
        unsigned short:     __kmask_priv_function_type_GET_unsigned_short((unsigned short)n, s, e), \
        int:                __kmask_priv_function_type_GET_int((int)n, s, e), \
        unsigned int:       __kmask_priv_function_type_GET_unsigned_int((unsigned int)n, s, e), \
        long:               __kmask_priv_function_type_GET_long((long)n, s, e), \
        unsigned long:      __kmask_priv_function_type_GET_unsigned_long((unsigned long)n, s, e), \
        long long:          __kmask_priv_function_type_GET_long_long((long long)n, s, e), \
        unsigned long long: __kmask_priv_function_type_GET_unsigned_long_long((unsigned long long)n, s, e) \
    )


KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, char, char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, signed char, signed_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, unsigned char, unsigned_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, short, short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, unsigned short, unsigned_short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, int, int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, unsigned int, unsigned_int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, long, long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, unsigned long, unsigned_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, long long, long_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(SET, unsigned long long, unsigned_long_long)


#define KMASK_PRIV_TYPE_SET(n, s, e) \
    _Generic((n), \
        char:               __kmask_priv_function_type_SET_char((char)n, s, e), \
        signed char:        __kmask_priv_function_type_SET_signed_char((signed char)n, s, e), \
        unsigned char:      __kmask_priv_function_type_SET_unsigned_char((unsigned char)n, s, e), \
        short:              __kmask_priv_function_type_SET_short((short)n, s, e), \
        unsigned short:     __kmask_priv_function_type_SET_unsigned_short((unsigned short)n, s, e), \
        int:                __kmask_priv_function_type_SET_int((int)n, s, e), \
        unsigned int:       __kmask_priv_function_type_SET_unsigned_int((unsigned int)n, s, e), \
        long:               __kmask_priv_function_type_SET_long((long)n, s, e), \
        unsigned long:      __kmask_priv_function_type_SET_unsigned_long((unsigned long)n, s, e), \
        long long:          __kmask_priv_function_type_SET_long_long((long long)n, s, e), \
        unsigned long long: __kmask_priv_function_type_SET_unsigned_long_long((unsigned long long)n, s, e) \
    )

KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, char, char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, signed char, signed_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, unsigned char, unsigned_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, short, short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, unsigned short, unsigned_short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, int, int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, unsigned int, unsigned_int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, long, long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, unsigned long, unsigned_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, long long, long_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(CLEAR, unsigned long long, unsigned_long_long)


#define KMASK_PRIV_TYPE_CLEAR(n, s, e) \
    _Generic((n), \
        char:               __kmask_priv_function_type_CLEAR_char((char)n, s, e), \
        signed char:        __kmask_priv_function_type_CLEAR_signed_char((signed char)n, s, e), \
        unsigned char:      __kmask_priv_function_type_CLEAR_unsigned_char((unsigned char)n, s, e), \
        short:              __kmask_priv_function_type_CLEAR_short((short)n, s, e), \
        unsigned short:     __kmask_priv_function_type_CLEAR_unsigned_short((unsigned short)n, s, e), \
        int:                __kmask_priv_function_type_CLEAR_int((int)n, s, e), \
        unsigned int:       __kmask_priv_function_type_CLEAR_unsigned_int((unsigned int)n, s, e), \
        long:               __kmask_priv_function_type_CLEAR_long((long)n, s, e), \
        unsigned long:      __kmask_priv_function_type_CLEAR_unsigned_long((unsigned long)n, s, e), \
        long long:          __kmask_priv_function_type_CLEAR_long_long((long long)n, s, e), \
        unsigned long long: __kmask_priv_function_type_CLEAR_unsigned_long_long((unsigned long long)n, s, e) \
    )


KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, char, char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, signed char, signed_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, unsigned char, unsigned_char)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, short, short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, unsigned short, unsigned_short)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, int, int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, unsigned int, unsigned_int)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, long, long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, unsigned long, unsigned_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, long long, long_long)
KMASK_PRIV_CREATE_FUNCTION_TYPE(TOGGLE, unsigned long long, unsigned_long_long)


#define KMASK_PRIV_TYPE_TOGGLE(n, s, e) \
    _Generic((n), \
        char:               __kmask_priv_function_type_TOGGLE_char((char)n, s, e), \
        signed char:        __kmask_priv_function_type_TOGGLE_signed_char((signed char)n, s, e), \
        unsigned char:      __kmask_priv_function_type_TOGGLE_unsigned_char((unsigned char)n, s, e), \
        short:              __kmask_priv_function_type_TOGGLE_short((short)n, s, e), \
        unsigned short:     __kmask_priv_function_type_TOGGLE_unsigned_short((unsigned short)n, s, e), \
        int:                __kmask_priv_function_type_TOGGLE_int((int)n, s, e), \
        unsigned int:       __kmask_priv_function_type_TOGGLE_unsigned_int((unsigned int)n, s, e), \
        long:               __kmask_priv_function_type_TOGGLE_long((long)n, s, e), \
        unsigned long:      __kmask_priv_function_type_TOGGLE_unsigned_long((unsigned long)n, s, e), \
        long long:          __kmask_priv_function_type_TOGGLE_long_long((long long)n, s, e), \
        unsigned long long: __kmask_priv_function_type_TOGGLE_unsigned_long_long((unsigned long long)n, s, e) \
    )

#endif

#define KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(rettype, type, suffix) \
    static inline rettype __kbit_priv_function_type_reverse_significant_ ## suffix(type n); \
    static inline rettype __kbit_priv_function_type_reverse_significant_ ## suffix(type n) \
    { \
        type reversed = 0; \
        \
        while (n > 0) \
        { \
            reversed = (type)(reversed << 1); \
            if (n & 1) \
                reversed ^= 1; \
            n >>= 1; \
        } \
        return (rettype)reversed; \
    }

KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(char, unsigned char, char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(signed char, unsigned char, signed_char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(unsigned char, unsigned char, unsigned_char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(short, unsigned short, short)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(unsigned short, unsigned short, unsigned_short)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(int, unsigned int, int)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(unsigned int, unsigned int, unsigned_int)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(long, unsigned long, long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(unsigned long, unsigned long, unsigned_long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(long long, unsigned long long, long_long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_SIGNIFICANT_BITS_TYPE(unsigned long long, unsigned long long, unsigned_long_long)

#define KBIT_PRIV_TYPE_REVERSE_SIGNIFICANT(n) \
    _Generic((n), \
        char:               __kbit_priv_function_type_reverse_significant_unsigned_char((unsigned char)n), \
        signed char:        __kbit_priv_function_type_reverse_significant_signed_char((unsigned char)n), \
        unsigned char:      __kbit_priv_function_type_reverse_significant_unsigned_char((unsigned char)n), \
        short:              __kbit_priv_function_type_reverse_significant_short((unsigned short)n), \
        unsigned short:     __kbit_priv_function_type_reverse_significant_unsigned_short((unsigned short)n), \
        int:                __kbit_priv_function_type_reverse_significant_int((unsigned int)n), \
        unsigned int:       __kbit_priv_function_type_reverse_significant_unsigned_int((unsigned int)n), \
        long:               __kbit_priv_function_type_reverse_significant_long((unsigned long)n), \
        unsigned long:      __kbit_priv_function_type_reverse_significant_unsigned_long((unsigned long)n), \
        long long:          __kbit_priv_function_type_reverse_significant_long_long((unsigned long long)n), \
        unsigned long long: __kbit_priv_function_type_reverse_significant_unsigned_long_long((unsigned long long)n) \
    )

#define KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(rettype, type, suffix) \
    static inline rettype __kbit_priv_function_type_reverse_ ## suffix(type n); \
    static inline rettype __kbit_priv_function_type_reverse_ ## suffix(type n) \
    { \
        type reversed = 0; \
        \
        for (size_t i = 0; i < sizeof(n) * CHAR_BIT; ++i) \
        { \
            reversed = (type)((reversed << 1) | (n & 1)); \
            n >>= 1; \
        } \
        return (rettype)reversed; \
    }

KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(char, unsigned char, char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(signed char, unsigned char, signed_char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(unsigned char, unsigned char, unsigned_char)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(short, unsigned short, short)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(unsigned short, unsigned short, unsigned_short)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(int, unsigned int, int)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(unsigned int, unsigned int, unsigned_int)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(long, unsigned long, long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(unsigned long, unsigned long, unsigned_long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(long long, unsigned long long, long_long)
KBIT_PRIV_CREATE_FUNCTION_REVERSE_BITS_TYPE(unsigned long long, unsigned long long, unsigned_long_long)

#define KBIT_PRIV_TYPE_REVERSE(n) \
    _Generic((n), \
        char:               __kbit_priv_function_type_reverse_unsigned_char((unsigned char)n), \
        signed char:        __kbit_priv_function_type_reverse_signed_char((unsigned char)n), \
        unsigned char:      __kbit_priv_function_type_reverse_unsigned_char((unsigned char)n), \
        short:              __kbit_priv_function_type_reverse_short((unsigned short)n), \
        unsigned short:     __kbit_priv_function_type_reverse_unsigned_short((unsigned short)n), \
        int:                __kbit_priv_function_type_reverse_int((unsigned int)n), \
        unsigned int:       __kbit_priv_function_type_reverse_unsigned_int((unsigned int)n), \
        long:               __kbit_priv_function_type_reverse_long((unsigned long)n), \
        unsigned long:      __kbit_priv_function_type_reverse_unsigned_long((unsigned long)n), \
        long long:          __kbit_priv_function_type_reverse_long_long((unsigned long long)n), \
        unsigned long long: __kbit_priv_function_type_reverse_unsigned_long_long((unsigned long long)n) \
    )

#define KBIT_PRIV_TYPE_FFS(n) \
    _Generic((n), \
        int:                KFFS((int)n), \
        unsigned int:       KFFS((int)n), \
        long:               KFFSL((long)n), \
        unsigned long:      KFFSL((long)n), \
        long long:          KFFSLL((long long)n), \
        unsigned long long: KFFSLL((long long)n) \
    )


#define KBIT_PRIV_TYPE_CLZ(n) \
    _Generic((n), \
        int:                KCLZ((unsigned int)n), \
        unsigned int:       KCLZ((unsigned int)n), \
        long:               KCLZL((unsigned long)n), \
        unsigned long:      KCLZL((unsigned long)n), \
        long long:          KCLZLL((unsigned long long)n), \
        unsigned long long: KCLZLL((unsigned long long)n) \
    )


#define KBIT_PRIV_TYPE_CTZ(n) \
    _Generic((n), \
        int:                KCTZ((unsigned int)n), \
        unsigned int:       KCTZ((unsigned int)n), \
        long:               KCTZL((unsigned long)n), \
        unsigned long:      KCTZL((unsigned long)n), \
        long long:          KCTZLL((unsigned long long)n), \
        unsigned long long: KCTZLL((unsigned long long)n) \
    )

#define KBIT_PRIV_TYPE_CLRSB(n) \
    _Generic((n), \
        int:                KCLRSB((int)n), \
        unsigned int:       KCLRSB((int)n), \
        long:               KCLRSBL((long)n), \
        unsigned long:      KCLRSBL((long)n), \
        long long:          KCLRSBLL((long long)n), \
        unsigned long long: KCLRSBLL((long long)n) \
    )


#define KBIT_PRIV_TYPE_POPCOUNT(n) \
    _Generic((n), \
        int:                KPOPCOUNT((unsigned int)n), \
        unsigned int:       KPOPCOUNT((unsigned int)n), \
        long:               KPOPCOUNTL((unsigned long)n), \
        unsigned long:      KPOPCOUNTL((unsigned long)n), \
        long long:          KPOPCOUNTLL((unsigned long long)n), \
        unsigned long long: KPOPCOUNTLL((unsigned long long)n) \
    )

#define KBIT_PRIV_TYPE_PARITY(n) \
    _Generic((n), \
        int:                KPARITY((unsigned int)n), \
        unsigned int:       KPARITY((unsigned int)n), \
        long:               KPARITYL((unsigned long)n), \
        unsigned long:      KPARITYL((unsigned long)n), \
        long long:          KPARITYLL((unsigned long long)n), \
        unsigned long long: KPARITYLL((unsigned long long)n) \
    )

#endif
