/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** calloc
*/

#include <stddef.h>
#include <string.h>
#include "libmem.h"
#include "my_macros.h"

void *calloc(size_t nmemb, size_t size)
{
    void *tmp = NULL;

    PTR(nmemb || !size, NULL);
    if (nmemb > 0xFFFFFFFFUL / size)
        return NULL;
    tmp =  malloc(nmemb * size);
    PTR(tmp, NULL);
    memset(tmp, 0, ALIGN16(nmemb * size));
    return tmp;
}
