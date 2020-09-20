#ifndef KCOMPILER_UNKNOWN_H
#define KCOMPILER_UNKNOWN_H

/*
    This is the private header for the KMacros.

    Do not include it directly

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kcompiler-unknown.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "kpreprocessor.h"
#include "kbuiltins-implementation.h"

/*********** DIAGNOSTIC SECTION ******************/

/* Only stubs, we dont know compiler, so we dont know how to implement them */
#define KCOMPILER_ERROR(msg)
#define KCOMPILER_WARNING(msg)
#define KCOMPILER_DIAG_PUSH()
#define KCOMPILER_DIAG_POP()
#define KCOMPILER_DIAG_WARNING(str)
#define KCOMPILER_DIAG_ERROR(str)
#define KCOMPILER_DIAG_IGNORE(str)

/*********** BUILTINS SECTION ******************/

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * You may use KEXPECT to provide the compiler with branch prediction information.
 * In general, you should prefer to use actual profile feedback for this (-fprofile-arcs),
 * as programmers are notoriously bad at predicting how their programs actually perform.
 * However, there are applications in which this data is hard to collect.
 * The return value is the value of exp, which should be an integral expression.
 * The semantics of the built-in are that it is expected that exp == c.
 */
#define KEXPECT(cond, val)                       kbuiltin_expect_impl(cond, val)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * The same as KEXPECT but it will try predict branches with some probability
 */
#define KEXPECT_PROBABILITY(cond, val, prob)     kbuiltin_expect_with_probability_impl(cond, val, prob)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * You can use the built-in function __builtin_choose_expr to evaluate code depending on
 * the value of a constant expression.
 * This built-in function returns exp1 if const_exp, which is an integer constant expression,
 * is nonzero. Otherwise it returns exp2.
 * This built-in function is analogous to the ‘? :’ operator in C,
 * except that the expression returned has its type unaltered by promotion rules.
 * Also, the built-in function does not evaluate the expression that is not chosen.
 * For example, if const_exp evaluates to true, exp2 is not evaluated even if it has side effects.
 * This built-in function can return an lvalue if the chosen argument is an lvalue.
 */
#define KCHOOSE_EXPRESSION(cond, tstate, fstate) kbuiltin_choose_expr_impl(cond, tstate, fstate)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * You can use the built-in function __builtin_types_compatible_p to
 * determine whether two types are the same.
 * This built-in function returns 1 if the unqualified versions of the types type1 and type2
 * (which are types, not expressions) are compatible, 0 otherwise.
 * The result of this built-in function can be used in integer constant expressions.
 * This built-in function ignores top level qualifiers (e.g., const, volatile).
 * For example, int is equivalent to const int.
 * The type int[] and int[5] are compatible.
 * On the other hand, int and char * are not compatible, even if the size of their types,
 * on the particular architecture are the same.
 * Also, the amount of pointer indirection is taken into account when determining similarity.
 * Consequently, short * is not similar to short **.
 * Furthermore, two types that are typedefed are considered compatible if their
 * underlying types are compatible.
 */
#define KTYPES_COMPATIBLE(type1, type2)          kbuiltin_types_compatible_p_impl(type1, type2)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * You can use the built-in function __builtin_constant_p to determine
 * if a value is known to be constant at compile time and hence that GCC can perform
 * constant-folding on expressions involving that value.
 * The argument of the function is the value to test.
 * The function returns the integer 1 if the argument is known to be a compile-time constant
 * and 0 if it is not known to be a compile-time constant.
 * A return of 0 does not indicate that the value is not a constant,
 * but merely that GCC cannot prove it is a constant with the specified value of the -O option.
 */
#define KIS_CONSTANT_EXPRESSION(expr)            kbuiltin_constant_p_impl(expr)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
 * KFFS(int x)
 * KFFSL(long x)
 * KFFSLL(long long x)
 */
