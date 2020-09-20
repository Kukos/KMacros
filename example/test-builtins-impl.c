#include <kmacros/kmacros.h>

void test_builtins_impl(void);

#if defined(KCOMPILER_GCC) || defined(KCOMPILER_CLANG)

#include <assert.h>

static void test_only_compiling_builtins(void);
static void test_ffs(void);
static void test_clz(void);
static void test_ctz(void);
static void test_clrsb(void);
static void test_popcount(void);
static void test_parity(void);
static void test_bswap(void);
static void test_overflow(void);

static void test_only_compiling_builtins(void)
{
    if (kbuiltin_expect_impl(10, 11))
        assert(10 == 11);

    if (kbuiltin_expect_with_probability_impl(10, 11, 0.5))
        assert(10 == 11);

    int x = kbuiltin_choose_expr_impl(10 == 11, 10, 11);
    assert(x == 11);

    assert(kbuiltin_types_compatible_p_impl(int , int) == true);
    assert(kbuiltin_types_compatible_p_impl(int *, int) == false);
    assert(kbuiltin_types_compatible_p_impl(double, long) == false);
    assert(kbuiltin_types_compatible_p_impl(float, const volatile float) == true);
    typedef int weird_int;
    assert(kbuiltin_types_compatible_p_impl(weird_int, int) == true);

    /* We cannot implement it, so always we are assuming that expr is not const */
    assert(kbuiltin_constant_p_impl(10) == 0);
    assert(kbuiltin_constant_p_impl(x) == 0);
}

static void test_ffs(void)
{
    int x;

    x = 0;
    assert(__builtin_ffs(x) == kbuiltin_ffs_impl(x));

    x = 121;
    assert(__builtin_ffs(x) == kbuiltin_ffs_impl(x));

    x = -1;
    assert(__builtin_ffs(x) == kbuiltin_ffs_impl(x));

    x = (int)(unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_ffs(x) == kbuiltin_ffs_impl(x));

    long y;

    y = 0;
    assert(__builtin_ffsl(y) == kbuiltin_ffsl_impl(y));

    y = 121;
    assert(__builtin_ffsl(y) == kbuiltin_ffsl_impl(y));

    y = -1;
    assert(__builtin_ffsl(y) == kbuiltin_ffsl_impl(y));

    y = (long)(unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_ffsl(y) == kbuiltin_ffsl_impl(y));

    long long z;

    z = 0;
    assert(__builtin_ffsll(z) == kbuiltin_ffsll_impl(z));

    z = 121;
    assert(__builtin_ffsll(z) == kbuiltin_ffsll_impl(z));

    z = -1;
    assert(__builtin_ffsll(z) == kbuiltin_ffsll_impl(z));

    z = (long long)(unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_ffsll(z) == kbuiltin_ffsll_impl(z));
}

static void test_clz(void)
{
    unsigned int x;

    x = 1;
    assert(__builtin_clz(x) == kbuiltin_clz_impl(x));

    x = 121;
    assert(__builtin_clz(x) == kbuiltin_clz_impl(x));

    x = (unsigned)-1;
    assert(__builtin_clz(x) == kbuiltin_clz_impl(x));

    x = (unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_clz(x) == kbuiltin_clz_impl(x));

    unsigned long y;

    y = 1;
    assert(__builtin_clzl(y) == kbuiltin_clzl_impl(y));

    y = 121;
    assert(__builtin_clzl(y) == kbuiltin_clzl_impl(y));

    y = (unsigned long)-1;
    assert(__builtin_clzl(y) == kbuiltin_clzl_impl(y));

    y = (unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_clzl(y) == kbuiltin_clzl_impl(y));

    unsigned long long z;

    z = 1;
    assert(__builtin_clzll(z) == kbuiltin_clzll_impl(z));

    z = 121;
    assert(__builtin_clzll(z) == kbuiltin_clzll_impl(z));

    z = (unsigned long long)-1;
    assert(__builtin_clzll(z) == kbuiltin_clzll_impl(z));

    z = (unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_clzll(z) == kbuiltin_clzll_impl(z));
}

