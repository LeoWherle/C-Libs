/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_dtor
*/

#include "vector.h"
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

    if (vec == NULL || fun == NULL) {
        return;
    }
    for (; i < vec->nmemb; i++) {
        if (fun(vec->items + (i * vec->item_size))) {
            memcpy(vec->items + (j * vec->item_size),
                vec->items + (i * vec->item_size), vec->item_size);
            j++;
        } else if (vec->dtor != NULL) {
            vec->dtor(vec->items + (i * vec->item_size));
        }
    }
    memset(vec->items + (j * vec->item_size), 0,
        (vec->nmemb - j) * vec->item_size);
    vec->nmemb = j;
}
