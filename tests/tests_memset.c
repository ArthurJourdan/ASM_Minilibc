/*
** EPITECH PROJECT, 2021
** tests_memset.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *fp_libasm = "./libasm.so";

static char my_test_char = 't';

void *(*my_memset)(void *, int, size_t);
static void *my_lib;

static void get_my_memset()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        return;
    }
    my_memset = dlsym(my_lib, "my_memset");
}

static void close_lib()
{
    dlclose(my_lib);
}

Test(my_memset, test_outdecl, .init=get_my_memset, .fini=close_lib)
{
    if (!my_memset)
        cr_skip_test();

    size_t size = 10;
    char *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_test_char, size);
    memset(expected_set, my_test_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, simple_string, .init=get_my_memset, .fini=close_lib)
{
    if (!my_memset)
        cr_skip_test();

    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_test_char, size);
    memset(expected_set, my_test_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, empty_string, .init=get_my_memset, .fini=close_lib)
{
    if (!my_memset)
        cr_skip_test();

    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_test_char, size);
    memset(expected_set, my_test_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}

Test(my_memset, long_string, .init=get_my_memset, .fini=close_lib)
{
    if (!my_memset)
        cr_skip_test();

    size_t size = 10;
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_set = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_set)
        cr_skip_test();
    my_memset(str_copyied, my_test_char, size);
    memset(expected_set, my_test_char, size);

    cr_assert_str_eq(str_copyied, expected_set);
}