#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <math.h>

#include <kmacros/kmacros.h>

/* FUNCTIONS ATTRIBUTES to show that attributes compiles */
static void before_main(void) KATTR_FUNC_CONSTRUCTOR;
static void before_main(void) { printf("%s\n", __func__); printf("BEFORE MAIN\n"); }

static void after_main(void) KATTR_FUNC_DESTRUCTOR;
static void after_main(void) { printf("%s\n", __func__); printf("AFTER MAIN\n"); }

static inline int finline(void) KATTR_FUNC_ALWAYS_INLINE KATTR_FUNC_UNUSED;
static int finline(void) { return 0; }

static inline int fpure(void) KATTR_FUNC_PURE KATTR_FUNC_UNUSED;
static inline int fpure(void) { return 0; }

static inline int fconst(void) KATTR_FUNC_CONST KATTR_FUNC_UNUSED;
static inline int fconst(void) { return 0; }

static inline int fdeprecated(void) KATTR_FUNC_DEPRECATED("f will be removed") KATTR_FUNC_UNUSED;
static inline int fdeprecated(void) { return 0; }

static int funused(void) KATTR_FUNC_UNUSED;
static int funused(void) { return 0; }

extern int ferrore(void) KATTR_FUNC_ERROR("f has a critical bug");

static inline int my_printf(const char* fmt, ...) KATTR_FUNC_FORMAT_PRINTF(1, 2) KATTR_FUNC_UNUSED;
static inline int my_printf(const char* fmt, ...) { (void)fmt; return 0; }

static inline int my_scanf(const char* fmt, ...) KATTR_FUNC_FORMAT_SCANF(1, 2) KATTR_FUNC_UNUSED;
static inline int my_scanf(const char* fmt, ...) { (void)fmt; return 0; }

static inline int my_strftime(const char* fmt, ...) KATTR_FUNC_FORMAT_STRFTIME(1) KATTR_FUNC_UNUSED;
static inline int my_strftime(const char* fmt, ...) { (void)fmt; return 0; }

static inline int my_strfmon(const char* fmt, ...) KATTR_FUNC_FORMAT_STRFMON(1, 2) KATTR_FUNC_UNUSED;
static inline int my_strfmon(const char* fmt, ...) { (void)fmt; return 0; }

static inline const char* my_fmt_creator(const char* fmt1, const char* fmt2) KATTR_FUNC_FORMAT_ARG(1) KATTR_FUNC_FORMAT_ARG(2) KATTR_FUNC_UNUSED;
static inline const char* my_fmt_creator(const char* fmt1, const char* fmt2) { (void)fmt1; (void)fmt2; return ""; }

static inline void* my_malloc(size_t size) KATTR_FUNC_MALLOC KATTR_FUNC_UNUSED;
static inline void* my_malloc(size_t size) { (void)size; return NULL; }

static inline void *my_memcpy(void *dst, const void *src, size_t size) KATTR_FUNC_NONNULL(1, 2) KATTR_FUNC_UNUSED;
static inline void *my_memcpy(void *dst, const void *src, size_t size) { (void)dst; (void)src; (void)size; return NULL; }

static inline void my_abort(void) KATTR_FUNC_NORETURN KATTR_FUNC_UNUSED;
static inline void my_abort(void) { abort(); }

static inline void f_var_attr(void) KATTR_FUNC_UNUSED;

static inline void int_ptr_destroy(int **ptr) { free(*ptr); }

static inline void f_var_attr(void)
{
    int a KATTR_VAR_ALIGNED(32);
    int *ptr KATTR_VAR_CLEANUP(int_ptr_destroy) = malloc(sizeof(int) * 100);
    double b KATTR_VAR_DEPRECATED("b will be removed soon") KATTR_VAR_UNUSED;
    char c[10] KATTR_VAR_NONSTRING;
    int d KATTR_VAR_VECTOR_SIZE(128);
    static int e KATTR_VAR_NOINIT;

    struct PackedFoo
    {
       char a;
       int x[2] KATTR_VAR_PACKED;
    } foo;

    (void)a;
    (void)ptr;
    // (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)foo;
}

/*************************************************************************************/

extern void test_builtins_impl(void);

static void example_preprocessr_tricks(void);
static void example_compiler_diag(void);
static void example_terminal_colors(void);
static void example_primitives(void);
static void example_builtins(void);
static void example_nargs(void);
static void example_bits(void);
static void example_mask(void);
static void example_common_macros(void);

static void example_for_readme(void);

