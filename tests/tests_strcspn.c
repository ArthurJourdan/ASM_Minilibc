/*
** EPITECH PROJECT, 2021
** tests_strcspn.c
** File description:
** ASM minilibc
*/

#include <dlfcn.h>
#include <criterion/criterion.h>

static const char *my_str = "qwerty";
static const char *my_str_near = "awdrgy";
static const char *my_str_different = "asdf";
static const char *my_str_empty = "";
static const char *my_str_wide = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjk"
                                 "lzxcvbnmqwertyuiopasdfghjklzxcvbn";

static const char *fp_libasm = "./libasm.so";
static size_t (*my_strcspn)(const char *, const char *);
static void *my_lib;
static const char *err_missing_lib = "Shared lib \"%s\" could not be opened\n";
static const char *err_missing_symbol =
    "Symbol \"%s\" could not be found in \"%s\"\n";

static void get_my_strcspn()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        cr_log_warn(err_missing_lib, fp_libasm);
        cr_skip_test();
    }
    my_strcspn = dlsym(my_lib, "strcspn");
    if (!my_strcspn) {
        cr_log_warn(err_missing_symbol, "strcspn", fp_libasm);
        cr_skip_test();
    }
}

static void close_lib()
{
    if (my_lib)
        dlclose(my_lib);
}

Test(my_strcspn, same_string, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str, my_str);
    size_t expected_len = strcspn(my_str, my_str);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, different_string, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str, my_str_different);
    size_t expected_len = strcspn(my_str, my_str_different);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, near_string, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str, my_str_near);
    size_t expected_len = strcspn(my_str, my_str_near);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, empty_string, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str_empty, my_str);
    size_t expected_len = strcspn(my_str_empty, my_str);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, string_empty, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str, my_str_empty);
    size_t expected_len = strcspn(my_str, my_str_empty);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, same_string_wide, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str_wide, my_str);
    size_t expected_len = strcspn(my_str_wide, my_str);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, different_string_wide, .init = get_my_strcspn,
    .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str_wide, my_str_different);
    size_t expected_len = strcspn(my_str_wide, my_str_different);

    cr_assert(my_len == expected_len);
}

Test(my_strcspn, near_string_wide, .init = get_my_strcspn, .fini = close_lib)
{
    size_t my_len = my_strcspn(my_str_wide, my_str_near);
    size_t expected_len = strcspn(my_str_wide, my_str_near);

    cr_assert(my_len == expected_len);
}