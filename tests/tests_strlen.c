/*
** EPITECH PROJECT, 2021
** tests_strlen.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <dlfcn.h>

static const char *fp_libasm = "./libasm.so";

static const char *my_test_str = "qwerty";
static const char *my_test_emptyStr = "";
static const char *my_test_longStr = \
"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbn";

static size_t (*my_strlen)(const char *);
static void *my_lib;

static void get_my_strlen()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        return;
    }
    my_strlen = dlsym(my_lib, "strlen");
}

static void close_lib()
{
    dlclose(my_lib);
}

Test(my_strlen, test_outdecl, .init=get_my_strlen, .fini=close_lib)
{
    if (!my_strlen)
        cr_skip_test();

    size_t my_len = my_strlen(my_test_str);
    size_t expected_len = strlen(my_test_str);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, simple_string, .init=get_my_strlen, .fini=close_lib)
{
    if (!my_strlen)
        cr_skip_test();

    size_t my_len = my_strlen(my_test_str);
    size_t expected_len = strlen(my_test_str);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, empty_string, .init=get_my_strlen, .fini=close_lib)
{
    if (!my_strlen)
        cr_skip_test();

    size_t my_len = my_strlen(my_test_emptyStr);
    size_t expected_len = strlen(my_test_emptyStr);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, long_string, .init=get_my_strlen, .fini=close_lib)
{
    if (!my_strlen)
        cr_skip_test();

    size_t my_len = my_strlen(my_test_longStr);
    size_t expected_len = strlen(my_test_longStr);

    cr_assert(my_len == expected_len);
}