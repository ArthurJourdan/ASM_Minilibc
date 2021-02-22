/*
** EPITECH PROJECT, 2021
** tests_memcpy.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *my_str = "qwerty";
static const char *my_str_empty = "";
static const char *my_str_long = \
"qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbn";
static const int my_int_arr[3] = {1, 2, 3};

static const char *fp_libasm = "./libasm.so";
static void *(*my_memcpy)(void *, const void *, size_t);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_memcpy()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_memcpy = dlsym(my_lib, "memcpy");
    if (!my_memcpy) {
        cr_log_warn(err_missing_symbol, "memcpy", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_memcpy, simple, .init=get_my_memcpy, .fini=close_lib)
{
    size_t size = strlen(my_str);
    char *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_str, size);
    memcpy(expected_cpy, my_str, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, simple_string, .init=get_my_memcpy, .fini=close_lib)
{
    size_t size = strlen(my_str);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_str, size);
    memcpy(expected_cpy, my_str, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, empty_string, .init=get_my_memcpy, .fini=close_lib)
{
    size_t size = strlen(my_str_empty);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_str_empty, size);
    memcpy(expected_cpy, my_str_empty, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, long_string, .init=get_my_memcpy, .fini=close_lib)
{
    size_t size = strlen(my_str_long);
    void *str_copyied = malloc(sizeof(char) * (size + 1));
    char *expected_cpy = malloc(sizeof(char) * (size + 1));

    if (!str_copyied || !expected_cpy)
        cr_skip_test();
    my_memcpy(str_copyied, my_str_long, size);
    memcpy(expected_cpy, my_str_long, size);

    cr_assert_str_eq(str_copyied, expected_cpy);
}

Test(my_memcpy, overlap, .init=get_my_memcpy, .fini=close_lib)
{
    size_t my_len = strlen(my_str);
    char *my_expect = malloc(sizeof(char) * my_len);
    char *my_expect_2 = my_expect + (my_len / sizeof(my_str[0]));
    char *my_cpy = malloc(sizeof(char) * my_len);
    char *my_cpy_2 = my_cpy + (my_len / sizeof(my_str[0]));

    memcpy(my_expect, my_str, my_len);
    memcpy(my_expect_2, my_expect, my_len);

    my_memcpy(my_cpy, my_str, my_len);
    my_memcpy(my_cpy_2, my_str, my_len);

    cr_assert_str_eq(my_expect, my_cpy);
    cr_assert_str_eq(my_expect_2, my_cpy_2);
}

Test(my_memcpy, int_arr, .init=get_my_memcpy, .fini=close_lib)
{
    size_t my_len = sizeof(my_int_arr);
    int *my_expect = malloc(my_len);
    int *my_cpy = malloc(my_len);

    memcpy(my_expect, my_int_arr, my_len);
    my_memcpy(my_cpy, my_int_arr, my_len);

    cr_assert_arr_eq(my_expect, my_cpy, my_len);
}


Test(my_memcpy, overlap_int_arr, .init=get_my_memcpy, .fini=close_lib)
{
    size_t my_len = sizeof(my_int_arr);
    int *my_expect = malloc(my_len);
    int *my_expect_2 = my_expect + (my_len / sizeof(my_int_arr[0]));
    int *my_cpy = malloc(my_len);
    int *my_cpy_2 = my_cpy + (my_len / sizeof(my_int_arr[0]));

    memcpy(my_expect, my_int_arr, my_len);
    memcpy(my_expect_2, my_expect, my_len);

    my_memcpy(my_cpy, my_int_arr, my_len);
    my_memcpy(my_cpy_2, my_cpy, my_len);

    cr_assert_arr_eq(my_expect, my_cpy, my_len);
    cr_assert_arr_eq(my_expect_2, my_cpy_2, my_len);
}
