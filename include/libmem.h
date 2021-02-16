/*
** EPITECH PROJECT, 2021
** B-PSU-400-BDX-4-1-malloc-alexandre.lacoste
** File description:
** libmem
*/

#ifndef LIBMEM_H_
#define LIBMEM_H_

#include <stdbool.h>
#include <sys/types.h>

#define ALIGN16(x) (((x) + ((16) - 1)) & ~((16) - 1))

typedef struct metadata_s {
    bool is_free_mem;
    size_t size;
    struct metadata_s *next;
} metadata_t;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb , size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

metadata_t *global_ptr(metadata_t *ptr, bool set_new_value);
int current_size(int size, bool set_new_value);

#endif /* !LIBMEM_H_ */
