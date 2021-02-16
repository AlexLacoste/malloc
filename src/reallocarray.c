/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** realloc_array
*/

#include <stddef.h>
#include "libmem.h"
#include "my_macros.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb > 0xFFFFFFFFUL / size)
        return NULL;
    return realloc(ptr, nmemb * size);
}
