/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vector
*/

#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

vector_t *vec_new(size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    vector_t *vec = malloc(sizeof(vector_t));

    if (vec == NULL) {
        return (NULL);
    }
    vec->dtor = dtor;
    vec->cpctor = cpctor;
    vec->item_size = elem_size;
    vec->items = malloc(VEC_INIT_CAPACITY * elem_size);
    vec->nmemb = 0;
    vec->capacity = VEC_INIT_CAPACITY;
    return (vec);
}

vec_error_t vec_reserve(vector_t *vec, size_t additional)
{
    u_char *items_new = NULL;
    if (vec == NULL) {
        return (VEC_NULLPTR);
    }
    if (vec->nmemb + additional > vec->capacity) {
        vec->capacity *= VEC_GROWTH_FACTOR + (additional / vec->capacity);
        items_new = realloc(vec->items, vec->capacity * vec->item_size);
        if (items_new == NULL) {
            return (VEC_ALLOC);
        }
        vec->items = items_new;
    }
    return (VEC_OK);
}

vector_t *vec_with_capacity(
    size_t size, size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    vector_t *vec = vec_new(elem_size, dtor, cpctor);

    if (vec == NULL) {
        return (NULL);
    }
    if (vec_reserve(vec, size) != VEC_OK) {
        vec_delete(vec);
        return (NULL);
    }
    return (vec);
}