/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_merge
*/

#include "vector.h"
#include <string.h>

vec_error_t vec_append(vector_t *dest, vector_t *src)
{
    size_t i = 0;

    if (dest == NULL || src == NULL) {
        return (VEC_NULLPTR);
    }
    if (vec_reserve(dest, src->nmemb) != VEC_OK) {
        return (VEC_ALLOC);
    }
    for (; i < src->nmemb; i++) {
        vec_push(dest, src->items + (i * src->item_size));
    }
    vec_clear(src);
    return (VEC_OK);
}

vector_t *vec_split_off(vector_t *vec, size_t index)
{
    vector_t *new_vec = NULL;

    if (vec == NULL || index >= vec->nmemb) {
        return (NULL);
    }
    new_vec = vec_with_capacity(
        vec->nmemb - index, vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL) {
        return (NULL);
    }
    memcpy(new_vec->items, vec->items + (index * vec->item_size),
        (vec->nmemb - index) * vec->item_size);
    new_vec->nmemb = vec->nmemb - index;
    memset(vec->items + (index * vec->item_size), 0,
        (vec->nmemb - index) * vec->item_size);
    vec->nmemb = index;
    return (new_vec);
}