static void test_ctz(void)
{
    unsigned int x;

    x = 1;
    assert(__builtin_ctz(x) == kbuiltin_ctz_impl(x));

    x = 121;
    assert(__builtin_ctz(x) == kbuiltin_ctz_impl(x));

    x = (unsigned)-1;
    assert(__builtin_ctz(x) == kbuiltin_ctz_impl(x));

    x = (unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_ctz(x) == kbuiltin_ctz_impl(x));

    unsigned long y;

    y = 1;
    assert(__builtin_ctzl(y) == kbuiltin_ctzl_impl(y));

    y = 121;
    assert(__builtin_ctzl(y) == kbuiltin_ctzl_impl(y));

    y = (unsigned long)-1;
    assert(__builtin_ctzl(y) == kbuiltin_ctzl_impl(y));

    y = (unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_ctzl(y) == kbuiltin_ctzl_impl(y));

    unsigned long long z;

    z = 1;
    assert(__builtin_ctzll(z) == kbuiltin_ctzll_impl(z));

    z = 121;
    assert(__builtin_ctzll(z) == kbuiltin_ctzll_impl(z));

    z = (unsigned long long)-1;
    assert(__builtin_ctzll(z) == kbuiltin_ctzll_impl(z));

    z = (unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_ctzll(z) == kbuiltin_ctzll_impl(z));
}

static void test_clrsb(void)
{
    int x;

    x = 0;
    assert(__builtin_clrsb(x) == kbuiltin_clrsb_impl(x));

    x = 121;
    assert(__builtin_clrsb(x) == kbuiltin_clrsb_impl(x));

    x = -1;
    assert(__builtin_clrsb(x) == kbuiltin_clrsb_impl(x));

    x = (int)(unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_clrsb(x) == kbuiltin_clrsb_impl(x));

    long y;

    y = 0;
    assert(__builtin_clrsbl(y) == kbuiltin_clrsbl_impl(y));

    y = 121;
    assert(__builtin_clrsbl(y) == kbuiltin_clrsbl_impl(y));

    y = -1;
    assert(__builtin_clrsbl(y) == kbuiltin_clrsbl_impl(y));

    y = (long)(unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_clrsbl(y) == kbuiltin_clrsbl_impl(y));

    long long z;

    z = 0;
    assert(__builtin_clrsbll(z) == kbuiltin_clrsbll_impl(z));

    z = 121;
    assert(__builtin_clrsbll(z) == kbuiltin_clrsbll_impl(z));

    z = -1;
    assert(__builtin_clrsbll(z) == kbuiltin_clrsbll_impl(z));

    z = (long long)(unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_clrsbll(z) == kbuiltin_clrsbll_impl(z));
}

static void test_popcount(void)
{
    unsigned int x;

    x = 1;
    assert(__builtin_popcount(x) == kbuiltin_popcount_impl(x));

    x = 121;
    assert(__builtin_popcount(x) == kbuiltin_popcount_impl(x));

    x = (unsigned)-1;
    assert(__builtin_popcount(x) == kbuiltin_popcount_impl(x));

    x = (unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_popcount(x) == kbuiltin_popcount_impl(x));

    unsigned long y;

    y = 1;
    assert(__builtin_popcountl(y) == kbuiltin_popcountl_impl(y));

    y = 121;
    assert(__builtin_popcountl(y) == kbuiltin_popcountl_impl(y));

    y = (unsigned long)-1;
    assert(__builtin_popcountl(y) == kbuiltin_popcountl_impl(y));

    y = (unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_popcountl(y) == kbuiltin_popcountl_impl(y));

    unsigned long long z;

    z = 1;
    assert(__builtin_popcountll(z) == kbuiltin_popcountll_impl(z));

    z = 121;
    assert(__builtin_popcountll(z) == kbuiltin_popcountll_impl(z));

    z = (unsigned long long)-1;
    assert(__builtin_popcountll(z) == kbuiltin_popcountll_impl(z));

    z = (unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_popcountll(z) == kbuiltin_popcountll_impl(z));
}

