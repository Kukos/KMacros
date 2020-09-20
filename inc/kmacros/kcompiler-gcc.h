#ifndef KCOMPILER_GCC_H
#define KCOMPILER_GCC_H

/*
    This is the private header for the KMacros.

    Do not include it directly.

    Here put all macros, functions, directives from gcc compiler

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com
    LICENCE: GPL3
*/

#ifndef KMACROS_H
#error "Never include <kmacros/kcompiler-gcc.h> directly, use <kmacros/kmacros.h> instead."
#endif

#include "kpreprocessor.h"
#include "kbuiltins-implementation.h"

/*********** DIAGNOSTIC SECTION ******************/

#define KPRAGMA_GCC(mode, msg)      _Pragma(KTOSTRING(GCC mode msg))

/* Private macro, do no use */
#define KDIAG_GCC(msg)              KPRAGMA_GCC(diagnostic, msg)

/**
 * Generates an error message.
 * This pragma is considered to indicate an error in the compilation,
 * and it will be treated as such.
 */
#define KCOMPILER_ERROR(msg)        KPRAGMA_GCC(error, msg)

/**
 * This is just like ‘pragma GCC error’ except that a warning message is issued
 * instead of an error message.
 * Unless -Werror is in effect, in which case this pragma will generate an error as well.
 */
#define KCOMPILER_WARNING(msg)      KPRAGMA_GCC(warning, msg)

/**
 * Use it to push (store for a while) diagnostic options
 *
 * Example: KCOMPILER_DIAG_PUSH()
 * Please note that clang shows you a warning when you put a semicolon at the end
 */
#define KCOMPILER_DIAG_PUSH()       KDIAG_GCC(push)

/**
 * Use it to pop (restore) diagnostic options
 *
 * Example: KCOMPILER_DIAG_POP()
 * Please note that clang shows you a warning when you put a semicolon at the end
 */
#define KCOMPILER_DIAG_POP()        KDIAG_GCC(pop)

/**
 * Use it to add another Warning to options (works like "-W")
 *
 * Example: KCOMPILER_DIAG_WARNING("-Wall")
 * Please note that clang shows you a warning when you put a semicolon at the end
 */
#define KCOMPILER_DIAG_WARNING(str) KDIAG_GCC(warning str)

/**
 * Use it to add another Warning to options (works like "-W -Werror")
 *
 * Example: KCOMPILER_DIAG_ERROR("-Wall")
 * Please note that clang shows you a warning when you put a semicolon at the end
 */
#define KCOMPILER_DIAG_ERROR(str)   KDIAG_GCC(error str)

/**
 * Use it to ignore Warning from options (works like "-Wno")
 *
 * Example: KCOMPILER_DIAG_IGNORE("-Wuninitialized")
 * Please note that clang shows you a warning when you put a semicolon at the end
 *
 * Some warnings have been added to "whitelist" by compiler developer.
 * You cannot ignore them by this option
 */
#define KCOMPILER_DIAG_IGNORE(str)  KDIAG_GCC(ignored str)

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
#define KEXPECT(cond, val)                       __builtin_expect(cond, val)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * The same as KEXPECT but it will try predict branches with some probability
 */
#define KEXPECT_PROBABILITY(cond, val, prob)     __builtin_expect_with_probability(cond, val, prob)

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
#define KCHOOSE_EXPRESSION(cond, tstate, fstate) __builtin_choose_expr(cond, tstate, fstate)

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
#define KTYPES_COMPATIBLE(type1, type2)          __builtin_types_compatible_p(type1, type2)

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
#define KIS_CONSTANT_EXPRESSION(expr)            __builtin_constant_p(expr)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
 * KFFS(int x)
 * KFFSL(long x)
 * KFFSLL(long long x)
 */
#define KFFS(x)          __builtin_ffs(x)
#define KFFSL(x)         __builtin_ffsl(x)
#define KFFSLL(x)        __builtin_ffsll(x)

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
#define KCLZ(x)          __builtin_clz(x)
#define KCLZL(x)         __builtin_clzl(x)
#define KCLZLL(x)        __builtin_clzll(x)

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
#define KCTZ(x)          __builtin_ctz(x)
#define KCTZL(x)         __builtin_ctzl(x)
#define KCTZLL(x)        __builtin_ctzll(x)

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
#define KCLRSB(x)        __builtin_clrsb(x)
#define KCLRSBL(x)       __builtin_clrsbl(x)
#define KCLRSBLL(x)      __builtin_clrsbll(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the number of 1-bits in x.
 *
 * KPOPCOUNT(unsigned int x)
 * KPOPCOUNTL(unsigned long x)
 * KPOPCOUNTLL(unsigned long long x)
 */
