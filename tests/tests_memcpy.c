/*
** EPITECH PROJECT, 2021
** tests_memcpy.c
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

void *(*my_memcpy)(void *, const void *, size_t);
static void *my_lib;

static void get_my_memcpy()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        return;
    }
    my_memcpy = dlsym(my_lib, "my_memcpy");
}

static void close_lib()
{
    dlclose(my_lib);
}

Test(my_memcpy, test_outdecl, .init=get_my_memcpy, .fini=close_lib)
{
    if (!my_memcpy)
        cr_skip_test();

    size_t size = strlen(my_test_str);
    char *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_test_str, size);
    memcpy(expected_cpy, my_test_str, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, simple_string, .init=get_my_memcpy, .fini=close_lib)
{
    if (!my_memcpy)
        cr_skip_test();

    size_t size = strlen(my_test_str);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_test_str, size);
    memcpy(expected_cpy, my_test_str, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, empty_string, .init=get_my_memcpy, .fini=close_lib)
{
    if (!my_memcpy)
        cr_skip_test();

    size_t size = strlen(my_test_emptyStr);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_test_emptyStr, size);
    memcpy(expected_cpy, my_test_emptyStr, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, long_string, .init=get_my_memcpy, .fini=close_lib)
{
    if (!my_memcpy)
        cr_skip_test();

    size_t size = strlen(my_test_longStr);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_test_longStr, size);
    memcpy(expected_cpy, my_test_longStr, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}