static void example_preprocessr_tricks(void)
{
    printf("%s\n", __func__);

    #define X 5
    #define Y 10

    printf("%s %s %s\n", KTOSTRING_NAME(X), KTOSTRING(X), KTOSTRING_NAME(a b c));
    printf("%s %s %s\n", KTOSTRING(KCONCAT_NAME(X, Y)), KTOSTRING(KCONCAT(X, Y)), KTOSTRING(KCONCAT(a b, c)));
    printf("%s %s\n", KMACRO_PRINT(X), KMACRO_PRINT(a b));

    #undef X
    #undef Y
}

static void example_compiler_diag(void)
{
    printf("%s\n", __func__);

    KCOMPILER_DIAG_PUSH()
    KCOMPILER_DIAG_WARNING("-Wextra")
    KCOMPILER_DIAG_ERROR("-Wall")
    KCOMPILER_DIAG_IGNORE("-Wuninitialized")
    int x;
    printf("Uninitialized x = %d\n", x);
    KCOMPILER_DIAG_POP()

    // KCOMPILER_WARNING("This is a compile time warning, you can use it inside a macro")
    // KCOMPILER_ERROR("This is a compile time error, you can use it inside a macro")
}

static void example_terminal_colors(void)
{
    printf("%s\n", __func__);

    printf(KTERMINAL_CREATE_FORMATTED_STRING("Formatted string",
                                             KTERMINAL_FONT_COLOR_STR_RED,
                                             KTERMINAL_BG_COLOR_STR_YELLOW,
                                             KTERMINAL_FORMAT_ATTR_STR_BOLD) "\n");

    printf(KTERMINAL_CREATE_COLORFUL_STRING("Only colorful string",
                                             KTERMINAL_FONT_COLOR_STR_GREEN) "\n");

    printf(KTERMINAL_CREATE_COLORFUL_BG_STRING("Colorful string with background",
                                               KTERMINAL_FONT_COLOR_STR_DGRAY,
                                               KTERMINAL_BG_COLOR_STR_LCYAN) "\n");
}

/* A lot to change in code, use macro instead */
#ifdef KCOMPILER_GNUC
#define EXAMPLE_PRIMITIVES_PRINT(var) \
    printf("Type nr: %d (%d), name: %s (%s), pfmt %s (%s), is primitive? %d(%d), probably a pointer? %d(%d)\n", \
           KPRIMITIVES_GET_ENUM_FROM_VAR(var), \
           KPRIMITIVES_GET_ENUM_FROM_TYPE(__typeof__(var)), \
           KPRIMITIVES_GET_NAME_FROM_VAR(var), \
           KPRIMITIVES_GET_NAME_FROM_TYPE(__typeof__(var)), \
           KPRIMITIVES_GET_PFMT_FROM_VAR(var), \
           KPRIMITIVES_GET_PFMT_FROM_TYPE(__typeof__(var)), \
           KPRIMITIVES_VAR_IS_PRIMITIVE(var), \
           KPRIMITIVES_TYPE_IS_PRIMITIVE(__typeof__(var)), \
           KPRIMITIVES_VAR_PROBABLY_POINTER(var), \
           KPRIMITIVES_TYPE_PROBABLY_POINTER(__typeof__(var)) \
          )
#else
    printf("Type nr: %d , name: %s , pfmt %s , is primitive? %d, probably a pointer? %d\n", \
           KPRIMITIVES_GET_ENUM_FROM_VAR(var), \
           KPRIMITIVES_GET_NAME_FROM_VAR(var), \
           KPRIMITIVES_GET_PFMT_FROM_VAR(var), \
           KPRIMITIVES_VAR_IS_PRIMITIVE(var), \
           KPRIMITIVES_VAR_PROBABLY_POINTER(var), \
          )
#endif

