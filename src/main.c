/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** main
*/

#include "vector.h"
#include <stdio.h>

void print_int(const void *data)
{
    printf("%d", *(int *) data);
}

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

    for (int i = 0; i < 10; i++) {
        if (vec_push(vec, &tab[i]) != VEC_OK) {
            printf("Error\n");
            return (84);
        }
    }
    vec_dedup(vec, &int_eq);
    vec_sort(vec, &vec_int_cmp);
    vec_print(vec, &print_int, NULL);
    printf("\n");
    vec_delete(vec);
    return (0);
}
