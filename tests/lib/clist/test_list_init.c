/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** test_list_init
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

Test(node_init, test_node_init)
{
    node_t *node = NULL;
    node = node_init(NULL);

    cr_assert_not_null(node);
    cr_assert_null(node->data);
    cr_assert_null(node->next);
}


Test(list_init, test_list_insert_empy_list)
{
    list_t *list = NULL;
    list = list_init();

    node_insert(list, "END");
    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}

Test(list_init, test_list_insert_list)
{
    list_t *list = NULL;
    list = list_init();

    node_insert(list, "END");
    node_insert(list, "MIDDLE");
    node_insert(list, "START");
    cr_assert_eq(list->size, 3);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->head->next->data, "MIDDLE");
    cr_assert_str_eq(list->head->next->next->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}

Test(list_init, test_list_append_empy_list)
{
    list_t *list = NULL;
    list = list_init();

    node_append(list, "START");
    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->tail->data, "START");
}

Test(list_init, test_list_append_list)
{
    list_t *list = NULL;
    list = list_init();

    node_append(list, "START");
    node_append(list, "MIDDLE");
    node_append(list, "END");
    cr_assert_eq(list->size, 3);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->head->next->data, "MIDDLE");
    cr_assert_str_eq(list->head->next->next->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}
