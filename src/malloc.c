/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** malloc
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/libmem.h"
#include "../include/my_macros.h"


// static metadata_t *best_fit(metadata_t **end, size_t size) // gérer le cas tmpNot found
// {
//     metadata_t *save = NULL;
//     metadata_t *save2 = NULL;

//     mputAddr("before ", *end, 1);
//     for (metadata_t *tmp = global_ptr(NULL, false); tmp; tmp = tmp ->next) {
//         if (tmp->is_free_mem && tmp->size >= size) {
//             save = tmp;
//             break;
//         }
//         save2 = tmp;
//     }
//     if (save) {
//         write(2, "found ", 6);
//         *end = save;
//         return save->next ;
//     }
//     if (save2) {
//         write(2, "not foundBut ", 13);
//         *end = save2;
//         mputAddr("after ", *end, 1);
//         return NULL;
//     }
//     if (global_ptr(NULL, false))
//         write(2, "tmpNot found ", 13);
//     else
//         write(2, "not found ", 10);
//     return global_ptr(NULL, false);
// }

static metadata_t *best_fit(metadata_t **end, size_t size) // faire best_fit
{
    metadata_t *tmp = global_ptr(NULL, false);
    // bool check = false;

    // mputAddr("before ", *end, 1);
    for (; tmp && (!tmp->is_free_mem || tmp->size < size); tmp = tmp->next) {
        *end = tmp;
        // check = true;
    }
    // if (check && tmp)
    //     write(2, "found ", 6);
    // else if (check) {
    //     write(2, "not foundBut ", 13);
    //     mputAddr("after ", *end, 1);
    // } else if (tmp)
    //     write(2, "tmpNot found ", 13);
    // else
    //     write(2, "not found ", 10);
    return tmp;
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

    // write(2, "malloc ", 7);
    PTR(size, NULL);
    align = ALIGN16(size);
    if (global_ptr(NULL, false)) {
        PTR((ptr = ptr_algo(align)), NULL);
    } else {
        PTR((ptr = no_ptr_algo(align)), NULL);
    }
    return ptr;
}