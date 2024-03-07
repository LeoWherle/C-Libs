/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cbuffer_get
*/

#include "cbuffer.h"

char cbuffer_getb(cbuffer_t *buffer, size_t pos)
{
    return buffer->data[pos % buffer->size];
}

short cbuffer_gets(cbuffer_t *buffer, size_t pos)
{
    short data = 0;

    data |= buffer->data[(pos + 0) % buffer->size] << 8;
    data |= buffer->data[(pos + 1) % buffer->size] << 0;
    return data;
}

int cbuffer_geti(cbuffer_t *buffer, size_t pos)
{
    int data = 0;

    data |= buffer->data[(pos + 0) % buffer->size] << 24;
    data |= buffer->data[(pos + 1) % buffer->size] << 16;
    data |= buffer->data[(pos + 2) % buffer->size] << 8;
    data |= buffer->data[(pos + 3) % buffer->size] << 0;
    return data;
}

void cbuffer_get(cbuffer_t *buffer, char *data, size_t size, size_t pos)
{
    size_t i = 0;

    for (; i < size; i++) {
        data[i] = buffer->data[(pos + i) % buffer->size];
    }
}