static void example_primitives(void)
{
    bool a;
    char b;
    signed char c;
    unsigned char d;
    short e;
    unsigned short f;
    int g;
    unsigned int h;
    long i;
    unsigned long j;
    long long k;
    unsigned long long l;
    float m;
    double n;
    long double o;
    void* p;
    int* r;
    enum {A, B, C} s;
    struct {int a;} t;
    uint16_t u;
    uint32_t w;
    uint64_t x;

    /* gcc thinks that variables are not used, so suppress warnings */
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)g;
    (void)h;
    (void)i;
    (void)j;
    (void)k;
    (void)l;
    (void)m;
    (void)n;
    (void)o;
    (void)p;
    (void)r;
    (void)s;
    (void)t;
    (void)u;
    (void)w;
    (void)x;

    printf("%s\n", __func__);

    EXAMPLE_PRIMITIVES_PRINT(a);
    EXAMPLE_PRIMITIVES_PRINT(b);
    EXAMPLE_PRIMITIVES_PRINT(c);
    EXAMPLE_PRIMITIVES_PRINT(d);
    EXAMPLE_PRIMITIVES_PRINT(e);
    EXAMPLE_PRIMITIVES_PRINT(f);
    EXAMPLE_PRIMITIVES_PRINT(g);
    EXAMPLE_PRIMITIVES_PRINT(h);
    EXAMPLE_PRIMITIVES_PRINT(i);
    EXAMPLE_PRIMITIVES_PRINT(j);
    EXAMPLE_PRIMITIVES_PRINT(k);
    EXAMPLE_PRIMITIVES_PRINT(l);
    EXAMPLE_PRIMITIVES_PRINT(m);
    EXAMPLE_PRIMITIVES_PRINT(n);
    EXAMPLE_PRIMITIVES_PRINT(o);
    EXAMPLE_PRIMITIVES_PRINT(p);
    EXAMPLE_PRIMITIVES_PRINT(r);
    EXAMPLE_PRIMITIVES_PRINT(s);
    EXAMPLE_PRIMITIVES_PRINT(t);
    EXAMPLE_PRIMITIVES_PRINT(u);
    EXAMPLE_PRIMITIVES_PRINT(w);
    EXAMPLE_PRIMITIVES_PRINT(x);
}

static void example_builtins(void)
{
    /* Check only if compiles */
    int a = 10;

    printf("%s\n", __func__);

    if (KEXPECT(a, 10))
        ++a;
    else
        --a;

    if (KEXPECT_PROBABILITY(a, 10, 0.01))
        ++a;
    else
        --a;

    KCHOOSE_EXPRESSION(10 * 0 + 1 == 10, ++a, --a);

    printf("int and unsigned are compatible? %d\n", KTYPES_COMPATIBLE(int, unsigned));
    printf("Value of a is a constant expression? %d\n", KIS_CONSTANT_EXPRESSION(a));

    /* TEST some bit builtins */
    unsigned long x = 0xdeadbeef;
    printf("x = %lx, ffs = %d, clz = %d, ctz = %d, clrsbl = %d, popcount = %d, parity = %d\n",
           x,
           KFFSL((long)x),
           KCLZL(x),
           KCTZL(x),
           KCLRSBL((long)x),
           KPOPCOUNTL(x),
           KPARITYL(x));

    uint32_t y = 0xdeadbeef;
    printf("y = %" PRIx32 ", bswap32 = %" PRIx32 "\n", y, KBSWAP32(y));

    /* KADD / KSUB / KMUL are generic, we can use 1 macro for all types */
    int n = (int)(1u << ((sizeof(n) * CHAR_BIT) - 2)) + 10000;
    int m = (int)(1u << ((sizeof(m) * CHAR_BIT) - 1)) + 100;
    int res;

    printf("%d + %d = %d (overflow? %d)\n"
           "%d - %d = %d (overflow? %d)\n"
           "%d * %d = %d (overflow? %d)\n",
           n, m, n + m, KADD_OVERFLOW(n, m, &res),
           n, m, n - m, KSUB_OVERFLOW(n, m, &res),
           n, m, n * m, KMUL_OVERFLOW(n, m, &res));

    unsigned long long n2 = (1ull << ((sizeof(n2) * CHAR_BIT) - 2)) + 10000;
    unsigned long long m2 = (1ull << ((sizeof(m2) * CHAR_BIT) - 1)) + 100;
    unsigned long long res2;

    printf("%llu + %llu = %llu (overflow? %d)\n"
           "%llu - %llu = %llu (overflow? %d)\n"
           "%llu * %llu = %llu (overflow? %d)\n",
           n2, m2, n2 + m2, KADD_OVERFLOW(n2, m2, &res2),
           n2, m2, n2 - m2, KSUB_OVERFLOW(n2, m2, &res2),
           n2, m2, n2 * m2, KMUL_OVERFLOW(n2, m2, &res2));
}

static void example_nargs(void)
{
    printf("%s\n", __func__);

    /* You can pass mixed values */
    printf("%d args given to macro\n", KNARGS(1, 2, 'c', 10.10, "ala", (void *)0xdeadbeef));

    /* You can also pass tokens (not values nor vars) */
    printf("%d args given to macro\n", KNARGS(a, b, c, d, e, f, g, h, i, j, k, l));

    /* You can paste __VA_ARGS__ from another macro */
#define EXAMPLE_NARGS(...) KNARGS(a, b, c, __VA_ARGS__)
    printf("%d args given to macro\n", EXAMPLE_NARGS(1, 2, 3));
}

