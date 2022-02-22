/*
** EPITECH PROJECT, 2021
** tests_strcmp.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *my_str = "qwerty";
static const char *my_str_different = "qwerto";
static const char *my_str_very_different = "asdf";
static const char *my_str_empty = "";

static const char *fp_libasm = "./libasm.so";
static int (*my_strcmp)(const char *, const char *);
static void *my_lib;
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";

static void get_my_strcmp()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strcmp = dlsym(my_lib, "strcmp");
    if (!my_strcmp) {
        cr_log_warn(err_missing_symbol, "strcmp", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

TestSuite(my_strcmp, .init=get_my_strcmp, .fini=close_lib);

Test(my_strcmp, no_difference)
{
    int my_cmp = my_strcmp(my_str, my_str);
    int my_expected_cmp = strcmp(my_str, my_str);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcmp, inc_ptr)
{
    int my_cmp = my_strcmp(my_str, my_str + 1);
    int my_expected_cmp = strcmp(my_str, my_str + 1);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcmp, near)
{
    int my_cmp = my_strcmp(my_str, my_str_different);
    int my_expected_cmp = strcmp(my_str, my_str_different);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcmp, no_similarity)
{
    int my_cmp = my_strcmp(my_str, my_str_very_different);
    int my_expected_cmp = strcmp(my_str, my_str_very_different);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcmp, empty_str)
{
    int my_cmp = my_strcmp(my_str, my_str_empty);
    int my_expected_cmp = strcmp(my_str, my_str_empty);

    cr_assert_eq(my_cmp, my_expected_cmp);
}