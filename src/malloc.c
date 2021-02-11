/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** malloc
*/

#include <unistd.h>
#include "libmem.h"
#include "my_macros.h"

static metadata_t *best_fit(metadata_t **save, size_t size)
{
    metadata_t *head = global_head(NULL, false);
    metadata_t *tmp = NULL;

    for (; head; head = head->next) {
        if (tmp && head->is_free_mem && head->size < size) {
            tmp = (head->size < tmp->size) ? head : tmp;
        } else if (head->is_free_mem && head->size < size) {
            tmp = head;
        }
    }
    *save = tmp;
    return head;
}

static metadata_t *enlarge(metadata_t *save, size_t size)
{
    metadata_t *tmp = sbrk(0);
    size_t mult = 2;

    while (size > sysconf(_SC_PAGESIZE) * mult)
        mult += 2;
    if (sbrk(sysconf(_SC_PAGESIZE) * mult) == (void *)-1)
        return NULL;
    tmp->size = size;
    tmp->next = NULL;
    tmp->prev = save;
    tmp->ptr = tmp->end_meta;
    if (save)
        save->next = tmp;
    tmp->is_free_mem = false;
    return tmp;
}

static metadata_t *head_algo(metadata_t *current, size_t align)
{
    metadata_t *save = NULL;

    save = global_head(NULL, false);
    current = best_fit(&save, align);
    if (current) {
        if ((current->size - align) >= (sizeof(metadata_t) + 8))
            split_block(current, align);
        current->is_free_mem = 0;
    } else {
        PTR((current = enlarge(save, align)), NULL);
    }
    return current;
}

static metadata_t *no_head_algo(metadata_t *current, size_t align)
{
    current = enlarge(NULL, align);
    PTR(current, NULL);
    global_head(current, false);
    return current;
}

void *malloc(size_t size)
{
    metadata_t *current = NULL;
    size_t align = ALIGN8(size);

    PTR(size, NULL);
    if (global_head(NULL, false)) {
        PTR((current = head_algo(current, align)), NULL);
    } else {
        PTR((current = no_head_algo(current, align)), NULL);
    }
    return current->end_meta;
}