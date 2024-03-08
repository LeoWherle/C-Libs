/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_traverse
*/

#include "vector.h"
#include <stdlib.h>

void vec_foreach(vector_t *vec, void (*fun)(void *))
{
    size_t i = 0;

    if (vec == NULL || fun == NULL)
        return;
    for (; i < vec->nmemb; i++) {
        fun(vec->items + (i * vec->item_size));
    }
}

void vec_foreach_arg(vector_t *vec, void (*fun)(void *, void *), void *arg)
{
    size_t i = 0;

    if (vec == NULL || fun == NULL)
        return;
    for (; i < vec->nmemb; i++) {
        fun(vec->items + (i * vec->item_size), arg);
    }
}

void *vec_find(const vector_t *vec, bool (*fun)(const void *))
{
    size_t i = 0;

    if (vec == NULL || fun == NULL)
        return NULL;
    for (; i < vec->nmemb; i++) {
        if (fun(vec->items + (i * vec->item_size))) {
            return vec->items + (i * vec->item_size);
        }
    }
    return NULL;
}

void *vec_find_arg(
    const vector_t *vec, bool (*fun)(const void *, void *), void *arg)
{
    size_t i = 0;

    if (vec == NULL || fun == NULL)
        return NULL;
    for (; i < vec->nmemb; i++) {
        if (fun(vec->items + (i * vec->item_size), arg)) {
            return vec->items + (i * vec->item_size);
        }
    }
    return NULL;
}

size_t vec_count(const vector_t *vec, bool (*fun)(const void *))
{
    size_t i = 0;
    size_t count = 0;

    if (vec == NULL || fun == NULL)
        return 0;
    for (; i < vec->nmemb; i++) {
        if (fun(vec->items + (i * vec->item_size))) {
            count++;
        }
    }
    return count;
}