#define KPOPCOUNT(x)     __builtin_popcount(x)
#define KPOPCOUNTL(x)    __builtin_popcountl(x)
#define KPOPCOUNTLL(x)   __builtin_popcountll(x)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#Other-Builtins
 *
 * Returns the parity of x, i.e. the number of 1-bits in x modulo 2.
 *
 * KPARITY(unsigned int x)
 * KPARITYL(unsigned long x)
 * KPARITYLL(unsigned long long x)
 */
#define KPARITY(x)       __builtin_parity(x)
#define KPARITYL(x)      __builtin_parityl(x)
#define KPARITYLL(x)     __builtin_parityll(x)

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
#define KBSWAP16(x)      __builtin_bswap16(x)
#define KBSWAP32(x)      __builtin_bswap32(x)
#define KBSWAP64(x)      __builtin_bswap64(x)

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

#if defined(__has_attribute)

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * Generally, functions are not inlined unless optimization is specified.
 * For functions declared inline, this attribute inlines the function independent
 * of any restrictions that otherwise apply to inlining.
 * Failure to inline such a function is diagnosed as an error.
 * Note that if such a function is called indirectly the compiler may or may not
 * inline it depending on optimization level and a failure to inline
 * an indirect call may or may not be diagnosed.
 */
#if __has_attribute(always_inline)
#define KATTR_FUNC_ALWAYS_INLINE __attribute__((always_inline))
#else
#define KATTR_FUNC_ALWAYS_INLINE
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 * Calls to functions whose return value is not affected by changes to the observable
 * state of the program and that have no observable effects on such state
 * other than to return a value may lend themselves to optimizations such
 *  as common subexpression elimination.
 * Declaring such functions with the const attribute allows GCC to avoid emitting some calls
 * in repeated invocations of the function with the same argument values.
 *
 * For example,
 * int square (int) KATTR_FUNC_CONST;
 * tells GCC that subsequent calls to function square with the same argument
 * value can be replaced by the result of the first call regardless of the statements in between.
 *
 * The const attribute prohibits a function from reading objects that affect its
 * return value between successive invocations.
 * However, functions declared with the attribute can safely read objects
 * that do not change their return value, such as non-volatile constants.
 *
 * The const attribute imposes greater restrictions on a function’s definition than
 * the similar pure attribute.
 * Declaring the same function with both the const and the pure attribute is diagnosed.
 * Because a const function cannot have any observable side effects it does not make sense
 * for it to return void.
 *
 * Declaring such a function is diagnosed.
 */
#if __has_attribute(const)
#define KATTR_FUNC_CONST __attribute__((const))
#else
#define KATTR_FUNC_CONST
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The constructor attribute causes the function to be called automatically
 * before execution enters main ().
 * Similarly, the destructor attribute causes the function to be called automatically after main ()
 * completes or exit () is called.
 * Functions with these attributes are useful for initializing data
 * that is used implicitly during the execution of the program.
 */
#if __has_attribute(constructor)
#define KATTR_FUNC_CONSTRUCTOR __attribute__((constructor))
#else
#define KATTR_FUNC_CONSTRUCTOR KCOMPILER_ERROR("__attribute__((constructor)) unsupported")
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The constructor attribute causes the function to be called automatically
 * before execution enters main ().
 * Similarly, the destructor attribute causes the function to be called automatically after main ()
 * completes or exit () is called.
 * Functions with these attributes are useful for initializing data
 * that is used implicitly during the execution of the program.
 */
#if __has_attribute(destructor)
#define KATTR_FUNC_DESTRUCTOR __attribute__((destructor))
#else
#define KATTR_FUNC_DESTRUCTOR KCOMPILER_ERROR("__attribute__((destructor)) unsupported")
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The deprecated attribute results in a warning if the function is used anywhere in the source file.
 * This is useful when identifying functions that are expected to be removed
 * in a future version of a program.
 * The warning also includes the location of the declaration of the deprecated function,
 * to enable users to easily find further information about why the function is deprecated,
 * or what they should do instead.
 * Note that the warnings only occurs for uses:
 *
 * int old_fn () KATTR_FUNC_DEPRECATED("old_fn will be removed");
 * int old_fn () { return 0; }
 * int (*fn_ptr)() = old_fn;
 *
 * results in a warning on line 3 but not line 2
 */
