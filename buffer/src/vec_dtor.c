/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_dtor
*/

#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void vec_delete(vector_t *vec)
{
    size_t i = 0;

    if (vec == NULL) {
        return;
    }
    if (vec->dtor != NULL) {
        for (; i < vec->nmemb; i++) {
            vec->dtor(vec->items + (i * vec->item_size));
        }
    }
    free(vec->items);
    free(vec);
}

void vec_clear(vector_t *vec)
{
    size_t i = 0;

    if (vec == NULL) {
        return;
    }
    if (vec->dtor != NULL) {
        for (; i < vec->nmemb; i++) {
            vec->dtor(vec->items + (i * vec->item_size));
        }
    }
    memset(vec->items, 0, vec->nmemb * vec->item_size);
    vec->nmemb = 0;
}

void vec_retain_if(vector_t *vec, bool (*fun)(const void *))
{
    size_t i = 0;
    size_t j = 0;
    bool ret = false;

    if (vec == NULL || fun == NULL)
        return;
    for (; i < vec->nmemb; i++) {
        ret = fun(vec->items + (i * vec->item_size));
        if (ret) {
            memcpy(vec->items + (j * vec->item_size),
                vec->items + (i * vec->item_size), vec->item_size);
            j++;
        }
        if (!ret && vec->dtor != NULL) {
            vec->dtor(vec->items + (i * vec->item_size));
        }
    }
    memset(vec->items + (j * vec->item_size), 0,
        (vec->nmemb - j) * vec->item_size);
    vec->nmemb = j;
}

static size_t vec_remove_if_dup(vector_t *vec,
    bool (*eq)(const void *, const void *), size_t original, size_t other)
{
    size_t new_other = other;

    if (eq(VEC_AT(vec, original), VEC_AT(vec, other))) {
        if (vec->dtor != NULL) {
            vec->dtor(vec->items + (other * vec->item_size));
        }
        memcpy(VEC_AT(vec, other), VEC_AT(vec, other + 1),
            (vec->nmemb - other) * vec->item_size);
        vec->nmemb--;
        new_other--;
    }
    return new_other;
}

// TO TEST, should work though
void vec_dedup(vector_t *vec, bool (*eq)(const void *, const void *))
{
    size_t i = 0;
    size_t j = 0;

    if (vec == NULL || eq == NULL) {
        return;
    }
    for (; i < vec->nmemb; i++) {
        for (j = i + 1; j < vec->nmemb; j++) {
            j = vec_remove_if_dup(vec, eq, i, j);
        }
    }
}