#define KFFS(x)          kbuiltin_ffs_impl(x)
#define KFFSL(x)         kbuiltin_ffsl_impl(x)
#define KFFSLL(x)        kbuiltin_ffsll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the number of leading 0-bits in x, starting at the most significant bit position.
 * If x is 0, the result is undefined
 *
 * KCLZ(unsigned int x)
 * KCLZL(unsigned long x)
 * KCLZLL(unsigned long long x)
 */
#define KCLZ(x)          kbuiltin_clz_impl(x)
#define KCLZL(x)         kbuiltin_clzl_impl(x)
#define KCLZLL(x)        kbuiltin_clzll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the number of trailing 0-bits in x, starting at the least significant bit position.
 * If x is 0, the result is undefined.
 *
 * KCTZ(unsigned int x)
 * KCTZL(unsigned long x)
 * KCTZLL(unsigned long long x)
 */
#define KCTZ(x)          kbuiltin_ctz_impl(x)
#define KCTZL(x)         kbuiltin_ctzl_impl(x)
#define KCTZLL(x)        kbuiltin_ctzll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the number of leading redundant sign bits in x, i.e.
 * the number of bits following the most significant bit that are identical to it.
 * There are no special cases for 0 or other values.
 *
 * KCLRSB(int x)
 * KCLRSBL(long x)
 * KCLRSBLL(long long x)
 */
#define KCLRSB(x)        kbuiltin_clrsb_impl(x)
#define KCLRSBL(x)       kbuiltin_clrsbl_impl(x)
#define KCLRSBLL(x)      kbuiltin_clrsbll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the number of 1-bits in x.
 *
 * KPOPCOUNT(unsigned int x)
 * KPOPCOUNTL(unsigned long x)
 * KPOPCOUNTLL(unsigned long long x)
 */
#define KPOPCOUNT(x)     kbuiltin_popcount_impl(x)
#define KPOPCOUNTL(x)    kbuiltin_popcountl_impl(x)
#define KPOPCOUNTLL(x)   kbuiltin_popcountll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the parity of x, i.e. the number of 1-bits in x modulo 2.
 *
 * KPARITY(unsigned int x)
 * KPARITYL(unsigned long x)
 * KPARITYLL(unsigned long long x)
 */
#define KPARITY(x)       kbuiltin_parity_impl(x)
#define KPARITYL(x)      kbuiltin_parityl_impl(x)
#define KPARITYLL(x)     kbuiltin_parityll_impl(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns x with the order of the bytes reversed; for example, 0xaabb becomes 0xbbaa.
 * Byte here always means exactly 8 bits
 *
 * KBSWAP16(uint16_t x)
 * KBSWAP32(uint32_t x)
 * KBSWAP64(uint64_t x)
 */
#define KBSWAP16(x)      kbuiltin_bswap16_impl(x)
#define KBSWAP32(x)      kbuiltin_bswap32_impl(x)
#define KBSWAP64(x)      kbuiltin_bswap64_impl(x)

/**
 * See https://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros
 *
 * Each builtin performs the specified mathematical operation on the first two arguments
 * and stores the result in the third argument.
 * If possible, the result will be equal to mathematically-correct result
 * and the builtin will return 0.
 * Otherwise, the builtin will return 1 and the result will be equal
 * to the unique value that is equivalent to the mathematically-correct result
 * modulo two raised to the k power, where k is the number of bits in the result type.
 * The behavior of these builtins is well-defined for all argument values.
 *
 * ADD --> *res = x + y.
 * SUB --> *res = x - y
 * MUL --> *res = x * y
 *
 * KUADD_OVERFLOW(unsigned int x, unsigned int y, unsigned int* res)
 * KUADDL_OVERFLOW(unsigned long x, unsigned long y, unsigned long* res)
 * KUADDLL_OVERFLOW(unsigned long long x, unsigned long long y, unsigned long long* res)
 *
 * KADD_OVERFLOW(int x, int y, int* res)
 * KADDL_OVERFLOW(long x, long y, long* res)
 * KADDLL_OVERFLOW(long long x, long long y, long long* res)
 *
 * KADD_OVERFLOW(x, y, res) --> analyze x y type and choose one of the function
 *
 * The same convention is applicable to SUB and MUL family
*/
#define KADD_OVERFLOW(x, y, res)      kbuiltin_add_overflow_impl(x, y, res)