#if __has_attribute(deprecated)
#define KATTR_FUNC_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#define KATTR_FUNC_DEPRECATED(msg)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * If the error or warning attribute is used on a function declaration and
 * a call to such a function is not eliminated through dead code elimination or other optimizations,
 * an error or warning (respectively) that includes message is diagnosed.
 * This is useful for compile-time checking, especially together with __builtin_constant_p
 * and inline functions where checking the inline function arguments
 * is not possible through extern char [(condition) ? 1 : -1]; tricks.
 */
#if __has_attribute(error)
#define KATTR_FUNC_ERROR(msg) __attribute__((error(msg)))
#else
#define KATTR_FUNC_ERROR(msg)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The format attribute specifies that a function takes printf, scanf, strftime or strfmon
 * style arguments that should be type-checked against a format string.
 *
 * For example, the declaration:
 *
 * extern int my_printf (void *my_object, const char *my_format, ...) KATTR_FUNC_FORMAT_PRINTF(2, 3);
 * causes the compiler to check the arguments in calls to my_printf for
 * consistency with the printf style format string argument my_format.
 *
 * The parameter archetype determines how the format string is interpreted,
 * In the example above, the format string (my_format) is the second argument of the function my_print,
 * and the arguments to check start with the third argument,
 * so the correct parameters for the format attribute are 2 and 3.
 */
#if __has_attribute(format)
#define KATTR_FUNC_FORMAT_PRINTF(fmt_index, vaargs_index)   __attribute__((format(printf, fmt_index, vaargs_index)))
#define KATTR_FUNC_FORMAT_SCANF(fmt_index, vaargs_index)    __attribute__((format(scanf, fmt_index, vaargs_index)))
#define KATTR_FUNC_FORMAT_STRFTIME(fmt_index)               __attribute__((format(strftime, fmt_index, 0)))
#define KATTR_FUNC_FORMAT_STRFMON(fmt_index, vaargs_index)  __attribute__((format(strfmon, fmt_index, vaargs_index)))
#else
#define KATTR_FUNC_FORMAT_PRINTF(fmt_index, vaargs_index)
#define KATTR_FUNC_FORMAT_SCANF(fmt_index, vaargs_index)
#define KATTR_FUNC_FORMAT_STRFTIME(fmt_index)
#define KATTR_FUNC_FORMAT_STRFMON(fmt_index, vaargs_index)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The format_arg attribute specifies that a function takes one or more format strings for a
 * printf, scanf, strftime or strfmon style function and modifies it
 * (for example, to translate it into another language),
 * so the result can be passed to a printf, scanf, strftime or strfmon
 * style function (with the remaining arguments to the format function
 * the same as they would have been for the unmodified string).
 * Multiple format_arg attributes may be applied to the same function,
 * each designating a distinct parameter as a format string. For example, the declaration:
 *
 * extern char *my_dgettext (char *my_domain, const char *my_format) KATTR_FUNC_FORMAT_ARG(2);
 *
 * causes the compiler to check the arguments in calls to a printf, scanf, strftime or strfmon
 * type function, whose format string argument is a call to the my_dgettext function,
 * for consistency with the format string argument my_format.
 * If the format_arg attribute had not been specified,
 * all the compiler could tell in such calls to format functions would be that the
 * format string argument is not constant; this would generate a warning
 * when -Wformat-nonliteral is used, but the calls could not be checked without the attribute.
 *
 * The format_arg attribute allows you to identify your own functions that modify format strings,
 * so that GCC or clang can check the calls to printf, scanf, strftime or strfmon type function
 * whose operands are a call to one of your own function.
 */
