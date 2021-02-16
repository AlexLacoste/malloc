/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** malloc
*/

#include <stdlib.h>
#include <unistd.h>
#include "libmem.h"
#include "my_macros.h"

static metadata_t *best_fit(metadata_t **end, size_t size)
{
    metadata_t *save = NULL;
    metadata_t *save2 = NULL;

    for (metadata_t *tmp = global_ptr(NULL, false); tmp; tmp = tmp ->next) {
        if (tmp->is_free_mem && tmp->size >= size) {
            save = tmp;
        } else
            save2 = tmp;
    }
    if (save) {
        *end = save2;
        return save;
    }
    if (save2) {
        *end = save2;
        return NULL;
    }
    return global_ptr(NULL, false);
}

static metadata_t *enlarge(metadata_t *end, size_t size)
{
    metadata_t *tmp = (!end) ? sbrk(0) : (void *)(end + 1) +
                                            end->size;
    size_t mult = 2;

    if ((size_t)current_size(0, false) < size + sizeof(metadata_t)) {
        while (size + sizeof(metadata_t) > sysconf(_SC_PAGESIZE) * mult)
            mult += 2;
        if (sbrk(sysconf(_SC_PAGESIZE) * mult) == (void *)-1)
            return NULL;
        current_size(current_size(0, false) +
                    sysconf(_SC_PAGESIZE) * mult, true);
    }
    tmp->size = size;
    tmp->next = NULL;
    tmp->is_free_mem = false;
    if (end)
        end->next = tmp;
    current_size(current_size(0, false) - size - sizeof(metadata_t), true);
    return tmp;
}

static metadata_t *ptr_algo(size_t align)
{
    metadata_t * end = global_ptr(NULL, false);
    metadata_t *ptr = best_fit(&end, align);

    if (!ptr) {
        PTR((ptr = enlarge(end, align)), NULL);
    } else
        ptr->is_free_mem = false;
    return ptr + 1;
}

static metadata_t *no_ptr_algo(size_t align)
{
    metadata_t *ptr = NULL;

    PTR((ptr = enlarge(ptr, align)), NULL);
    global_ptr(ptr, true);
    return ptr + 1;
}

void *malloc(size_t size)
{
    metadata_t *ptr = NULL;
    size_t align = 0;

    PTR(size, NULL);
    align = ALIGN16(size);
    if (global_ptr(NULL, false)) {
        PTR((ptr = ptr_algo(align)), NULL);
    } else {
        PTR((ptr = no_ptr_algo(align)), NULL);
    }
    return ptr;
}