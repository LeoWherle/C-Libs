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
    vector_t *vec = NULL;

    vec = malloc(sizeof(vector_t));
    if (vec == NULL) {
        return (NULL);
    }
    vec->dtor = dtor;
    vec->cpctor = cpctor;
    vec->item_size = elem_size;
    vec->items = malloc(VEC_INIT_CAPACITY * elem_size);
    if (vec->items == NULL) {
        free(vec);
        return (NULL);
    }
    vec->nmemb = 0;
    vec->capacity = VEC_INIT_CAPACITY;
    return (vec);
}

vec_error_t vec_reserve(vector_t *vec, size_t additional)
{
    u_char *items_new = NULL;
    size_t new_capacity = 0;

    if (vec == NULL) {
        return (VEC_NULLPTR);
    }
    new_capacity = vec->nmemb + additional;
    if (new_capacity > vec->capacity) {
        new_capacity *= 2;
        items_new = reallocarray(vec->items, new_capacity, vec->item_size);
        if (items_new == NULL) {
            return (VEC_ALLOC);
        }
        vec->capacity = new_capacity;
        vec->items = items_new;
    }
    return (VEC_OK);
}

vector_t *vec_with_capacity(
    size_t size, size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    vector_t *vec = NULL;

    vec = vec_new(elem_size, dtor, cpctor);
    if (vec == NULL) {
        return (NULL);
    }
    if (vec_reserve(vec, size) != VEC_OK) {
        vec_delete(vec);
        return (NULL);
    }
    return (vec);
}

vector_t *vec_clone(const vector_t *vec)
{
    vector_t *new_vec = NULL;

    if (vec == NULL) {
        return (NULL);
    }
    new_vec =
        vec_with_capacity(vec->nmemb, vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL) {
        return (NULL);
    }
    if (vec->cpctor != NULL) {
        for (size_t i = 0; i < vec->nmemb; i++) {
            vec->cpctor(new_vec->items + (i * vec->item_size),
                vec->items + (i * vec->item_size));
        }
    } else {
        memcpy(new_vec->items, vec->items, vec->nmemb * vec->item_size);
    }
    new_vec->nmemb = vec->nmemb;
    return (new_vec);
}

vec_error_t vec_extend_with(vector_t *vec, const void *element, size_t n)
{
    if (vec == NULL || element == NULL) {
        return (VEC_NULLPTR);
    }
    if (vec_reserve(vec, n) != VEC_OK) {
        return (VEC_ALLOC);
    }
    if (vec->cpctor != NULL) {
        for (size_t i = 0; i < n; i++) {
            vec->cpctor(
                vec->items + ((vec->nmemb + i) * vec->item_size), element);
        }
    } else {
        for (size_t i = 0; i < n; i++) {
            memcpy(vec->items + ((vec->nmemb + i) * vec->item_size), element,
                vec->item_size);
        }
    }
    vec->nmemb += n;
    return (VEC_OK);
}