#if __has_attribute(format_arg)
#define KATTR_FUNC_FORMAT_ARG(arg_index) __attribute__((format_arg(arg_index)))
#else
#define KATTR_FUNC_FORMAT_ARG(arg_index)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * This tells the compiler that a function is malloc-like, i.e., that the pointer P
 * returned by the function cannot alias any other pointer valid when the function returns,
 * and moreover no pointers to valid objects occur in any storage addressed by P.
 *
 * Using this attribute can improve optimization.
 * Compiler predicts that a function with the attribute returns non-null in most cases.
 * Functions like malloc and calloc have this property because they return a pointer to
 * uninitialized or zeroed-out storage.
 * However, functions like realloc do not have this property,
 * as they can return a pointer to storage containing pointers.
 */
#if __has_attribute(malloc)
#define KATTR_FUNC_MALLOC __attribute__((malloc))
#else
#define KATTR_FUNC_MALLOC
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * The nonnull attribute may be applied to a function that takes at least one argument of a pointer type.
 * It indicates that the referenced arguments must be non-null pointers.
 * For instance, the declaration:
 *
 * extern void *my_memcpy (void *dest, const void *src, size_t len) KATTR_FUNC_NONNULL(1, 2);
 *
 * causes the compiler to check that, in calls to my_memcpy,
 * arguments dest and src are non-null.
 * If the compiler determines that a null pointer is passed in an argument
 * slot marked as non-null, and the -Wnonnull option is enabled, a warning is issued.
 */
#if __has_attribute(nonnull)
#define KATTR_FUNC_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
#else
#define KATTR_FUNC_NONNULL(...)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * A few standard library functions, such as abort and exit, cannot return.
 * Compiler knows this automatically.
 * Some programs define their own functions that never return.
 * You can declare them noreturn to tell the compiler this fact. For example,
 *
 * void fatal (void) KATTR_FUNC_NORETURN;
 * void fatal (void) { abort(); }
 * The noreturn keyword tells the compiler to assume that fatal cannot return.
 * It can then optimize without regard to what would happen if fatal ever did return.
 * This makes slightly better code.
 * More importantly, it helps avoid spurious warnings of uninitialized variables.
 *
 * The noreturn keyword does not affect the exceptional path when that applies:
 * a noreturn-marked function may still return to the caller by throwing an exception
 * or calling longjmp.
 *
 * In order to preserve backtraces, Compiler will never turn calls to noreturn functions into tail calls.
 *
 * Do not assume that registers saved by the calling function are restored
 * before calling the noreturn function.
 *
 * It does not make sense for a noreturn function to have a return type other than void.
 */
#if __has_attribute(noreturn)
#define KATTR_FUNC_NORETURN __attribute__((noreturn))
#else
#define KATTR_FUNC_NORETURN
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * Calls to functions that have no observable effects on the state of the program other
 * than to return a value may lend themselves to optimizations such as common subexpression elimination.
 * Declaring such functions with the pure attribute allows GCC to avoid emitting some calls in repeated invocations of the function with the same argument values.
 *
 * The pure attribute prohibits a function from modifying the state of the program that
 * is observable by means other than inspecting the function’s return value.
 * However, functions declared with the pure attribute can safely read any non-volatile objects,
 * and modify the value of objects in a way that does not affect
 * their return value or the observable state of the program.
 *
 * For example,
 * int hash (char *) KATTR_FUNC_PURE;
 *
 * tells GCC that subsequent calls to the function hash with the same string can be replaced
 * by the result of the first call provided the state of the program observable by hash,
 * including the contents of the array itself, does not change in between.
 * Even though hash takes a non-const pointer argument it must not modify the array it points to,
 * or any other object whose value the rest of the program may depend on.
 * However, the caller may safely change the contents of the array between successive
 * calls to the function (doing so disables the optimization).
 */
#if __has_attribute(pure)
#define KATTR_FUNC_PURE __attribute__((pure))
#else
#define KATTR_FUNC_PURE
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#Common-Function-Attributes
 *
 * This attribute, attached to a function, means that code must be emitted
 * for the function even if it appears that the function is not referenced.
 * This is useful, for example, when the function is referenced only in inline assembly.
 */
