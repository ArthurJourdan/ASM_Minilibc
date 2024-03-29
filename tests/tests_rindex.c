/*
** EPITECH PROJECT, 2021
** tests_rindex.c
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
static const char my_char = 't';

static const char *fp_libasm = "./libasm.so";
static char *(*my_rindex)(const char *, int);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol =
    "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_rindex()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_rindex = dlsym(my_lib, "rindex");
    if (!my_rindex) {
        cr_log_warn(err_missing_symbol, "rindex", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}
TestSuite(my_rindex, .init=get_my_rindex, .fini=close_lib);

Test(my_rindex, simple)
{
    char *result_char = my_rindex(my_str, my_char);
    char *expected_char = rindex(my_str, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_rindex, simple_string)
{
    char *result_char = my_rindex(my_str, my_char);
    char *expected_char = rindex(my_str, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_rindex, empty_string)
{
    char *result_char = my_rindex(my_str_empty, my_char);
    char *expected_char = rindex(my_str_empty, my_char);

    cr_assert_eq(result_char, expected_char);
}

Test(my_rindex, long_string)
{
    char *result_char = my_rindex(my_str_wide, my_char);
    char *expected_char = rindex(my_str_wide, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_rindex, find_0)
{
    char *result_char = my_rindex(my_str_wide, '\0');
    char *expected_char = rindex(my_str_wide, '\0');

    cr_assert_str_eq(result_char, expected_char);
}