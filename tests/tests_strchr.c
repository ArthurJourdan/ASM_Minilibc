/*
** EPITECH PROJECT, 2021
** tests_strchr.c
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
static const char my_char_out = 'p';

static const char *fp_libasm = "./libasm.so";
static char *(*my_strchr)(const char *, int);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol =
    "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strchr()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strchr = dlsym(my_lib, "strchr");
    if (!my_strchr) {
        cr_log_warn(err_missing_symbol, "strchr", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_strchr, simple, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str, my_char);
    char *expected_char = strchr(my_str, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_strchr, simple_string, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str, my_char);
    char *expected_char = strchr(my_str, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_strchr, empty_string, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str_empty, my_char);
    char *expected_char = strchr(my_str_empty, my_char);

    cr_assert_eq(result_char, expected_char);
}

Test(my_strchr, long_string, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str_wide, my_char);
    char *expected_char = strchr(my_str_wide, my_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_strchr, find_0, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str_wide, '\0');
    char *expected_char = strchr(my_str_wide, '\0');

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_strchr, simple_not_find, .init = get_my_strchr, .fini = close_lib)
{
    char *result_char = my_strchr(my_str, my_char_out);
    char *expected_char = strchr(my_str, my_char_out);

    cr_assert_eq(result_char, expected_char);
}
