/*
** EPITECH PROJECT, 2021
** tests_strchr.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *fp_libasm = "./libasm.so";

static const char *my_test_str = "qwerty";
static const char *my_test_emptyStr = "";
static const char *my_test_longStr = \
"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbn";
static const char my_test_char = 't';

char *(*my_strchr)(const char *, int);
static void *my_lib;

static void get_my_strchr()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        return;
    }
    my_strchr = dlsym(my_lib, "my_strchr");
}

static void close_lib()
{
    dlclose(my_lib);
}

Test(my_strchr, test_outdecl, .init=get_my_strchr, .fini=close_lib)
{
    if (!my_strchr)
        cr_skip_test();

    char *result_char = my_strchr(my_test_str, my_test_char);
    char *expected_char = strchr(my_test_str, my_test_char);

    cr_assert_str_eq(result_char, expected_char);
}

Test(my_strchr, simple_string, .init=get_my_strchr, .fini=close_lib)
{
    if (!my_strchr)
        cr_skip_test();

    char *result_char = my_strchr(my_test_str, my_test_char);
    char *expected_char = strchr(my_test_str, my_test_char);

    cr_assert_str_eq(result_char, expected_char);
}

#include <stdio.h>

Test(my_strchr, empty_string, .init=get_my_strchr, .fini=close_lib)
{
    if (!my_strchr)
        cr_skip_test();

    char *result_char = my_strchr(my_test_emptyStr, my_test_char);
    char *expected_char = strchr(my_test_emptyStr, my_test_char);

    cr_assert_eq(result_char, expected_char);
}

Test(my_strchr, long_string, .init=get_my_strchr, .fini=close_lib)
{
    if (!my_strchr)
        cr_skip_test();

    char *result_char = my_strchr(my_test_longStr, my_test_char);
    char *expected_char = strchr(my_test_longStr, my_test_char);

    cr_assert_str_eq(result_char, expected_char);
}