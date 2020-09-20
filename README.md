# KMacros - Kukos's common useful macros

This library is simple as can. There is no source code to compile. There is no static or shared library to link.
KMacros is a powerful and useful set of common macros independent of compilers and C dialect. Library is detecting your compiler (for now clang and gcc are in 100% supported) and your C dialect and using the best version of macro / function.

This library has been created with 0 abstraction cost property. So you have more abstraction layers in your code by using this library. But runtime performance is the same as using simple macros without detecting compilers.

### Getting started:
Before you use this code I suggest to see, compile and play with examples which can be found in this repo (example directory)

To compile examples type:

````
$make all
````

or

````
$make example
````

## Features
* Preprocessor - macros like concat and tostring
* Nargs - macro to calculate number of params in vaargs macro
* Primitives - framework to detect variable type (primitives like int, short, double)
* Bits - functions and macros for single bits and mask
* Builtins - a lot of builtins from gcc and clang under macros. When compiler does not support builtin then simple implementation is used (inline function)
* Compiler - detecting compiler, detecting compiler dialect and also macros with compiler diagnostisc like ignoring warnings or adding another
* Attributes - a lot of functions and variables attributes supported by compiler. Library can auto detect attribute support and enable or disable code under macro
* Common macros - set of useful and powerful macros. Like getting array length (not dynamic array), calculating log2 from integers, 100% safe swap.

## Platforms
For now KMacros has been tested only on Linux.

## Requirements
* Compiler with at least C11 standard
* Makefile

## How to build

You can type make help to get list of all targets:
````
KMacros Makefile

Targets:
    all               - build examples
    examples          - build examples
    install[P = Path] - install kmacros to path P or default Path

Makefile supports Verbose mode when V=1
To check default compiler (gcc) change CC variable (i.e export CC=clang)
````
## How to install
To install KMacros on your computer you can use

````
make install [P=path]
````
or you can execute script directly from

````
scripts/install_kmacros.sh [P=path]
````

