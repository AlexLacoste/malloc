/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** use_next_chunk
*/

#include <stddef.h>
#include "libmem.h"
#include "my_macros.h"

static metadata_t *use_next_chunk(metadata_t *current)
{
    if (current && current->next && current->next->is_free_mem) {
        current->size += sizeof(metadata_t) +
                        current->next->size;
        current->next = current->next->next;
    }
    return current;
}

void free(void *ptr)
{
    metadata_t *current = (ptr) ? ptr - sizeof(metadata_t) : NULL;

    if (!ptr)
        return;
    current = ptr - sizeof(metadata_t);
    current->is_free_mem = true;
    if (current->next)
        use_next_chunk(current);
}