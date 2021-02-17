/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** tests_realloc
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmem.h"

Test(realloc, no_error_alloc)
{
    char *test = malloc(sizeof(char *) * 10);
    test = realloc(test, sizeof(char *) * 9000);
    test[0] = 'a';
    cr_assert_str_eq("a", "a");
}

Test(realloc, no_error_no_alloc)
{
    char *test = malloc(sizeof(char *) * 10);
    test = realloc(test, sizeof(char *) * 5);
    test[0] = 'a';
    cr_assert_str_eq("a", "a");
}

Test(realloc, error_null_ptr)
{
    char *test = realloc(NULL, sizeof(char *) * 5);
    test[0] = 'a';
    cr_assert_str_eq("a", "a");
}

Test(realloc, error_null_size)
{
    char *test = malloc(sizeof(char *) * 10);
    test = realloc(test, 0);
    cr_expect(test == NULL);
}