#define KUADD_OVERFLOW(x, y, res)     kbuiltin_uadd_overflow_impl(x, y, res)
#define KUADDL_OVERFLOW(x, y, res)    kbuiltin_uaddl_overflow_impl(x, y, res)
#define KUADDLL_OVERFLOW(x, y, res)   kbuiltin_uaddll_overflow_impl(x, y, res)

#define KSADD_OVERFLOW(x, y, res)     kbuiltin_sadd_overflow_impl(x, y, res)
#define KSADDL_OVERFLOW(x, y, res)    kbuiltin_saddl_overflow_impl(x, y, res)
#define KSADDLL_OVERFLOW(x, y, res)   kbuiltin_saddll_overflow_impl(x, y, res)

#define KSUB_OVERFLOW(x, y, res)      kbuiltin_sub_overflow_impl(x, y, res)

#define KUSUB_OVERFLOW(x, y, res)     kbuiltin_usub_overflow_impl(x, y, res)
#define KUSUBL_OVERFLOW(x, y, res)    kbuiltin_usubl_overflow_impl(x, y, res)
#define KUSUBLL_OVERFLOW(x, y, res)   kbuiltin_usubll_overflow_impl(x, y, res)

#define KSSUB_OVERFLOW(x, y, res)     kbuiltin_ssub_overflow_impl(x, y, res)
#define KSSUBL_OVERFLOW(x, y, res)    kbuiltin_ssubl_overflow_impl(x, y, res)
#define KSSUBLL_OVERFLOW(x, y, res)   kbuiltin_ssubll_overflow_impl(x, y, res)

#define KMUL_OVERFLOW(x, y, res)      kbuiltin_mul_overflow_impl(x, y, res)

#define KUMUL_OVERFLOW(x, y, res)     kbuiltin_umul_overflow_impl(x, y, res)
#define KUMULL_OVERFLOW(x, y, res)    kbuiltin_umull_overflow_impl(x, y, res)
#define KUMULLL_OVERFLOW(x, y, res)   kbuiltin_umulll_overflow_impl(x, y, res)

#define KSMUL_OVERFLOW(x, y, res)     kbuiltin_smul_overflow_impl(x, y, res)
#define KSMULL_OVERFLOW(x, y, res)    kbuiltin_smull_overflow_impl(x, y, res)
#define KSMULLL_OVERFLOW(x, y, res)   kbuiltin_smulll_overflow_impl(x, y, res)

/*********** ATTRIBUTES SECTION ******************/
#define KATTR_FUNC_ALWAYS_INLINE
#define KATTR_FUNC_CONST
#define KATTR_FUNC_CONSTRUCTOR
#define KATTR_FUNC_DESTRUCTOR
#define KATTR_FUNC_DEPRECATED(msg)
#define KATTR_FUNC_ERROR(msg)
#define KATTR_FUNC_FORMAT_PRINTF(fmt_index, vaargs_index)
#define KATTR_FUNC_FORMAT_SCANF(fmt_index, vaargs_index)
#define KATTR_FUNC_FORMAT_STRFTIME(fmt_index)
#define KATTR_FUNC_FORMAT_STRFMON(fmt_index, vaargs_index)
#define KATTR_FUNC_FORMAT_ARG(arg_index)
#define KATTR_FUNC_MALLOC
#define KATTR_FUNC_NONNULL(...)
#define KATTR_FUNC_NORETURN
#define KATTR_FUNC_PURE
#define KATTR_FUNC_UNUSED

#define KATTR_VAR_CLEANUP(func)
#define KATTR_VAR_ALIGNED(x)
#define KATTR_VAR_DEPRECATED(msg)
#define KATTR_VAR_NONSTRING
#define KATTR_VAR_PACKED
#define KATTR_VAR_UNUSED
#define KATTR_VAR_VECTOR_SIZE(size)
#define KATTR_VAR_NOINIT

#define KFALLTRGOUGH_FAKE do { } while (0)

#endif
