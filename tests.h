/** @weakgroup tests
 *  @{
 */
/**
 * @file tests.h
 * @brief frameworkless functions testing procedures
 *
 * Copyright 2020 Stanislav V. Vlasov <stanislav.v.v@gmail.com>
 *
 * All tests here. See test_list[]
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "libs/strings_local.h"
#include "libs/utils.h"

/// test i2bin
void test_i2bin(void)
{
    uint32_t n = 0x13d800ac;
    char a[40];
    char b[] = "0001 0011 1101 1000 0000 0000 1010 1100";
    i2bin(n, a, 8);
    assert(!strcmp(a, b));

}

/// test i2bin
void test_itobin_u32(void)
{
    uint32_t n = 0x13d800ac;
    char a[40];
    char b[] = "10011110110000000000010101100";
    itobin_u32(n, a);
    assert(!strcmp(a, b));

}

/// test itohex_u32
void test_itohex_u32(void)
{
    uint32_t n = 508000172;
    char a[10];
    char b[10];
    itohex_u32(n, a);
    sprintf(b, "%x", n);
    assert(!strcmp(a, b));
}

/// test itoa_s16
void test_itoa_s16(void)
{
    uint16_t n = -12345;
    char a[10];
    itoa_s16(n, a);
    assert(!strcmp("-12345", a));
}

/// test itoa_u16
void test_itoa_u16(void)
{
    uint16_t n = 12345;
    char a[10];
    itoa_u16(n, a);
    assert(!strcmp("12345", a));
}

/// test reverse
void test_reverse(void)
{
    char a[] = "ABCDEF";
    reverse(a);
    assert(!strcmp("FEDCBA", a));
}

/// test compare_strings
void test_compare_strings(void)
{
    const char a1[] = "ABCDE";
    const char a2[] = "ABCDE";
    const char a3[] = "ABCDEF";
    assert(compare_strings(a1, a2));
    assert(!compare_strings(a1, a3));
}

/// test strncmp_local
void test_strncmp_local(void)
{
    const char a1[] = "ABCDE";
    const char a2[] = "ABCDEF";
    // strncmp_local return TRUE on compare
    assert(strncmp(a1, a2, 4) == !strncmp_local(a1, a2, 4));
    assert(!(strncmp(a1, a2, 6) == !strncmp_local(a1, a2, 6)));
}

/// test strlen_local
void test_strlen_local(void)
{
    const char a[] = "ABCDE\0";
    assert(strlen(a) == strlen_local(a));
}

/// test reverse bits
void test_reverse_bits(void)
{
    uint16_t a = (uint16_t)(0x13d800ac);
    reverse_bits(a, 16);
    assert(!(a == 0x35000379));
}

/// test procedure pointer type
typedef void (*test_handler_t)(void);

/// test procedure list entry type
typedef struct
{
    const char* test_str; ///< name of test, usually testing function name
    test_handler_t test_proc; ///< test procedure
    const uint16_t test_group_id; ///< test group id
} test_def_t;

/// test group list entry type
typedef struct
{
    uint16_t group_id; ///< test group id
    const char* group_name; /// test group name
} test_groups_t;

/// list of test groups
static test_groups_t group_list[] =
{
    {1, "string_local.h"},
    {2, "utils"},
    {0, NULL}
};

/// list of tests
static test_def_t test_list[] =
{
// template line
//    {"",               test_, 1},
    {"i2bin",                 test_i2bin, 1},
    {"itobin_u32",            test_itobin_u32, 1},
    {"itohex_u32",            test_itohex_u32, 1},
    {"itoa_s16",              test_itoa_s16, 1},
    {"itoa_u16",              test_itoa_u16, 1},
    {"reverse",               test_reverse, 1},
    {"compare_strings",       test_compare_strings, 1},
    {"strnsmp_local",         test_strncmp_local, 1},
    {"strlen_local",          test_strlen_local, 1},
    {"reverse_bits",          test_reverse_bits, 2},
    {NULL, NULL, 0}
};

/** @}*/
