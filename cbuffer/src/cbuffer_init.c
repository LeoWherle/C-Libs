/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cbuffer_init
*/

#include <stdlib.h>
#include "cbuffer.h"

// returns 0 on success, 1 otherwise
static int cbuffer_init(cbuffer_t *buffer, size_t size)
{
    buffer->size = size;
    buffer->data = malloc(sizeof(char) * size);
    if (!buffer->data)
        return 0;
    return 1;
}

cbuffer_t *cbuffer_create(size_t size)
{
    cbuffer_t *buffer = NULL;

    buffer = malloc(sizeof(cbuffer_t));
    if (!buffer)
        return NULL;
    if (!cbuffer_init(buffer, size)) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

void cbuffer_destroy(cbuffer_t *buffer)
{
    free(buffer->data);
    free(buffer);
}
