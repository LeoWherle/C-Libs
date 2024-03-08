/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cvecfer
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef void (*dtor_t)(void *);
typedef void (*cpctor_t)(void);

typedef struct error_t {
    enum {
        VEC_OK = 0,
        VEC_ALLOC,
        VEC_INDEX,
        VEC_EMPTY,
        VEC_CAPACITY,
        VEC_SIZE,
        VEC_NULLPTR,
        VEC_INVALID,
    } code;
} error_t;

/**
 * @brief A vector struct
 *
 * @param data the data of the vector
 * @param data_size the size of each element in the vector
 * @param nmemb the number of elements in the vector
 * @param capacity the capacity of the vector
 * @param dtor the destructor function for the elements in the vector
 * @param cpctor the copy constructor function for the elements in the vector
 */
typedef struct vector_s {
    error_t error;
    u_char *data;
    size_t data_size;
    size_t nmemb;
    size_t capacity;
    dtor_t dtor;
    cpctor_t cpctor;
} vector_t;

/**
 * @brief creates a new vector with a given element size
 * @param dtor can be NULL if no destructor is needed
 */
vector_t *vec_new(size_t elem_size, dtor_t, cpctor_t);
void vec_delete(vector_t *vec);

/**
 * @brief preallocates memory for the vector
 * @return Sets the error code to VEC_ALLOC if the allocation fails
 */
error_t vec_reserve(vector_t *vec, size_t additional);

/**
 * @brief intialize a vector with preallocated memory of size * elem_size
 * @param dtor can be NULL if no destructor is needed
 */
vector_t *vec_with_capacity(size_t size, size_t elem_size, dtor_t, cpctor_t);

/**
 * @brief Removes an element from the vector and returns it. Places the last
 * element in the vector in the position of the removed element. Use vec_remove
 * if you want to keep the order of the elements.
 * @return The element is not deallocated, so the caller is responsible for
 * freeing it. (It is reallocated)
 */
void *vec_swap_remove(vector_t *vec, size_t index);

/**
 * @brief Inserts an element at position `index` within the vector, shifting
 * all elements after it to the right.
 * The element is copied into the vector, so the original can be safely
 * deallocated after the call if necessary.
 * @return Sets the error code to VEC_INDEX if the index is out of bounds
 */
error_t vec_insert(vector_t *vec, void *elem, size_t index);

/**
 * @brief Removes an element at position `index` within the vector, shifting
 * all elements after it to the left.
 * The element is not deallocated, so the caller is responsible for freeing it.
 */
void *vec_remove(vector_t *vec, size_t index);

/**
 * @brief Retains only the elements specified by the predicate.
 * In other words, remove all elements `e` for which `f(&e)` returns `false`.
 * This method operates in place, visiting each element exactly once in the
 * original order, and preserves the order of the retained elements.
 *
 * # Example
 * ```c
 * bool is_even(const void *elem) {
 *     return *(int *)elem % 2 == 0;
 * }
 *
 * int main() {
 *     vector_t *vec = vec_new(sizeof(int), NULL);
 *     for (int i = 0; i < 10; i++) {
 *         vec_push(vec, &i);
 *     }
 *     vec_retain_if(vec, is_even);
 *     for (size_t i = 0; i < vec_size(vec); i++) {
 *         printf("%d\n", *(int *)vec_get(vec, i));
 *     }
 *     vec_delete(vec);
 * }
 */
void vec_retain_if(vector_t *vec, bool (*f)(const void *));

/**
 * @brief Appends an element to the end of the vector.
 * The element is copied into the vector, so the original can be safely
 * deallocated after the call if necessary.
 */
error_t vec_push(vector_t *vec, void *elem);

/**
 * @brief Removes the last element from the vector and returns it.
 * The element is not deallocated, so the caller is responsible for freeing it.
 */
void *vec_pop(vector_t *vec);

/**
 * @brief Moves all the elements of `dest` into `src` leaving `dest` empty.
 * The elements are copied into `dest`, and the original elements from `src`
 * are deallocated.
 */
void vec_append(vector_t *dest, vector_t *src);

/**
 * @brief Clears the vector, deallocating all elements.
 */
void vec_clear(vector_t *vec);

void vec_is_empty(vector_t *vec);

/**
 * @brief Splits the collection into two at the given index.
 * Returns a newly allocated vector containing the elements in the range
 * `[at, len)`. After the call, the original vector will be left containing
 * the elements `[0, at)` with its previous capacity unchanged.
 * @return The newly allocated vector containing the elements in the range
 * `[at, len)`. Or NULL if the allocation fails (and the original vector is
 * unchanged).
 */
vector_t *vec_split_off(vector_t *vec, size_t at);

/**
 * @brief Extend the vector by `n` clones of value.
 */
error_t vec_extend_with(vector_t *vec, const void *element);

/**
 * @brief Removes consecutive repeated elements from the vector. Uses the
 * provided equality function to determine whether two elements are equal.
 */
void vec_dedup(vector_t *vec, bool (*eq)(const void *, const void *));

/**
 * @brief Duplicates the input vector. The elements are copied into the new
 * vector, so the original can be safely deallocated after the call if
 * necessary.
 */
vector_t *vec_clone(const vector_t *vec);

vector_t *vec_print(
    const vector_t *vec, void (*print)(const void *), char *sep);

// Uses qsort_r
void *vec_sort(vector_t *vec, int (*cmp)(const void *, const void *));

void vec_foreach(vector_t *vec, void (*f)(void *));
// Use a local struct to pass multiple arguments to the function if needed
void vec_foreach_with_arg(vector_t *vec, void (*f)(void *, void *), void *arg);

void *vec_find(const vector_t *vec, bool (*f)(const void *, const void *),
    const void *match);

/**
 * @brief Returns a new vector containing the elements of the original vector
 * for which the predicate returns `true`.
 */
vector_t *vec_filter(const vector_t *vec,
    bool (*f)(const void *, const void *), const void *match);

vector_t *vec_map(const vector_t *vec, void *(*f)(const void *) );

// Use a local struct to pass multiple arguments to the function if needed
vector_t *vec_map_with_arg(
    const vector_t *vec, void *(*f)(const void *, void *), void *arg);

// UNSAFE, use with caution (no bounds checking) and only if you know what you
// are doing
void *vec_get(const vector_t *vec, size_t index);
