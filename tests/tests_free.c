/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** tests_free
*/

#include <criterion/criterion.h>
#include <stddef.h>
#include "libmem.h"

Test(free, no_error)
{
    char *test = malloc(sizeof(char *) * 5);

    free(test);
    cr_expect((((metadata_t *)test - sizeof(metadata_t))->is_free_mem == 0));
}