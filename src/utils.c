/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** utils
*/

#include <stdbool.h>
#include <stddef.h>
#include "libmem.h"

void *global_head(void *ptr, bool set_new_value)
{
    static void *head = NULL;

    if (set_new_value) {
        head = ptr;
        return NULL;
    } else {
        return head;
    }
}

void split_block(metadata_t *current, size_t size)
{
    metadata_t *tmp = ((metadata_t *)current->end_meta) + size;

    tmp->size = ALIGN8(current->size - size - sizeof(metadata_t));
    tmp->next = current->next;
    tmp->prev = current;
    tmp->is_free_mem = 1;
    tmp->ptr = current->end_meta;
    current->size = ALIGN8(size);
    current->next = tmp;
    if (tmp->next)
        tmp->next->prev = current;
}