static void test_parity(void)
{
    unsigned int x;

    x = 1;
    assert(__builtin_parity(x) == kbuiltin_parity_impl(x));

    x = 121;
    assert(__builtin_parity(x) == kbuiltin_parity_impl(x));

    x = (unsigned)-1;
    assert(__builtin_parity(x) == kbuiltin_parity_impl(x));

    x = (unsigned)(1u << ((sizeof(x) * CHAR_BIT) - 1));
    assert(__builtin_parity(x) == kbuiltin_parity_impl(x));

    unsigned long y;

    y = 1;
    assert(__builtin_parityl(y) == kbuiltin_parityl_impl(y));

    y = 121;
    assert(__builtin_parityl(y) == kbuiltin_parityl_impl(y));

    y = (unsigned long)-1;
    assert(__builtin_parityl(y) == kbuiltin_parityl_impl(y));

    y = (unsigned long)(1ul << ((sizeof(y) * CHAR_BIT) - 1));
    assert(__builtin_parityl(y) == kbuiltin_parityl_impl(y));

    unsigned long long z;

    z = 1;
    assert(__builtin_parityll(z) == kbuiltin_parityll_impl(z));

    z = 121;
    assert(__builtin_parityll(z) == kbuiltin_parityll_impl(z));

    z = (unsigned long long)-1;
    assert(__builtin_parityll(z) == kbuiltin_parityll_impl(z));

    z = (unsigned long long)(1ull << ((sizeof(z) * CHAR_BIT) - 1));
    assert(__builtin_parityll(z) == kbuiltin_parityll_impl(z));
}

static void test_bswap(void)
{
    uint16_t x;

    x = 0;
    assert(__builtin_bswap16(x) == kbuiltin_bswap16_impl(x));

    x = 0xABCD;
    assert(__builtin_bswap16(x) == kbuiltin_bswap16_impl(x));

    x = 0xABBA;
    assert(__builtin_bswap16(x) == kbuiltin_bswap16_impl(x));

    uint32_t y;

    y = 0;
    assert(__builtin_bswap32(y) == kbuiltin_bswap32_impl(y));

    y = 0x12345678;
    assert(__builtin_bswap32(y) == kbuiltin_bswap32_impl(y));

    y = 0xABABBABA;
    assert(__builtin_bswap32(y) == kbuiltin_bswap32_impl(y));

    uint64_t z;

    z = 0;
    assert(__builtin_bswap64(z) == kbuiltin_bswap64_impl(z));

    z = 0x0123456789ABCDEF;
    assert(__builtin_bswap64(z) == kbuiltin_bswap64_impl(z));

    z = 0xABABABABBABABABA;
    assert(__builtin_bswap64(z) == kbuiltin_bswap64_impl(z));
}

#if defined(KCOMPILER_CLANG) || (defined(KCOMPILER_GCC) && (defined(__x86_64__) || defined(__i386__)))

static void test_overflow_addi(void);
static void test_overflow_addu(void);
static void test_overflow_addl(void);
static void test_overflow_addul(void);
static void test_overflow_addll(void);
static void test_overflow_addull(void);
static void test_overflow_add_generic(void);

static void test_overflow_subi(void);
static void test_overflow_subu(void);
static void test_overflow_subl(void);
static void test_overflow_subul(void);
static void test_overflow_subll(void);
static void test_overflow_subull(void);
static void test_overflow_sub_generic(void);

static void test_overflow_muli(void);
static void test_overflow_mulu(void);
static void test_overflow_mull(void);
static void test_overflow_mulul(void);
static void test_overflow_mulll(void);
static void test_overflow_mulull(void);
static void test_overflow_mul_generic(void);

