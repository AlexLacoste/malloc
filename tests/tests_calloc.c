/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** tests_calloc
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmem.h"

Test(calloc, no_error)
{
    char *test = calloc(1, sizeof(char *) * 10);

    cr_expect(test[0] == '\0');
}

Test(calloc, error)
{
    char *test = calloc(90000000000, sizeof(char *) * 10);

    cr_expect(test == NULL);
}