/*
** EPITECH PROJECT, 2021
** tests_memset.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char my_char = 't';

static const char *fp_libasm = "./libasm.so";
static void *(*my_memset)(void *, int, size_t);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_memset()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_memset = dlsym(my_lib, "memset");
    if (!my_memset) {
        cr_log_warn(err_missing_symbol, "memset", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_memset, simple, .init=get_my_memset, .fini=close_lib)
{
    size_t size = 10;
    char *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_char, size);
    memset(expected_set, my_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, simple_string, .init=get_my_memset, .fini=close_lib)
{
    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_char, size);
    memset(expected_set, my_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, empty_string, .init=get_my_memset, .fini=close_lib)
{
    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_char, size);
    memset(expected_set, my_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, long_string, .init=get_my_memset, .fini=close_lib)
{
    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_char, size);
    memset(expected_set, my_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}