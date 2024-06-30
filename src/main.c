/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** main
*/

#include "vector.h"
#include <stdio.h>

bool int_eq(const void *a, const void *b)
{
    return (*(int *) a == *(int *) b);
}

int vec_int_cmp(const void *a, const void *b)
{
    return (*(int *) a - *(int *) b);
}

int main(int ac, char *av[])
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    int tab[] = {1, 27, 3, 6, 5, 6, 5, 8, 1, 10};

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            perror("Error");
            return (84);
        }
    }
    if (vec_reserve(vec, 2000) != BUF_OK) {
        perror("Error");
        return (84);
    }
    printf("capacity: %ld\n", vec->capacity);
    vec_dedup(vec, &int_eq);
    vec_sort(vec, &vec_int_cmp);
    vec_print_int(vec);
    printf("\n");
    vec_delete(vec);
    return (0);
}
