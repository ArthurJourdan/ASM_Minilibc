/*
** EPITECH PROJECT, 2021
** tests_strcasecmp.c
** File description:
** ASM minilibc
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <dlfcn.h>

static const char *my_str = "qwerty";
static const char *my_str_similar = "qWeRtY";
static const char *my_str_different = "qWeRtYiop";
static const char *my_empty_str = "";

static const char *fp_libasm = "./libasm.so";
static int (*my_strcasecmp)(const char *, const char *);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol = "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strcasecmp()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strcasecmp = dlsym(my_lib, "strcasecmp");
    if (!my_strcasecmp) {
        cr_log_warn(err_missing_symbol, "strcasecmp", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_strcasecmp, no_difference, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_str, my_str);
    int my_expected_cmp = strcasecmp(my_str, my_str);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcasecmp, inc_ptr, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_str, my_str + 1);
    int my_expected_cmp = strcasecmp(my_str, my_str + 1);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcasecmp, near, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_str, my_str_similar);
    int my_expected_cmp = strcasecmp(my_str, my_str_similar);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcasecmp, no_similarity, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_str, my_str_different);
    int my_expected_cmp = strcasecmp(my_str, my_str_different);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcasecmp, empty_str, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_str, my_empty_str);
    int my_expected_cmp = strcasecmp(my_str, my_empty_str);

    cr_assert_eq(my_cmp, my_expected_cmp);
}

Test(my_strcasecmp, two_empty_str, .init=get_my_strcasecmp, .fini=close_lib)
{
    int my_cmp = my_strcasecmp(my_empty_str, my_empty_str);
    int my_expected_cmp = strcasecmp(my_empty_str, my_empty_str);

    cr_assert_eq(my_cmp, my_expected_cmp);
}