static void test_overflow_addi(void)
{
    int x;
    int y;
    int res_built;
    int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_sadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_sadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_sadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_sadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_sadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_addu(void)
{
    unsigned int x;
    unsigned int y;
    unsigned int res_built;
    unsigned int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_uadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uadd_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uadd_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_addl(void)
{
    long x;
    long y;
    long res_built;
    long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_saddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_saddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_saddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_saddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_saddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_addul(void)
{
    unsigned long x;
    unsigned long y;
    unsigned long res_built;
    unsigned long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_uaddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uaddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uaddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uaddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uaddl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_addll(void)
{
    long long x;
    long long y;
    long long res_built;
    long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_saddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_saddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_saddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_saddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_saddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_saddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_addull(void)
{
    unsigned long long x;
    unsigned long long y;
    unsigned long long res_built;
    unsigned long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_uaddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uaddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uaddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_uaddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_uaddll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_uaddll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_add_generic(void)
{
    bool overflow_built;
    bool overflow_impl;

    int x = 10;
    int y = 1 << 10;
    int res_built;
    int res_impl;
    overflow_built = __builtin_add_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_add_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    long x2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 10000;
    long y2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 100;
    long res_built2;
    long res_impl2;
    overflow_built = __builtin_add_overflow(x2, y2, &res_built2);
    overflow_impl = kbuiltin_add_overflow_impl(x2, y2, &res_impl2);

    assert(overflow_built == overflow_impl);
    assert(res_built2 == res_impl2);

    long long x3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 10000;
    long long y3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 100;
    long long res_built3;
    long long res_impl3;
    overflow_built = __builtin_add_overflow(x3, y3, &res_built3);
    overflow_impl = kbuiltin_add_overflow_impl(x3, y3, &res_impl3);

    assert(overflow_built == overflow_impl);
    assert(res_built3 == res_impl3);

    unsigned x4 = (1u << ((sizeof(x4) * CHAR_BIT) - 2)) + 10000;
    unsigned y4 = (1u << ((sizeof(x4) * CHAR_BIT) - 1)) + 100;
    unsigned res_built4;
    unsigned res_impl4;
    overflow_built = __builtin_add_overflow(x4, y4, &res_built4);
    overflow_impl = kbuiltin_add_overflow_impl(x4, y4, &res_impl4);

    assert(overflow_built == overflow_impl);
    assert(res_built4 == res_impl4);

    unsigned long x5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 1)) + 10000;
    unsigned long y5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 2)) + 100;
    unsigned long res_built5;
    unsigned long res_impl5;
    overflow_built = __builtin_add_overflow(x5, y5, &res_built5);
    overflow_impl = kbuiltin_add_overflow_impl(x5, y5, &res_impl5);

    assert(overflow_built == overflow_impl);
    assert(res_built5 == res_impl5);

    unsigned long long x6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 4)) + 10000;
    unsigned long long y6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 1)) + 100;
    unsigned long long res_built6;
    unsigned long long res_impl6;
    overflow_built = __builtin_add_overflow(x6, y6, &res_built6);
    overflow_impl = kbuiltin_add_overflow_impl(x6, y6, &res_impl6);

    assert(overflow_built == overflow_impl);
    assert(res_built6 == res_impl6);
}

