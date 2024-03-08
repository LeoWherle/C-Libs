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

static bool vec_has_indentical(vector_t *vec, size_t pos,
    bool (*eq)(const void *, const void *), size_t *same_pos)
{
    size_t i = pos + 1;

    for (; i < vec->nmemb; i++) {
        if (eq(vec->items + (pos * vec->item_size),
                vec->items + (i * vec->item_size))) {
            *same_pos = i;
            return true;
        }
    }
    return false;
}

// TO TEST, should work though
void vec_dedup(vector_t *vec, bool (*eq)(const void *, const void *))
{
    size_t i = 0;
    size_t j = 0;
    bool ret = false;

    if (vec == NULL || eq == NULL)
        return;
    for (; i < vec->nmemb; i++) {
        ret = vec_has_indentical(vec, i, eq, &j);
        if (ret && vec->dtor != NULL) {
            vec->dtor(vec->items + (j * vec->item_size));
        }
        if (ret) {
            memmove(vec->items + (j * vec->item_size),
                vec->items + ((j + 1) * vec->item_size),
                (vec->nmemb - j - 1) * vec->item_size);
            vec->nmemb--;
        }
    }
}