#if __has_attribute(unused)
#define KATTR_FUNC_UNUSED __attribute__((unused))
#else
#define KATTR_FUNC_UNUSED
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * The aligned attribute specifies a minimum alignment for the variable
 * or structure field, measured in bytes.
 * When specified, alignment must be an integer constant power of 2.
 * For example, the declaration:
 *
 * int x KATTR_VAR_ALIGNED(16) = 0;
 *
 * causes the compiler to allocate the global variable x on a 16-byte boundary.
 *
 * You can also specify the alignment of structure fields.
 * For example, to create a double-word aligned int pair, you could write:
 *
 * struct foo { int x[2] KATTR_VAR_ALIGNED(8); };
 *
 * This is an alternative to creating a union with a double member,
 * which forces the union to be double-word aligned.
 *
 * When used on a struct, or struct member, the aligned attribute can only increase the alignment; in order to decrease it, the packed attribute must be specified as well. When used as part of a typedef, the aligned attribute can both increase and decrease alignment, and specifying the packed attribute generates a warning.
 *
 * Note that the effectiveness of aligned attributes
 * for static variables may be limited by inherent limitations in the system linker
 * and/or object file format.
 * On some systems, the linker is only able to arrange for variables to be aligned up
 * to a certain maximum alignment.
 * (For some linkers, the maximum supported alignment may be very very small.)
 * If your linker is only able to align variables up to a maximum of 8-byte alignment,
 * then specifying aligned(16) in an __attribute__ still only provides you with 8-byte alignment.
 * See your linker documentation for further information.
 */
#if __has_attribute(aligned)
#define KATTR_VAR_ALIGNED(x) __attribute__((aligned(x)))
#else
#define KATTR_VAR_ALIGNED(x)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * The cleanup attribute runs a function when the variable goes out of scope.
 * This attribute can only be applied to auto function scope variables;
 * it may not be applied to parameters or variables with static storage duration.
 * The function must take one parameter, a pointer to a type compatible with the variable.
 * The return value of the function (if any) is ignored.
 *
 * Example:
 * void ptr_clean(int** ptr) { free(*ptr); }
 * int *ptr KATTR_VAR_CLEANUP(ptr_clean) = malloc(sizeof(*ptr) * 100);
 *
 * When ptr will go out of scope ptr_clan will be called. You can use this to implement RAII in C.
 */
#if __has_attribute(cleanup)
#define KATTR_VAR_CLEANUP(func) __attribute__((cleanup(func)))
#else
#define KATTR_VAR_CLEANUP(func)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * The deprecated attribute results in a warning if the variable is used anywhere in the source file.
 * This is useful when identifying variables that are expected to be removed in a future
 * version of a program.
 * The warning also includes the location of the declaration of the deprecated variable,
 * to enable users to easily find further information about why the variable is deprecated,
 *  or what they should do instead.
 * Note that the warning only occurs for uses:
 *
 * extern int old_var __attribute__ ((deprecated));
 * extern int old_var;
 * int new_fn () { return old_var; }
 *
 * results in a warning on line 3 but not line 2.
 */
#if __has_attribute(deprecated)
#define KATTR_VAR_DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#define KATTR_VAR_DEPRECATED(msg)
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * The nonstring variable attribute specifies that an object or member declaration
 * with type array of char, signed char, or unsigned char,
 * or pointer to such a type is intended to store character arrays that do not necessarily
 * contain a terminating NULL.
 * This is useful in detecting uses of such arrays or pointers with functions that
 * expect NULL-terminated strings, and to avoid warnings when such an array
 * or pointer is used as an argument to a bounded string manipulation function such as strncpy.
 * For example, without the attribute, Compiler will issue a warning for the strncpy
 * call below because it may truncate the copy without appending the terminating NULL character.
 * Using the attribute makes it possible to suppress the warning.
 * However, when the array is declared with the attribute the call to strlen is diagnosed
 * because when the array doesn’t contain a NULL-terminated string the call is undefined.
 * To copy, compare, of search non-string character arrays use the memcpy, memcmp, memchr,
 * and other functions that operate on arrays of bytes.
 * In addition, calling strnlen and strndup with such arrays is safe provided a suitable bound
 * is specified, and not diagnosed.
 *
 * Example:
 *
 * struct Data
 * {
 *     char name [32] KATTR_VAR_NONSTRING;
 * };
 *
 * int f (struct Data *pd, const char *s)
 * {
 *     strncpy (pd->name, s, sizeof pd->name);
 *     return strlen (pd->name);   // unsafe, gets a warning
 * }
 *
 */
