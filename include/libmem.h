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

#define ALIGN8(x) (((x) + ((8) - 1)) & ~((8) - 1))

typedef struct metadata_s {
    int is_free_mem;
    size_t size;
    void *ptr;
    struct metadata_s *next;
    struct metadata_s *prev;
    char end_meta[0];
} metadata_t;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb , size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

void *global_head(void *ptr, bool set_new_value);
void split_block(metadata_t *current, size_t size);

#endif /* !LIBMEM_H_ */
