#ifndef KBITS_H
#define KBITS_H

/*
    This is the private header for the KMacros.

    This header constains all macros connected with bits (except builtins)

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kbits.h> directly, use <kmacros/kbits.h> instead."
#endif

#include "kbits-priv.h"

/**
 * Macro creates mask for at most long long type
 *
 * @param[in] s - start pos of mask (first bit from right has pos 0)
 * @param[in] e - end pos of mask (last bit from right has pos sizeof(type) * CHAR_BIT - 1)
 *
 * @return mask with '1' on positions [s; e]
 *
 * Example:
 * int a = KMASK(1, 3) will produce 0000...1110
 */
#define KMASK(s, e)          KMASK_PRIV_TYPE(s, e)

/**
 * Get normalized mask from number
 *
 * @param[in] n - number
 * @param[in] s - start pos of mask (first bit from right has pos 0)
 * @param[in] e - end pos of mask (last bit from right has pos sizeof(type) * CHAR_BIT - 1)
 *
 * @return normalized mask from n
 *
 * Example:
 * int a = KMASK(1, 3) will produce 0000...1110
 * int b = KMASK_GET(2, 3) will return 000000...11 because mask is normalized (shiffted to right)
 */
#define KMASK_GET(n, s, e)    KMASK_PRIV_TYPE_GET(n, s, e)

/**
 * Produce number with additional mask on top of previous number. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] s - start pos of mask (first bit from right has pos 0)
 * @param[in] e - end pos of mask (last bit from right has pos sizeof(type) * CHAR_BIT - 1)
 *
 * @return number n with additional bits set to '1'
 *
 * Example:
 * int a = KMASK(1, 3) will produce 0000...1110
 * int b = KMASK_SET(2, 5) will return 000000...111110
 */
#define KMASK_SET(n, s, e)    KMASK_PRIV_TYPE_SET(n, s, e)

/**
 * Produce number with cleaned mask on top of number n. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] s - start pos of mask (first bit from right has pos 0)
 * @param[in] e - end pos of mask (last bit from right has pos sizeof(type) * CHAR_BIT - 1)
 *
 * @return number n with cleaned bits, set to '0'
 *
 * Example:
 * int a = KMASK(1, 3) will produce 0000...1110
 * int b = KMASK_CLEAN(2, 5) will return 000000...0010
 */
#define KMASK_CLEAR(n, s, e)   KMASK_PRIV_TYPE_CLEAR(n, s, e)


/**
 * Produce number with opposite mask (1->0, 0->1) on top of number n. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] s - start pos of mask (first bit from right has pos 0)
 * @param[in] e - end pos of mask (last bit from right has pos sizeof(type) * CHAR_BIT - 1)
 *
 * @return number n with toggled bits
 *
 * Example:
 * int a = KMASK(1, 3) will produce 0000...1110
 * int b = KMASK_TOGGLE(2, 5) will return 000000...110010
 */
#define KMASK_TOGGLE(n, s, e)  KMASK_PRIV_TYPE_TOGGLE(n, s, e)

/**
 * Macro creates mask with one bit for at most long long type
 *
 * @param[in] k - bit to set (valid k is [0; sizeof(type) * CHAR_BIT - 1])
 *
 * @return mask with '1' on kth position
 *
 * Example:
 * int a = KBIT(3) will produce 0000...1000
 */
#define KBIT(k)               KMASK(k, k)

/**
 * Get normalized bit (0 or 1) from number
 *
 * @param[in] n - number
 * @param[in] k - bit position. (valid k is [0; sizeof(type) * CHAR_BIT - 1])
 *
 * @return normalized bit from n
 *
 * Example:
 * int a = KBIT(3) will produce 0000...1000
 * int b = KBIT_GET(3) will return 000000...01 because bit is normalized (shiffted to right)
 */
#define KBIT_GET(n, k)        KMASK_GET(n, k, k)

/**
 * Set bit ('1') on top of number n. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] k - bit position. (valid k is [0; sizeof(type) * CHAR_BIT - 1])
 *
 * @return n with another bit set to '1'
 *
 * Example:
 * int a = KBIT(3) will produce 0000...1000
 * int b = KBIT_SET(1) will return 000000...1001
 */
#define KBIT_SET(n, k)        KMASK_SET(n, k, k)

/**
 * Clean bit ('1' -> '0') on top of number n. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] k - bit position. (valid k is [0; sizeof(type) * CHAR_BIT - 1])
 *
 * @return n with cleaned bit
 *
 * Example:
 * int a = KBIT(3) will produce 0000...1000
 * int b = KBIT_CLEAN(3) will return 000000...000
 */
#define KBIT_CLEAR(n, k)      KMASK_CLEAR(n, k, k)

/**
 * Toggle bit ('1' -> '0', '0' -> '1') on top of number n. Number n will not be modified
 *
 * @param[in] n - number
 * @param[in] k - bit position. (valid k is [0; sizeof(type) * CHAR_BIT - 1])
 *
 * @return n with toggled bit
 *
 * Example:
 * int a = KBIT(3) will produce 0000...1000
 * int b = KBIT_TOGGLE(0) will return 000000...1001
 */
#define KBIT_TOGGLE(n, k)     KMASK_TOGGLE(n, k, k)

/**
 * Reverse significants bits variable. Number n will not be modified
 *
 * @params[in] n - number
 *
 * @return n with reversed only significants bits
 *
 * Example
 * int a = 0xA // 00....1010
 * int b = KBIT_REVERSE_SIGNIFICANT(a) will return 0000.. 0101 not 0101 0000
 */
#define KBIT_REVERSE_SIGNIFICANT(n)       KBIT_PRIV_TYPE_REVERSE_SIGNIFICANT(n)

/**
 * Reverse bits order in variable. Number n will not be modified
 *
 * @params[in] n - number
 *
 * @return n with reversed bits order
 *
 * Example
 * int a = 0xA // 00....1010
 * int b = KBITS_REVERSE(a) will return 0101 00000... 0
 */
#define KBIT_REVERSE(n)                   KBIT_PRIV_TYPE_REVERSE(n)

/**
 * Returns one plus the index of the least significant 1-bit of n, or if n is zero, returns zero.
 */
#define KBIT_FFS(n)                       KBIT_PRIV_TYPE_FFS(n)

/**
 * Returns the number of leading 0-bits in n, starting at the most significant bit position.
 * If n is 0, the result is undefined.
 */
#define KBIT_CLZ(n)                       KBIT_PRIV_TYPE_CLZ(n)

/**
 * Returns the number of trailing 0-bits in n, starting at the least significant bit position.
 * If n is 0, the result is undefined.
 */
#define KBIT_CTZ(n)                       KBIT_PRIV_TYPE_CTZ(n)

/**
 * Returns the number of leading redundant sign bits in n, i.e.
 * the number of bits following the most significant bit that are identical to it.
 * There are no special cases for 0 or other values.
 */
#define KBIT_CLRSB(n)                     KBIT_PRIV_TYPE_CLRSB(n)

/**
 * Returns the number of 1-bits in n.
 */
#define KBIT_POPCOUNT(n)                  KBIT_PRIV_TYPE_POPCOUNT(n)
/**
 * Returns the parity of n, i.e. the number of 1-bits in x modulo 2.
 */
#define KBIT_PARITY(n)                    KBIT_PRIV_TYPE_PARITY(n)

#endif