static void example_bits(void)
{
    printf("%s\n", __func__);

    short a  = KBIT(7);
    unsigned int b  = KBIT(12);
    long c = KBIT(30);
    unsigned long long d  = KBIT(62);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KBIT_SET(a, 3);
    b = KBIT_SET(b, 3);
    c = KBIT_SET(c, 3);
    d = KBIT_SET(d, 3);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);
    printf("GET 3rd bit: a = %hd, b = %d, c = %ld, d = %lld\n", KBIT_GET(a, 3), KBIT_GET(b, 3), KBIT_GET(c, 3), KBIT_GET(d, 3));
    printf("GET 5th bit: a = %hd, b = %d, c = %ld, d = %lld\n", KBIT_GET(a, 5), KBIT_GET(b, 5), KBIT_GET(c, 5), KBIT_GET(d, 5));

    a = KBIT_CLEAR(a, 7);
    b = KBIT_CLEAR(b, 12);
    c = KBIT_CLEAR(c, 30);
    d = KBIT_CLEAR(d, 62);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KBIT_TOGGLE(a, 5);
    b = KBIT_TOGGLE(b, 5);
    c = KBIT_TOGGLE(c, 5);
    d = KBIT_TOGGLE(d, 5);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KBIT_TOGGLE(a, 5);
    b = KBIT_TOGGLE(b, 5);
    c = KBIT_TOGGLE(c, 5);
    d = KBIT_TOGGLE(d, 5);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);
}

static void example_mask(void)
{
    printf("%s\n", __func__);

    short a  = KMASK(2, 5);
    unsigned int b  = KMASK(7, 12);
    long c = KMASK(10, 30);
    unsigned long long d  = KMASK(50, 62);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KMASK_SET(a, 1, 3);
    b = KMASK_SET(b, 1, 3);
    c = KMASK_SET(c, 1, 3);
    d = KMASK_SET(d, 1, 3);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);
    printf("GET 3rd - 5th bits: a = %hd, b = %d, c = %ld, d = %lld\n", KMASK_GET(a, 3, 5), KMASK_GET(b, 3, 5), KMASK_GET(c, 3, 5), KMASK_GET(d, 3, 5));
    a = KMASK_CLEAR(a, 4, 7);
    b = KMASK_CLEAR(b, 4, 12);
    c = KMASK_CLEAR(c, 8, 30);
    d = KMASK_CLEAR(d, 40, 62);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KMASK_TOGGLE(a, 0, 5);
    b = KMASK_TOGGLE(b, 0, 5);
    c = KMASK_TOGGLE(c, 0, 5);
    d = KMASK_TOGGLE(d, 0, 5);

    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KBIT_REVERSE_SIGNIFICANT(a);
    b = KBIT_REVERSE_SIGNIFICANT(b);
    c = KBIT_REVERSE_SIGNIFICANT(c);
    d = KBIT_REVERSE_SIGNIFICANT(d);
    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    a = KBIT_REVERSE(a);
    b = KBIT_REVERSE(b);
    c = KBIT_REVERSE(c);
    d = KBIT_REVERSE(d);
    printf("a = %hx, b = %x, c = %lx, d = %llx\n", a, b, c, d);

    printf("FFS: a %d b %d c %d d %d\n", KBIT_FFS((int)a), KBIT_FFS(b), KBIT_FFS(c), KBIT_FFS(d));
    printf("CLZ: a %d b %d c %d d %d\n", KBIT_CLZ((int)a), KBIT_CLZ(b), KBIT_CLZ(c), KBIT_CLZ(d));
    printf("CTZ: a %d b %d c %d d %d\n", KBIT_CTZ((int)a), KBIT_CTZ(b), KBIT_CTZ(c), KBIT_CTZ(d));
    printf("CLRSB: a %d b %d c %d d %d\n", KBIT_CLRSB((int)a), KBIT_CLRSB(b), KBIT_CLRSB(c), KBIT_CLRSB(d));
    printf("POPCOUNT: a %d b %d c %d d %d\n", KBIT_POPCOUNT((int)a), KBIT_POPCOUNT(b), KBIT_POPCOUNT(c), KBIT_POPCOUNT(d));
    printf("PARITY: a %d b %d c %d d %d\n", KBIT_PARITY((int)a), KBIT_PARITY(b), KBIT_PARITY(c), KBIT_PARITY(d));
}

