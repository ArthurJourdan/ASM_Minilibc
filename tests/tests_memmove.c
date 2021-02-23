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
    size_t my_size = strlen(my_str);
    char *my_move = malloc(sizeof(char) * (my_size + 1));
    char *my_expect = malloc(sizeof(char) * (my_size + 1));

    if (!my_move || !my_expect)
        cr_skip_test();
    my_memmove(my_move, my_str, my_size);
    memmove(my_expect, my_str, my_size);

    cr_assert_str_eq(my_move, my_expect);
}

Test(my_memmove, simple_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = strlen(my_str);
    char *my_move = malloc(sizeof(char) * (my_size + 1));
    char *my_expect = malloc(sizeof(char) * (my_size + 1));

    if (!my_move || !my_expect)
        cr_skip_test();
    my_memmove(my_move, my_str, my_size);
    memmove(my_expect, my_str, my_size);

    cr_assert_str_eq(my_move, my_expect);
}

Test(my_memmove, empty_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = strlen(my_str_empty);
    char *my_move = malloc(sizeof(char) * (my_size + 1));
    char *my_expect = malloc(sizeof(char) * (my_size + 1));

    if (!my_move || !my_expect)
        cr_skip_test();
    my_memmove(my_move, my_str_empty, my_size);
    memmove(my_expect, my_str_empty, my_size);

    cr_assert_str_eq(my_move, my_expect);
}

Test(my_memmove, long_string, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = strlen(my_str_wide);
    char *my_move = malloc(sizeof(char) * (my_size + 1));
    char *my_expect = malloc(sizeof(char) * (my_size + 1));

    if (!my_move || !my_expect)
        cr_skip_test();
    my_memmove(my_move, my_str_wide, my_size);
    memmove(my_expect, my_str_wide, my_size);

    cr_assert_str_eq(my_move, my_expect);
}

Test(my_memmove, long_string_partially, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = strlen(my_str_wide) / 2;
    char *my_move = malloc(sizeof(char) * (my_size + 1));
    char *my_expect = malloc(sizeof(char) * (my_size + 1));

    if (!my_move || !my_expect)
        cr_skip_test();
    my_memmove(my_move, my_str_wide, my_size);
    memmove(my_expect, my_str_wide, my_size);

    cr_assert_str_eq(my_move, my_expect);
}

Test(my_memmove, overlap, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = strlen(my_str);
    char *my_expect = malloc(sizeof(char) * my_size);
    char *my_expect_2 = my_expect + (my_size / sizeof(my_str[0]));
    char *my_move = malloc(sizeof(char) * my_size);
    char *my_move_2 = my_move + (my_size / sizeof(my_str[0]));

    memmove(my_expect, my_str, my_size);
    memmove(my_expect_2, my_expect, my_size);

    my_memmove(my_move, my_str, my_size);
    my_memmove(my_move_2, my_str, my_size);

    cr_assert_str_eq(my_expect, my_move);
    cr_assert_str_eq(my_expect_2, my_move_2);
}

Test(my_memmove, int_arr, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = sizeof(my_int_arr);
    int *my_expect = malloc(my_size);
    int *my_move = malloc(my_size);

    memmove(my_expect, my_int_arr, my_size);
    my_memmove(my_move, my_int_arr, my_size);

    cr_assert_arr_eq(my_expect, my_move, my_size);
}

Test(my_memmove, overlap_int_arr, .init=get_my_memmove, .fini=close_lib)
{
    size_t my_size = sizeof(my_int_arr);
    int *my_expect = malloc(my_size);
    int *my_expect_2 = my_expect + (my_size / sizeof(my_int_arr[0]));
    int *my_move = malloc(my_size);
    int *my_move_2 = my_move + (my_size / sizeof(my_int_arr[0]));

    memmove(my_expect, my_int_arr, my_size);
    memmove(my_expect_2, my_expect, my_size);

    my_memmove(my_move, my_int_arr, my_size);
    my_memmove(my_move_2, my_move, my_size);

    cr_assert_arr_eq(my_expect, my_move, my_size);
    cr_assert_arr_eq(my_expect_2, my_move_2, my_size);
}

Test(my_memmove, NULL_dest, .init=get_my_memmove, .fini=close_lib)
{
    char *my_move = NULL;

    my_memmove(my_move, my_str, 0);

    cr_assert_null(my_move);
}

Test(my_memmove, NULL_src, .init=get_my_memmove, .fini=close_lib)
{
    void *my_null = NULL;
    char *my_move = malloc(sizeof(char) * 1);

    if (!my_move)
        cr_skip_test();
    my_memmove(my_move, my_null, 0);

    cr_assert_not_null(my_move);
}

Test(my_memmove, NULL_args, .init=get_my_memmove, .fini=close_lib)
{
    void *my_null = NULL;
    char *my_move = NULL;

    my_memmove(my_move, my_null, 0);

    cr_assert_null(my_move);
}