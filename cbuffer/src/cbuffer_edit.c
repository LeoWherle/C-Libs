/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cbuffer_edit
*/

#include "cbuffer.h"

void cbuffer_setb(cbuffer_t *buffer, char data, size_t pos)
{
    buffer->data[(pos) % buffer->size] = data;
}

void cbuffer_sets(cbuffer_t *buffer, short data, size_t pos)
{
    buffer->data[(pos + 0) % buffer->size] = (data >> 8) & 0xFF;
    buffer->data[(pos + 1) % buffer->size] = (data >> 0) & 0xFF;
}

void cbuffer_seti(cbuffer_t *buffer, int data, size_t pos)
{
    buffer->data[(pos + 0) % buffer->size] = (data >> 24) & 0xFF;
    buffer->data[(pos + 1) % buffer->size] = (data >> 16) & 0xFF;
    buffer->data[(pos + 2) % buffer->size] = (data >> 8) & 0xFF;
    buffer->data[(pos + 3) % buffer->size] = (data >> 0) & 0xFF;
}

void cbuffer_set(cbuffer_t *buffer, void *data, size_t size, size_t pos)
{
    size_t i = 0;
    char *data_ptr = data;

    for (; i < size; i++) {
        buffer->data[(pos + i) % buffer->size] = data_ptr[i];
    }
}

void cbuffer_fill(cbuffer_t *buffer, char data)
{
    size_t i = 0;

    for (; i < buffer->size; i++) {
        buffer->data[i] = data;
    }
}
