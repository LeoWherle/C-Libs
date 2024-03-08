/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_remove
*/

#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

vec_error_t vec_insert(vector_t *vec, const void *elem, size_t index)
{
    if (vec == NULL)
        return (VEC_NULLPTR);
    if (index > vec->nmemb)
        return (VEC_INDEX);
    if (vec_reserve(vec, 1) != VEC_OK)
        return (VEC_ALLOC);
    if (index < vec->nmemb) {
        memmove(vec->items + ((index + 1) * vec->item_size),
            vec->items + (index * vec->item_size),
            (vec->nmemb - index) * vec->item_size);
    }
    if (vec->cpctor != NULL) {
        vec->cpctor(vec->items + (index * vec->item_size), elem);
    } else {
        memcpy(vec->items + (index * vec->item_size), elem, vec->item_size);
    }
    vec->nmemb++;
    return (VEC_OK);
}

static void vec_remove_element(vector_t *vec, size_t index, void *item)
{
    if (vec->dtor != NULL) {
        vec->dtor(item);
    }
    if (index != vec->nmemb - 1) {
        memmove(item, item + vec->item_size,
            (vec->nmemb - index - 1) * vec->item_size);
    }
    vec->nmemb--;
}

static bool is_valid_index(const vector_t *vec, size_t index)
{
    return (vec != NULL && index < vec->nmemb);
}

vec_error_t vec_delete_at(vector_t *vec, size_t index)
{
    void *item = NULL;

    if (!is_valid_index(vec, index)) {
        return (VEC_INDEX);
    }
    item = vec->items + (index * vec->item_size);
    vec_remove_element(vec, index, item);
    return (VEC_OK);
}

void *vec_remove(vector_t *vec, size_t index)
{
    void *item = NULL;
    void *copy = NULL;

    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    copy = malloc(vec->item_size);
    if (copy == NULL)
        return (NULL);
    item = vec->items + (index * vec->item_size);
    copy = memcpy(copy, item, vec->item_size);
    vec_remove_element(vec, index, item);
    return (copy);
}

void *vec_swap_remove(vector_t *vec, size_t index)
{
    void *item = NULL;
    void *copy = NULL;

    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    copy = malloc(vec->item_size);
    if (copy == NULL) {
        return (NULL);
    }
    item = vec->items + (index * vec->item_size);
    copy = memcpy(copy, item, vec->item_size);
    if (vec->dtor != NULL)
        vec->dtor(item);
    if (index != vec->nmemb - 1) {
        memmove(
            item, item + ((vec->nmemb - 1) * vec->item_size), vec->item_size);
    }
    vec->nmemb--;
    return (copy);
}

void *vec_at(const vector_t *vec, size_t index)
{
    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    return (vec->items + (index * vec->item_size));
}