#if __has_attribute(nonstring)
#define KATTR_VAR_NONSTRING __attribute__((nonstring))
#else
#define KATTR_VAR_NONSTRING
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * The packed attribute specifies that a structure member should have
 * the smallest possible alignment—one bit for a bit-field and one byte otherwise,
 * unless a larger value is specified with the aligned attribute.
 * The attribute does not apply to non-member objects.
 *
 * For example in the structure below, the member array x is packed so that it
 * immediately follows a with no intervening padding:
 *
 * struct foo
 * {
 *     char a;
 *     int x[2] KATTR_VAR_PACKED;
 * };
 */
#if __has_attribute(packed)
#define KATTR_VAR_PACKED __attribute__((packed))
#else
#define KATTR_VAR_PACKED
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * This attribute, attached to a variable, means that the variable is meant to be possibly unused.
 * Compiler does not produce a warning for this variable.
 */
#if __has_attribute(unused)
#define KATTR_VAR_UNUSED __attribute__((unused))
#else
#define KATTR_VAR_UNUSED
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 *
 * This attribute specifies the vector size for the type of the declared variable, measured in bytes.
 * The type to which it applies is known as the base type.
 * The bytes argument must be a positive power-of-two multiple of the base type size.
 * For example, the declaration:
 *
 * int foo KATTR_VAR_VECTOR_SIZE(16);
 *
 * causes the compiler to set the mode for foo, to be 16 bytes, divided into int sized units.
 * Assuming a 32-bit int, foo’s type is a vector of four units of four bytes each,
 * and the corresponding mode of foo is V4SI.
 *
 * This attribute is only applicable to integral and floating scalars,
 * although arrays, pointers, and function return values are allowed in conjunction with this construct.
 *
 * Aggregates with this attribute are invalid,
 * even if they are of the same size as a corresponding scalar.
 * For example, the declaration:
 *
 * struct S { int a; };
 * struct S foo KATTR_VAR_VECTOR_SIZE(16);
 *
 * is invalid even if the size of the structure is the same as the size of the int.
 */
#if __has_attribute(vector_size)
#define KATTR_VAR_VECTOR_SIZE(size) __attribute__((vector_size(size)))
#else
#define KATTR_VAR_VECTOR_SIZE(size) KCOMPILER_ERROR("__attribute__((vector_size)) unsupported"
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Common-Variable-Attributes.html#Common-Variable-Attributes
 *
 * Any data with the noinit attribute will not be initialized by the C runtime startup code,
 * or the program loader.
 * Not initializing data in this way can reduce program startup times.
 * This attribute is specific to ELF targets and relies on the linker to
 * place such data in the right location
 */
#if __has_attribute(noinit)
#define KATTR_VAR_NOINIT __attribute__((noinit))
#else
#define KATTR_VAR_NOINIT
#endif

/**
 * See: https://gcc.gnu.org/onlinedocs/gcc/Statement-Attributes.html#Statement-Attributes
 *
 * The fallthrough attribute with a null statement serves as a fallthrough statement.
 * It hints to the compiler that a statement that falls through to another case label,
 * or user-defined label in a switch statement is intentional and
 * thus the -Wimplicit-fallthrough warning must not trigger.
 * The fallthrough attribute may appear at most once in each attribute list,
 * and may not be mixed with other attributes.
 * It can only be used in a switch statement (the compiler will issue an error otherwise),
 * after a preceding statement and before a logically succeeding case label, or user-defined label
 *
 * If compiler does not supports this, for 99% has not warning implemented. So we can paste empty statement
 *
 */
#if __has_attribute(__fallthrough__)
#define KFALLTRGOUGH_FAKE __attribute__((__fallthrough__))
#else
#define KFALLTRGOUGH_FAKE do { } while (0)
#endif

#else /* #if defined(__has_attribute)  */

#define KATTR_FUNC_ALWAYS_INLINE
#define KATTR_FUNC_CONST
#define KATTR_FUNC_CONSTRUCTOR KCOMPILER_ERROR("__attribute__((constructor)) unsupported")
#define KATTR_FUNC_DESTRUCTOR  KCOMPILER_ERROR("__attribute__((destructor)) unsupported")
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
#define KATTR_VAR_VECTOR_SIZE(size) KCOMPILER_ERROR("__attribute__((vector_size)) unsupported"
#define KATTR_VAR_NOINIT

#define KFALLTRGOUGH_FAKE do { } while (0)

#endif

#endif
