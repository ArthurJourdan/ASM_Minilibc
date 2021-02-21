/*
** EPITECH PROJECT, 2021
** tests_memmove.c
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

void *(*my_memmove)(void *, const void *, size_t);
static void *my_lib;

static void get_my_memmove()
{
    my_lib = dlopen(fp_libasm, RTLD_LAZY);
    if (!my_lib) {
        return;
    }
    my_memmove = dlsym(my_lib, "memmove");
}

static void close_lib()
{
    dlclose(my_lib);
}

Test(my_memmove, test_outdecl, .init=get_my_memmove, .fini=close_lib)
{
    if (!my_memmove)
        cr_skip_test();

    size_t size = strlen(my_test_str);
    char *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_mov = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_mov)
        cr_skip_test();
    my_memmove(str_moved, my_test_str, size);
    memmove(expected_mov, my_test_str, size);

    cr_assert_str_eq(str_moved, expected_mov);
}

Test(my_memmove, simple_string, .init=get_my_memmove, .fini=close_lib)
{
    if (!my_memmove)
        cr_skip_test();

    size_t size = strlen(my_test_str);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_mov = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_mov)
        cr_skip_test();
    my_memmove(str_moved, my_test_str, size);
    memmove(expected_mov, my_test_str, size);

    cr_assert_str_eq(str_moved, expected_mov);
}

Test(my_memmove, empty_string, .init=get_my_memmove, .fini=close_lib)
{
    if (!my_memmove)
        cr_skip_test();

    size_t size = strlen(my_test_emptyStr);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_mov = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_mov)
        cr_skip_test();
    my_memmove(str_moved, my_test_emptyStr, size);
    memmove(expected_mov, my_test_emptyStr, size);

    cr_assert_str_eq(str_moved, expected_mov);
}

Test(my_memmove, long_string, .init=get_my_memmove, .fini=close_lib)
{
    if (!my_memmove)
        cr_skip_test();

    size_t size = strlen(my_test_longStr);
    void *str_moved = malloc(sizeof(char) * (size + 1));
    char *expected_mov = malloc(sizeof(char) * (size + 1));

    if (!str_moved || !expected_mov)
        cr_skip_test();
    my_memmove(str_moved, my_test_longStr, size);
    memmove(expected_mov, my_test_longStr, size);

    cr_assert_str_eq(str_moved, expected_mov);
}