/*
** EPITECH PROJECT, 2021
** tests_memmove.c
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
static const char my_int_arr[3] = {1, 2, 3};

static const char *fp_libasm = "./libasm.so";
static void *(*my_memmove)(void *, const void *, size_t);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_memmove()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_memmove = dlsym(my_lib, "memmove");
    if (!my_memmove) {
        cr_log_warn(err_missing_symbol, "memmove", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_memmove, simple, .init=get_my_memmove, .fini=close_lib)
{
    size_t size = strlen(my_str);
    char *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_moved = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_moved)
        cr_skip_test();
    my_memmove(str_moved, my_str, size);
    memmove(expected_moved, my_str, size);

    cr_assert_str_eq(str_moved, expected_moved);
}

Test(my_memmove, simple_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t size = strlen(my_str);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_moved = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_moved)
        cr_skip_test();
    my_memmove(str_moved, my_str, size);
    memmove(expected_moved, my_str, size);

    cr_assert_str_eq(str_moved, expected_moved);
}

Test(my_memmove, empty_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t size = strlen(my_str_empty);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_moved = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_moved)
        cr_skip_test();
    my_memmove(str_moved, my_str_empty, size);
    memmove(expected_moved, my_str_empty, size);

    cr_assert_str_eq(str_moved, expected_moved);
}

Test(my_memmove, long_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t size = strlen(my_str_wide);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_moved = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_moved)
        cr_skip_test();
    my_memmove(str_moved, my_str_wide, size);
    memmove(expected_moved, my_str_wide, size);

    cr_assert_str_eq(str_moved, expected_moved);
}


Test(my_memmove, long_string_partially, .init=get_my_memmove, .fini=close_lib)
{
    size_t size = strlen(my_str_wide) / 2;
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_moved = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_moved)
        cr_skip_test();
    my_memmove(str_moved, my_str_wide, size);
    memmove(expected_moved, my_str_wide, size);

    cr_assert_str_eq(str_moved, expected_moved);
}

Test(my_memmove, overlap, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_len = strlen(my_str);
    char *my_expect = malloc(sizeof(char) * my_len);
    char *my_expect_2 = my_expect + (my_len / 2);
    char *my_cpy = malloc(sizeof(char) * my_len);
    char *my_cpy_2 = my_cpy + (my_len / 2);

    memmove(my_expect, my_str, my_len);
    memmove(my_expect_2, my_expect, my_len);

    memmove(my_cpy, my_str, my_len);
    memmove(my_cpy_2, my_str, my_len);

    cr_assert_str_eq(my_expect, my_cpy);
    cr_assert_str_eq(my_expect_2, my_cpy_2);
}

Test(my_memmove, int_arr, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_len = sizeof(my_int_arr) / sizeof(my_int_arr[0]);
    int *my_expect = malloc(sizeof(int) * my_len);
    int *my_cpy = malloc(sizeof(int) * my_len);

    memmove(my_expect, my_int_arr, my_len);
    memmove(my_cpy, my_int_arr, my_len);

    cr_assert_arr_eq(my_expect, my_cpy, my_len);
}


Test(my_memmove, overlap_int_arr, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_len = sizeof(my_int_arr) / sizeof(my_int_arr[0]);
    int *my_expect = malloc(sizeof(int) * my_len);
    int *my_expect_2 = my_expect + (my_len / 2);
    int *my_cpy = malloc(sizeof(int) * my_len);
    int *my_cpy_2 = my_cpy + (my_len / 2);

    memmove(my_expect, my_int_arr, my_len);
    memmove(my_expect_2, my_expect, my_len);

    memmove(my_cpy, my_int_arr, my_len);
    memmove(my_cpy_2, my_int_arr, my_len);

    cr_assert_arr_eq(my_expect, my_cpy, my_len);
    cr_assert_arr_eq(my_expect_2, my_cpy_2, my_len);
}