static void example_common_macros(void)
{
    printf("%s\n", __func__);

    volatile int fall = 3;
    switch (fall)
    {
        case 1: printf("fall >= 1\n"); KFALLTRGOUGH_FAKE;
        case 2: printf("fall >= 2\n"); KFALLTRGOUGH_FAKE;
        case 3: printf("fall >= 3\n"); KFALLTRGOUGH_FAKE;
        default: printf("fall = %d\n", fall);
    }

    KSTATIC_ASSERT_MSG(1, "Assert 1");
    KSTATIC_ASSERT(1);

    int t[10];
    printf("LEN t[10] = %zu\n", KARRAY_SIZE(t));
    int *ptr = malloc(100 * sizeof(*ptr));
    KFREE(ptr);

    KUNUSED_RETVAL(printf("Dummy print\n"));

    printf("Bool from {-1, 10, 0} = {%d, %d, %d}\n", KCAST_TO_BOOL(-1), KCAST_TO_BOOL(10), KCAST_TO_BOOL(0));

    volatile int x = 0;
    volatile int y = 0;
    if (KLIKELY(x == y))
        printf("Likely x == y\n");
    else
        printf("Incorrect Likely x == y\n");

    y = 1;
    if (KUNLIKELY(x == y))
        printf("Incorrect Unlikely x == y\n");
    else
        printf("Unlikely x == y\n");

    printf("Almost unique name from x = %s\n", KTOSTRING(KVAR_ALMOST_UNIQUE_NAME(x)));

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

    KPRINT_PRETTY("pretty Void print\n");
    KPRINT_PRETTY("pretty x = %d, y = %d\n",x ,y);

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

    unsigned int a = 1;
    unsigned int b = 10;
    unsigned long c = 32;
    unsigned long long d = 0;

    printf("%u is 2^k? %d\n", a, KIS_POWER2(a));
    printf("%u is 2^k? %d\n", b, KIS_POWER2(b));
    printf("%lu is 2^k? %d\n", c, KIS_POWER2(c));
    printf("%llu is 2^k? %d\n", d, KIS_POWER2(d));

    printf("floor(log2(%u)) = %d, ceil(log2(%u)) = %d\n", a, KLOG2_FLOOR(a), a, KLOG2_CEIL(a));
    printf("floor(log2(%u)) = %d, ceil(log2(%u)) = %d\n", b, KLOG2_FLOOR(b), b, KLOG2_CEIL(b));
    printf("floor(log2(%lu)) = %ld, ceil(log2(%lu)) = %ld\n", c, KLOG2_FLOOR(c), c, KLOG2_CEIL(c));
    printf("floor(log2(%llu)) = %lld, ceil(log2(%llu)) = %lld\n", d, KLOG2_FLOOR(d), d, KLOG2_CEIL(d));

    printf("roundUp(%u) = %u, roundDown(%u) = %u, allign(%u) = %u\n", a, KROUND_POWER2_UP(a), a, KROUND_POWER2_DOWN(a), a, KALLIGN_POWER2(a));
    printf("roundUp(%u) = %u, roundDown(%u) = %u, allign(%u) = %u\n", b, KROUND_POWER2_UP(b), b, KROUND_POWER2_DOWN(b), b, KALLIGN_POWER2(b));
    printf("roundUp(%lu) = %lu, roundDown(%lu) = %lu, allign(%lu) = %lu\n", c, KROUND_POWER2_UP(c), c, KROUND_POWER2_DOWN(c), c, KALLIGN_POWER2(c));
    printf("roundUp(%llu) = %llu, roundDown(%llu) = %llu, allign(%llu) = %llu\n", d, KROUND_POWER2_UP(d), d, KROUND_POWER2_DOWN(d), d, KALLIGN_POWER2(d));

    printf("MIN(%d %d %d) = %d\n", 100, 50, -100, KMIN(100, 50, -100));
    printf("MIN(%lf %lf %lf %lf %lf) = %lf\n", 0.2, 50.1, -1323.1312, -100.11, 0.0, KMIN(0.2, 50.1, -1323.1312, -100.11, 0.0));

    printf("MAX(%d %d %d) = %d\n", 100, 50, -100, KMAX(100, 50, -100));
    printf("MAX(%lf %lf %lf %lf %lf) = %lf\n", 0.2, 50.1, -1323.1312, -100.11, 0.0, KMAX(0.2, 50.1, -1323.1312, -100.11, 0.0));
}

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
    example_preprocessr_tricks();
    example_compiler_diag();
    example_terminal_colors();
    example_primitives();
    example_builtins();
    example_nargs();
    example_bits();
    example_mask();
    example_common_macros();

    test_builtins_impl();

    // fdeprecated();
    // ferrore();

    example_for_readme();

    return 0;
}
