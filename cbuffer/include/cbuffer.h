/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cbuffer
*/

#ifndef CBUFFER_H_
    #define CBUFFER_H_

    #include <stddef.h>

typedef struct cbuffer_s {
    char *data;
    size_t size;
} cbuffer_t;

cbuffer_t *cbuffer_create(size_t size);
void cbuffer_destroy(cbuffer_t *buffer);

void cbuffer_setb(cbuffer_t *buffer, char data, size_t pos);
/**
 * @brief Set data in buffer at pos from data
 *
 * @param buffer the buffer to set data in
 * @param data the data to set
 * @param size the size of data to set (must be <= data len)
 * @param pos the position to set data at
 */
void cbuffer_set(cbuffer_t *buffer, void *data, size_t size, size_t pos);

char cbuffer_getb(cbuffer_t *buffer, size_t pos);
short cbuffer_gets(cbuffer_t *buffer, size_t pos);
int cbuffer_geti(cbuffer_t *buffer, size_t pos);

/**
 * @brief Get data from buffer at pos and store it in data
 *
 * @param buffer the buffer to get data from
 * @param data the data to store the result in (must be allocated)
 * @param size the size of data to get
 * @param pos the position to get data from
 */
void cbuffer_get(cbuffer_t *buffer, char *data, size_t size, size_t pos);

void cbuffer_fill(cbuffer_t *buffer, char data);
#endif /* !CBUFFER_H_ */
