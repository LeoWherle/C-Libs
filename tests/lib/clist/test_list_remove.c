/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_remove
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "clist.h"

Test(list_remove, test_list_remove_last_node)
{
    list_t *list = list_init();
    char *str = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");

    node_append(list, str);
    node_popf(list);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(list_remove, test_list_remove_first_node)
{
    list_t *list = list_init();
    char *str = NULL;
    char *str2 = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");

    node_append(list, str);
    node_append(list, str2);
    node_popf(list);
    cr_assert_eq(list->head->data, str2);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 1);
}

Test(list_remove, test_list_remove_empty)
{
    list_t *list = list_init();

    node_popf(list);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(list_remove, test_list_remove_middle_node_pop)
{
    list_t *list = list_init();
    char *str = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");
    node_append(list, str);
    node_append(list, str2);
    node_append(list, str3);
    node_pop(list, str2);
    cr_assert_eq(list->head->data, str);
    cr_assert_eq(list->head->next->data, str3);
    cr_assert_eq(list->tail->data, str3);
    cr_assert_eq(list->size, 2);
}

Test(list_remove, test_list_remove_first_node_pop_data)
{
    list_t *list = list_init();
    char *str = NULL;
    char *str2 = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");

    node_append(list, str);
    node_append(list, str2);
    node_pop(list, str);
    cr_assert_eq(list->head->data, str2);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 1);
}

Test(list_remove, test_list_remove_last_node_pop_data)
{
    list_t *list = list_init();
    char *str = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");

    node_append(list, str);
    node_append(list, str2);
    node_append(list, str3);
    node_pop(list, str3);
    cr_assert_eq(list->head->data, str);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 2);
}

Test(list_remove, test_list_remove_last_node_pop)
{
    list_t *list = list_init();
    char *str = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");

    node_append(list, str);
    node_append(list, str2);
    node_append(list, str3);
    node_pop(list, NULL);
    cr_assert_eq(list->head->data, str);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 2);
}

Test(list_remove, test_list_remove_empty_pop)
{
    list_t *list = list_init();

    node_pop(list, NULL);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(list_remove, test_list_remove_empty_pop2)
{
    list_t *list = list_init();
    char *str = NULL;
    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");
    node_t *node = node_init(str);

    node_pop(list, node);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(list_remove, test_list_remove_one_pop)
{
    list_t *list = list_init();
    char *str = NULL;
    str = malloc(sizeof(char) * 6);
    strcpy(str, "test1");

    node_append(list, str);
    node_pop(list, NULL);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}
