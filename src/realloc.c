/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** realloc
*/

#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include "../include/libmem.h"
#include "../include/my_macros.h"

static void *hanlde_realloc_error(void *ptr, size_t size)
{
    PTR(size && !ptr, NULL);
    if (!ptr)
        return malloc(size);
    free(ptr);
    return NULL;
}

void *realloc(void *ptr, size_t size)
{
    size_t align = ALIGN16(size);
    metadata_t *current = NULL;
    void *new = NULL;

    if (!ptr || !size)
        return hanlde_realloc_error(ptr, size);
    current = ptr - sizeof(metadata_t);
    if (current->is_free_mem || current->size >= align)
        return ptr;
    new = malloc(align);
    PTR(new, NULL);
    memcpy(new, ptr, current->size);
    free(ptr);
    return new;
}