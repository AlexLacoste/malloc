/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** utils
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/libmem.h"

metadata_t *global_ptr(metadata_t *ptr, bool set_new_value)
{
    static metadata_t *tmp = NULL;

    if (set_new_value) {
        tmp = ptr;
        return NULL;
    } else {
        return tmp;
    }
}

int current_size(int size, bool set_new_value)
{
    static int current = 0;

    if (set_new_value) {
        current = size;
        return 0;
    } else {
        return current;
    }
}