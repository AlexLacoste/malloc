/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** tests_realloc_array
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmem.h"

Test(reallocarray, no_error)
{
    char *test = malloc(sizeof(char *) * 10);
    test = reallocarray(test, 1, sizeof(char *) * 10);
    test[0] = 'a';
    cr_assert_str_eq("a", "a");
}

Test(reallocarray, error)
{
    char *test = reallocarray(NULL, 90000000000, sizeof(char *) * 10);

    cr_expect(test == NULL);
}