static void test_overflow_subi(void)
{
    int x;
    int y;
    int res_built;
    int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_ssub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_subu(void)
{
    unsigned int x;
    unsigned int y;
    unsigned int res_built;
    unsigned int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_usub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_subl(void)
{
    long x;
    long y;
    long res_built;
    long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_ssubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_subul(void)
{
    unsigned long x;
    unsigned long y;
    unsigned long res_built;
    unsigned long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_usubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usubl_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubl_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_subll(void)
{
    long long x;
    long long y;
    long long res_built;
    long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_ssubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_ssubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_ssubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_ssubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_subull(void)
{
    unsigned long long x;
    unsigned long long y;
    unsigned long long res_built;
    unsigned long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_usubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_usubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_usubll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_usubll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_sub_generic(void)
{
    bool overflow_built;
    bool overflow_impl;

    int x = 10;
    int y = 1 << 10;
    int res_built;
    int res_impl;
    overflow_built = __builtin_sub_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_sub_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    long x2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 10000;
    long y2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 100;
    long res_built2;
    long res_impl2;
    overflow_built = __builtin_sub_overflow(x2, y2, &res_built2);
    overflow_impl = kbuiltin_sub_overflow_impl(x2, y2, &res_impl2);

    assert(overflow_built == overflow_impl);
    assert(res_built2 == res_impl2);

    long long x3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 10000;
    long long y3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 100;
    long long res_built3;
    long long res_impl3;
    overflow_built = __builtin_sub_overflow(x3, y3, &res_built3);
    overflow_impl = kbuiltin_sub_overflow_impl(x3, y3, &res_impl3);

    assert(overflow_built == overflow_impl);
    assert(res_built3 == res_impl3);

    unsigned x4 = (1u << ((sizeof(x4) * CHAR_BIT) - 2)) + 10000;
    unsigned y4 = (1u << ((sizeof(x4) * CHAR_BIT) - 1)) + 100;
    unsigned res_built4;
    unsigned res_impl4;
    overflow_built = __builtin_sub_overflow(x4, y4, &res_built4);
    overflow_impl = kbuiltin_sub_overflow_impl(x4, y4, &res_impl4);

    assert(overflow_built == overflow_impl);
    assert(res_built4 == res_impl4);

    unsigned long x5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 1)) + 10000;
    unsigned long y5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 2)) + 100;
    unsigned long res_built5;
    unsigned long res_impl5;
    overflow_built = __builtin_sub_overflow(x5, y5, &res_built5);
    overflow_impl = kbuiltin_sub_overflow_impl(x5, y5, &res_impl5);

    assert(overflow_built == overflow_impl);
    assert(res_built5 == res_impl5);

    unsigned long long x6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 4)) + 10000;
    unsigned long long y6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 1)) + 100;
    unsigned long long res_built6;
    unsigned long long res_impl6;
    overflow_built = __builtin_sub_overflow(x6, y6, &res_built6);
    overflow_impl = kbuiltin_sub_overflow_impl(x6, y6, &res_impl6);

    assert(overflow_built == overflow_impl);
    assert(res_built6 == res_impl6);
}

