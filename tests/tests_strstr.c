/*
** EPITECH PROJECT, 2021
** tests_strstr.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *my_str = "qwerty";
static const char *my_str_empty = "";
static const char *my_str_wide = \
"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbn";
static const char *my_str_sub = "ert";

static const char *fp_libasm = "./libasm.so";
static char *(*my_strstr)(const char *, const char *);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strstr()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strstr = dlsym(my_lib, "strstr");
    if (!my_strstr) {
        cr_log_warn(err_missing_symbol, "strstr", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_strstr, simple, .init=get_my_strstr, .fini=close_lib)
{
    char *result_str = my_strstr(my_str, my_str_sub);
    char *expected_str = strstr(my_str, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strstr, simple_string, .init=get_my_strstr, .fini=close_lib)
{
    char *result_str = my_strstr(my_str, my_str_sub);
    char *expected_str = strstr(my_str, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strstr, empty_string, .init=get_my_strstr, .fini=close_lib)
{
    char *result_str = my_strstr(my_str_empty, my_str_sub);
    char *expected_str = strstr(my_str_empty, my_str_sub);

    cr_assert_eq(result_str, expected_str);
}

Test(my_strstr, long_string, .init=get_my_strstr, .fini=close_lib)
{
    char *result_str = my_strstr(my_str_wide, my_str_sub);
    char *expected_str = strstr(my_str_wide, my_str_sub);

    cr_assert_str_eq(result_str, expected_str);
}

Test(my_strstr, find_nothing, .init=get_my_strstr, .fini=close_lib)
{
    char *result_str = my_strstr(my_str_wide, my_str_empty);
    char *expected_str = strstr(my_str_wide, my_str_empty);

    cr_assert_str_eq(result_str, expected_str);
}