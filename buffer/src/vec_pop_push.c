/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_pop_push
*/

#include "vector.h"
#include <string.h>

vec_error_t vec_push(vector_t *vec, const void *item)
{
    if (vec == NULL || item == NULL) {
        return (VEC_NULLPTR);
    }
    if (vec_reserve(vec, 1) != VEC_OK) {
        return (VEC_ALLOC);
    }
    if (vec->cpctor != NULL) {
        vec->cpctor(vec->items + (vec->nmemb * vec->item_size), item);
    } else {
        memcpy(
            vec->items + (vec->nmemb * vec->item_size), item, vec->item_size);
    }
    vec->nmemb++;
    return (VEC_OK);
}

vec_error_t vec_pop(vector_t *vec)
{
    if (vec == NULL) {
        return (VEC_NULLPTR);
    }
    if (vec->nmemb == 0) {
        return (VEC_EMPTY);
    }
    if (vec->dtor != NULL) {
        vec->dtor(vec->items + ((vec->nmemb - 1) * vec->item_size));
    }
    vec->nmemb--;
    return (VEC_OK);
}