static void test_overflow_muli(void)
{
    int x;
    int y;
    int res_built;
    int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_smul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (int)(1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (int)(1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mulu(void)
{
    unsigned int x;
    unsigned int y;
    unsigned int res_built;
    unsigned int res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_umul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1u << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1u << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mull(void)
{
    long x;
    long y;
    long res_built;
    long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_smull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long)(1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mulul(void)
{
    unsigned long x;
    unsigned long y;
    unsigned long res_built;
    unsigned long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_umull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ul << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ul << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umull_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umull_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mulll(void)
{
    long long x;
    long long y;
    long long res_built;
    long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_smulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_smulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (long long)(1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_smulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_smulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mulull(void)
{
    unsigned long long x;
    unsigned long long y;
    unsigned long long res_built;
    unsigned long long res_impl;
    bool overflow_built;
    bool overflow_impl;

    x = 10;
    y = 1 << 10;
    overflow_built = __builtin_umulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 100;
    overflow_built = __builtin_umulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    x = (1ull << ((sizeof(x) * CHAR_BIT) - 1)) + 10000;
    y = (1ull << ((sizeof(x) * CHAR_BIT) - 2)) + 100;
    overflow_built = __builtin_umulll_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_umulll_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);
}

static void test_overflow_mul_generic(void)
{
    bool overflow_built;
    bool overflow_impl;

    int x = 10;
    int y = 1 << 10;
    int res_built;
    int res_impl;
    overflow_built = __builtin_mul_overflow(x, y, &res_built);
    overflow_impl = kbuiltin_mul_overflow_impl(x, y, &res_impl);

    assert(overflow_built == overflow_impl);
    assert(res_built == res_impl);

    long x2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 10000;
    long y2 = (long)(1ul << ((sizeof(x2) * CHAR_BIT) - 1)) + 100;
    long res_built2;
    long res_impl2;
    overflow_built = __builtin_mul_overflow(x2, y2, &res_built2);
    overflow_impl = kbuiltin_mul_overflow_impl(x2, y2, &res_impl2);

    assert(overflow_built == overflow_impl);
    assert(res_built2 == res_impl2);

    long long x3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 10000;
    long long y3 = (long long)(1ull << ((sizeof(x3) * CHAR_BIT) - 2)) + 100;
    long long res_built3;
    long long res_impl3;
    overflow_built = __builtin_mul_overflow(x3, y3, &res_built3);
    overflow_impl = kbuiltin_mul_overflow_impl(x3, y3, &res_impl3);

    assert(overflow_built == overflow_impl);
    assert(res_built3 == res_impl3);

    unsigned x4 = (1u << ((sizeof(x4) * CHAR_BIT) - 2)) + 10000;
    unsigned y4 = (1u << ((sizeof(x4) * CHAR_BIT) - 1)) + 100;
    unsigned res_built4;
    unsigned res_impl4;
    overflow_built = __builtin_mul_overflow(x4, y4, &res_built4);
    overflow_impl = kbuiltin_mul_overflow_impl(x4, y4, &res_impl4);

    assert(overflow_built == overflow_impl);
    assert(res_built4 == res_impl4);

    unsigned long x5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 1)) + 10000;
    unsigned long y5 = (1ul << ((sizeof(x5) * CHAR_BIT) - 2)) + 100;
    unsigned long res_built5;
    unsigned long res_impl5;
    overflow_built = __builtin_mul_overflow(x5, y5, &res_built5);
    overflow_impl = kbuiltin_mul_overflow_impl(x5, y5, &res_impl5);

    assert(overflow_built == overflow_impl);
    assert(res_built5 == res_impl5);

    unsigned long long x6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 4)) + 10000;
    unsigned long long y6 = (1ull << ((sizeof(x6) * CHAR_BIT) - 1)) + 100;
    unsigned long long res_built6;
    unsigned long long res_impl6;
    overflow_built = __builtin_mul_overflow(x6, y6, &res_built6);
    overflow_impl = kbuiltin_mul_overflow_impl(x6, y6, &res_impl6);

    assert(overflow_built == overflow_impl);
    assert(res_built6 == res_impl6);
}

static void test_overflow(void)
{
    test_overflow_addi();
    test_overflow_addu();
    test_overflow_addl();
    test_overflow_addul();
    test_overflow_addll();
    test_overflow_addull();
    test_overflow_add_generic();

    test_overflow_subi();
    test_overflow_subu();
    test_overflow_subl();
    test_overflow_subul();
    test_overflow_subll();
    test_overflow_subull();
    test_overflow_sub_generic();

    test_overflow_muli();
    test_overflow_mulu();
    test_overflow_mull();
    test_overflow_mulul();
    test_overflow_mulll();
    test_overflow_mulull();
    test_overflow_mul_generic();
}

#else

/* gcc supports it only on x86 */
static void test_overflow(void)
{

}

#endif

void test_builtins_impl(void)
{
    test_only_compiling_builtins();
    test_ffs();
    test_clz();
    test_ctz();
    test_clrsb();
    test_popcount();
    test_parity();
    test_bswap();
    test_overflow();
}

#else

/* test has been compile using weird compiler, do nothing */
void test_builtins_impl(void)
{

}

#endif