Let's assume that you have your project MyProject and directories as follows:
```
.
├── app
├── external
├── inc
├── src
└── tests
````

You want to install KMacros in external/Kmacros directory and use it in your unit tests under tests directory.

````
1. Download this repo
2. $make install P=/home/$user/MyProject/external/Kmacros
3. Add path to headers. To compiler options add -I/home/$user/MyProject/external/Kmacros/inc
4. In your files you need include main header: #include <kmacros/kmacros.h>
5. Write your code and enjoy! Please see examples for details.
````



## Example
Code below shows only a 10-20% macros from library.
I suggest to compile full examples and play with them before you will start using this library.

````c
#include <kmacros/kmacros.h>
static void before_main(void) KATTR_FUNC_CONSTRUCTOR;
static void before_main(void) { printf("%s\n", __func__); printf("BEFORE MAIN\n"); }

static void after_main(void) KATTR_FUNC_DESTRUCTOR;
static void after_main(void) { printf("%s\n", __func__); printf("AFTER MAIN\n"); }

static inline void* my_malloc(size_t size) KATTR_FUNC_MALLOC KATTR_FUNC_UNUSED;
static inline void* my_malloc(size_t size) { (void)size; return NULL; }

static void example_for_readme(void);
static void example_for_readme(void)
{
    printf("Examples to README\n");

    /* Some preprocessor tricks */
    #define X 5
    #define Y 10

    printf("%s %s %s\n", KTOSTRING_NAME(X), KTOSTRING(X), KTOSTRING_NAME(a b c));
    printf("%s %s %s\n", KTOSTRING(KCONCAT_NAME(X, Y)), KTOSTRING(KCONCAT(X, Y)), KTOSTRING(KCONCAT(a b, c)));
    printf("%s %s\n", KMACRO_PRINT(X), KMACRO_PRINT(a b));

    #undef X
    #undef Y

    /* You can check type compatibility without error, this will return false / true */
    printf("int and unsigned are compatible? %d\n", KTYPES_COMPATIBLE(int, unsigned));

    int a = 10 * 10;
    /* Always we can check if expression is known in compile time */
    printf("Value of a is a constant expression? %d\n", KIS_CONSTANT_EXPRESSION(a));

    /* primitive bitwise operations */
    long b = 0x31;
    printf("b = %lx, set(2) = %lx, clear(5) = %lx, get(1) = %lx, toggle(4) = %lx, ReverseSignificant(b) = %lx, Reverse(b) = %lx\n",
           b,
           KBIT_SET(b, 2),
           KBIT_CLEAR(b, 5),
           KBIT_GET(b, 1),
           KBIT_TOGGLE(b, 4),
           KBIT_REVERSE_SIGNIFICANT(b),
           KBIT_REVERSE(b));

    /* KMacros has set of advanced bitwise operation */
    unsigned long c = 0xdeadbeef;
    printf("c = %lx, ffs = %d, clz = %d, ctz = %d, clrsbl = %d, popcount = %d, parity = %d\n",
           c,
           KFFSL((long)c),
           KCLZL(c),
           KCTZL(c),
           KCLRSBL((long)c),
           KPOPCOUNTL(c),
           KPARITYL(c));

    uint32_t d = 0xdeadbeef;
    printf("d = %" PRIx32 ", bswap32 = %" PRIx32 "\n", d, KBSWAP32(d));

    /* KADD / KSUB / KMUL are generic, we can use 1 macro for all types */
    int e = (int)(1u << ((sizeof(e) * CHAR_BIT) - 2)) + 10000;
    int f = (int)(1u << ((sizeof(f) * CHAR_BIT) - 1)) + 100;
    int res;

    /* Macros will return value by out paramater and return in retval overflow status */
    printf("%d + %d = %d (overflow? %d)\n"
           "%d - %d = %d (overflow? %d)\n"
           "%d * %d = %d (overflow? %d)\n",
           e, f, e + f, KADD_OVERFLOW(e, f, &res),
           e, f, e - f, KSUB_OVERFLOW(e, f, &res),
           e, f, e * f, KMUL_OVERFLOW(e, f, &res));

    /* When you will use g then message will be printed with warning */
    double g KATTR_VAR_DEPRECATED("g will be removed soon") KATTR_VAR_UNUSED;

    /* h is uninitializaed, but we want to supress warning not to fix it */
    KCOMPILER_DIAG_PUSH()
    KCOMPILER_DIAG_IGNORE("-Wuninitialized")
    int h;
    printf("Uninitialized h = %d\n", h);
    KCOMPILER_DIAG_POP()

    /* KPRIMITIVE is a powerful interface to check some type chracteristic in compile time */
    long double var = (long double)0.0;
    (void)var;
    printf("Type nr: %d (%d), name: %s (%s), pfmt %s (%s), is primitive? %d(%d), probably a pointer? %d(%d)\n", \
           KPRIMITIVES_GET_ENUM_FROM_VAR(var), \
           KPRIMITIVES_GET_ENUM_FROM_TYPE(long double), \
           KPRIMITIVES_GET_NAME_FROM_VAR(var), \
           KPRIMITIVES_GET_NAME_FROM_TYPE(long double), \
           KPRIMITIVES_GET_PFMT_FROM_VAR(var), \
           KPRIMITIVES_GET_PFMT_FROM_TYPE(long double), \
           KPRIMITIVES_VAR_IS_PRIMITIVE(var), \
           KPRIMITIVES_TYPE_IS_PRIMITIVE(long double), \
           KPRIMITIVES_VAR_PROBABLY_POINTER(var), \
           KPRIMITIVES_TYPE_PROBABLY_POINTER(long double) \
          );

    /* KMacros have advanced macros for memory manipulation (write / read/ swap) */
    struct Member
    {
        int a;
        int b;
    };

    struct Base
    {
        int a;
        struct Member b;
        int c;
    };

    struct Base base = {.a = 10, .b = {.a = 100, .b = 200}, .c = 30};
    struct Member* member_ptr = &base.b;
    struct Base* base_ptr = KCONTAINER_OF(member_ptr, struct Base, b);
    printf("Base = {%d {%d %d} %d}, base_ptr = {%d {%d %d} %d}\n",
           base.a, base.b.a, base.b.b, base.c,
           base_ptr->a, base_ptr->b.a, base_ptr->b.b, base_ptr->c);

    struct Base base2 = {0};
    KWRITE_VAR(base2, base);
    printf("Base = {%d {%d %d} %d}, Base2 = {%d {%d %d} %d}\n",
           base.a, base.b.a, base.b.b, base.c,
           base2.a, base2.b.a, base2.b.b, base2.c);

    struct Member m1 = {.a = 1, .b = 2};
    struct Member m2 = {0};
    KWRITE_PTR(&m2, &m1);
    printf("Member = {%d %d}, Member2 = {%d %d}\n", m1.a, m1.b, m2.a, m2.b);

    char base_buf[sizeof(struct Base)] = {"Ala ma kota"};
    KWRITE_SIZE_VAR(base2, base_buf, sizeof(base2));
    printf("Base2 = {%d {%d %d} %d}\n", base2.a, base2.b.a, base2.b.b, base2.c);

    struct Member m3 = {.a = 1, .b = 2};
    struct Member m4 = {.a = 4, .b = 5};
    printf("Member3 = {%d %d}, Member4 = {%d %d}\n", m3.a, m3.b, m4.a, m4.b);
    KSWAP(m3, m4);
    printf("Member3 = {%d %d}, Member4 = {%d %d}\n", m3.a, m3.b, m4.a, m4.b);

    /* Fast macros to compute some power2, log, round, align */
    unsigned int n = 10;
    printf("%u is 2^k? %d\n", n, KIS_POWER2(n));
    printf("floor(log2(%u)) = %d, ceil(log2(%u)) = %d\n", n, KLOG2_FLOOR(n), n, KLOG2_CEIL(n));
    printf("roundUp(%u) = %u, roundDown(%u) = %u, allign(%u) = %u\n", n, KROUND_POWER2_UP(n), n, KROUND_POWER2_DOWN(n), n, KALLIGN_POWER2(n));

    /* Advanced MIN & MAX macros supports from 2 to 5 params. 100% safe (type checking, i++ protection) */
    printf("MIN(%d %d %d) = %d\n", 100, 50, -100, KMIN(100, 50, -100));
    printf("MIN(%lf %lf %lf %lf %lf) = %lf\n", 0.2, 50.1, -1323.1312, -100.11, 0.0, KMIN(0.2, 50.1, -1323.1312, -100.11, 0.0));

    printf("MAX(%d %d %d) = %d\n", 100, 50, -100, KMAX(100, 50, -100));
    printf("MAX(%lf %lf %lf %lf %lf) = %lf\n", 0.2, 50.1, -1323.1312, -100.11, 0.0, KMAX(0.2, 50.1, -1323.1312, -100.11, 0.0));
}

int main(void)
{
    example_for_readme();

    return 0;
}

/*
OUTPUT

before_main
BEFORE MAIN
Examples to README
X 5 a b c
XY 510 a bc
X = 5 a b = a b
int and unsigned are compatible? 0
Value of a is a constant expression? 1
b = 31, set(2) = 35, clear(5) = 11, get(1) = 0, toggle(4) = 21, ReverseSignificant(b) = 23, Reverse(b) = 8c00000000000000
c = deadbeef, ffs = 1, clz = 32, ctz = 0, clrsbl = 31, popcount = 24, parity = 0
d = deadbeef, bswap32 = efbeadde
1073751824 + -2147483548 = -1073731724 (overflow? 0)
1073751824 - -2147483548 = -1073731924 (overflow? 1)
1073751824 * -2147483548 = 1000000 (overflow? 1)
Uninitialized h = 0
Type nr: 14 (14), name: long double (long double), pfmt %Lf (%Lf), is primitive? 1(1), probably a pointer? 0(0)
Base = {10 {100 200} 30}, base_ptr = {10 {100 200} 30}
Base = {10 {100 200} 30}, Base2 = {10 {100 200} 30}
Member = {1 2}, Member2 = {1 2}
Base2 = {543255617 {1797284205 6386799} 0}
Member3 = {1 2}, Member4 = {4 5}
Member3 = {4 5}, Member4 = {1 2}
10 is 2^k? 0
floor(log2(10)) = 3, ceil(log2(10)) = 4
roundUp(10) = 16, roundDown(10) = 8, allign(10) = 16
MIN(100 50 -100) = -100
MIN(0.200000 50.100000 -1323.131200 -100.110000 0.000000) = -1323.131200
MAX(100 50 -100) = 100
MAX(0.200000 50.100000 -1323.131200 -100.110000 0.000000) = 50.100000
after_main
AFTER MAIN
*/
````

#### Contact
email: michalkukowski10@gmail.com
