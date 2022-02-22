/*
** EPITECH PROJECT, 2021
** tests_strncmp.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const size_t my_nb = 3;
static const char *my_str = "qwerty";
static const char *my_str_different = "qwerto";
static const char *my_str_very_different = "asdf";
static const char *my_str_empty = "";

static const char *fp_libasm = "./libasm.so";
static int (*my_strncmp)(const char *, const char *, size_t);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strncmp()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strncmp = dlsym(my_lib, "strncmp");
    if (!my_strncmp) {
        cr_log_warn(err_missing_symbol, "strncmp", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

TestSuite(my_strncmp, .init=get_my_strncmp, .fini=close_lib);

Test(my_strncmp, no_difference)
{
    int my_cmp = my_strncmp(my_str, my_str, my_nb);
    int my_expected_cmp = strncmp(my_str, my_str, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, no_difference_zero)
{
    int my_cmp = my_strncmp(my_str, my_str, 0);
    int my_expected_cmp = strncmp(my_str, my_str, 0);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, inc_ptr)
{
    int my_cmp = my_strncmp(my_str, my_str + 1, my_nb);
    int my_expected_cmp = strncmp(my_str, my_str + 1, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, near)
{
    int my_cmp = my_strncmp(my_str, my_str_different, my_nb);
    int my_expected_cmp = strncmp(my_str, my_str_different, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, no_similarity)
{
    int my_cmp = my_strncmp(my_str, my_str_very_different, my_nb);
    int my_expected_cmp = strncmp(my_str, my_str_very_different, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, no_similarity_zero)
{
    int my_cmp = my_strncmp(my_str, my_str_very_different, 0);
    int my_expected_cmp = strncmp(my_str, my_str_very_different, 0);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, no_similarity_empty_str)
{
    int my_cmp = my_strncmp(my_str, my_str_empty, my_nb);
    int my_expected_cmp = strncmp(my_str, my_str_empty, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, empty_str_zero)
{
    int my_cmp = my_strncmp(my_str_empty, my_str_empty, my_nb);
    int my_expected_cmp = strncmp(my_str_empty, my_str_empty, my_nb);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strncmp, NULL_args)
{
    char *my_null = NULL;
    int my_cmp = my_strncmp(my_null, my_null, 0);

    cr_assert_null(my_cmp);
}