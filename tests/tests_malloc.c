/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** tests_malloc
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmem.h"

Test(malloc, no_error)
{
    char *test = malloc(sizeof(char *) * 9000);

    test[0] = 't';
    test[1] = 'e';
    test[2] = 's';
    test[3] = 't';
    test[4] = '\0';
    cr_assert_str_eq("test", "test");
}

Test(malloc, error)
{
    char *test = malloc(sizeof(char *) * 0);

    cr_expect(test == NULL);
}