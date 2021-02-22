/*
** EPITECH PROJECT, 2021
** tests_strlen.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <dlfcn.h>

static const char *my_str = "qwerty";
static const char *my_str_empty = "";
static const char *my_str_wide = \
"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbn";

static const char *fp_libasm = "./libasm.so";
static size_t (*my_strlen)(const char *);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strlen()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strlen = dlsym(my_lib, "strlen");
    if (!my_strlen) {
        cr_log_warn(err_missing_symbol, "strlen", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_strlen, simple, .init=get_my_strlen, .fini=close_lib)
{
    size_t my_len = my_strlen(my_str);
    size_t expected_len = strlen(my_str);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, simple_string, .init=get_my_strlen, .fini=close_lib)
{
    size_t my_len = my_strlen(my_str);
    size_t expected_len = strlen(my_str);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, empty_string, .init=get_my_strlen, .fini=close_lib)
{
    size_t my_len = my_strlen(my_str_empty);
    size_t expected_len = strlen(my_str_empty);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, long_string, .init=get_my_strlen, .fini=close_lib)
{
    size_t my_len = my_strlen(my_str_wide);
    size_t expected_len = strlen(my_str_wide);

    cr_assert(my_len == expected_len);
}

Test(my_strlen, NULL_str, .init=get_my_strlen, .fini=close_lib)
{
    char *my_null = NULL;
    size_t my_len = my_strlen(my_null);
    size_t expected_len = strlen(my_null);

    cr_assert(my_len == expected_len);
}
