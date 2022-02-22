/*
** EPITECH PROJECT, 2021
** tests_strpbrk.c
** File description:
** ASM minilibc
*/

#include <dlfcn.h>
#include <unistd.h>
#include <criterion/criterion.h>

static const char *my_str = "qwerty";
static const char *my_str_empty = "";
static const char *my_str_wide = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjk"
                                 "lzxcvbnmqwertyuiopasdfghjklzxcvbn";
static const char *my_str_sub = "ert";

static const char *fp_libasm = "./libasm.so";
static char *(*my_strpbrk)(const char *, const char *);
static void *my_lib;
static const char *err_missing_symbol =
    "Symbol \"%s\" could not be found in \"%s\"\n";
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";

static void get_my_strpbrk()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strpbrk = dlsym(my_lib, "strpbrk");
    if (!my_strpbrk) {
        cr_log_warn(err_missing_symbol, "strpbrk", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

TestSuite(my_strpbrk, .init=get_my_strpbrk, .fini=close_lib);

Test(my_strpbrk, simple)
{
    char *result_str = my_strpbrk(my_str, my_str_sub);
    char *expected_str = strpbrk(my_str, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strpbrk, simple_string)
{
    char *result_str = my_strpbrk(my_str, my_str_sub);
    char *expected_str = strpbrk(my_str, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strpbrk, empty_string)
{
    char *result_str = my_strpbrk(my_str_empty, my_str_sub);
    char *expected_str = strpbrk(my_str_empty, my_str_sub);

    cr_assert_eq(result_str, expected_str);
}

Test(my_strpbrk, long_string)
{
    char *result_str = my_strpbrk(my_str_wide, my_str_sub);
    char *expected_str = strpbrk(my_str_wide, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strpbrk, find_nothing)
{
    char *result_str = my_strpbrk(my_str_wide, my_str_empty);
    char *expected_str = strpbrk(my_str_wide, my_str_empty);

    cr_assert_eq(result_str, expected_str);
}