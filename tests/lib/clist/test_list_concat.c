/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_concat
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

Test(list_concat, test_list_append)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list, "END");
    node_append(list, "END2");
    node_append(list2, "END3");
    node_append(list2, "END4");
    list_append(list, list2);
    cr_assert_eq(list->size, 4);
    cr_assert_str_eq(list->head->data, "END");
    cr_assert_str_eq(list->head->next->data, "END2");
    cr_assert_str_eq(list->head->next->next->data, "END3");
    cr_assert_str_eq(list->head->next->next->next->data, "END4");
    cr_assert_str_eq(list->tail->data, "END4");
}

Test(list_concat, test_list_append_empty_destlist)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list2, "END3");
    node_append(list2, "END4");
    cr_assert_eq(list2->size, 2);
    list_append(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 2);
    cr_assert_str_eq(list->head->data, "END3");
    cr_assert_str_eq(list->head->next->data, "END4");
    cr_assert_str_eq(list->tail->data, "END4");
}

Test(list_concat, test_list_append_empty_srclist)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list, "END");
    node_append(list, "END2");
    cr_assert_eq(list->size, 2);
    list_append(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 2);
    cr_assert_str_eq(list->head->data, "END");
    cr_assert_str_eq(list->head->next->data, "END2");
    cr_assert_str_eq(list->tail->data, "END2");
}

Test(list_concat, test_list_append_empty_lists)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    list_append(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 0);
}

Test(list_concat, test_list_insert)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list, "END");
    node_append(list, "END2");
    node_append(list2, "END3");
    node_append(list2, "END4");
    list_insert(list, list2);
    cr_assert_eq(list->size, 4);
    cr_assert_str_eq(list->head->data, "END3");
    cr_assert_str_eq(list->head->next->data, "END4");
    cr_assert_str_eq(list->head->next->next->data, "END");
    cr_assert_str_eq(list->head->next->next->next->data, "END2");
    cr_assert_str_eq(list->tail->data, "END2");
}

Test(list_concat, test_list_insert_empty_destlist)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list2, "END3");
    node_append(list2, "END4");
    cr_assert_eq(list2->size, 2);
    list_insert(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 2);
    cr_assert_str_eq(list->head->data, "END3");
    cr_assert_str_eq(list->head->next->data, "END4");
    cr_assert_str_eq(list->tail->data, "END4");
}

Test(list_concat, test_list_insert_empty_srclist)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    node_append(list, "END");
    node_append(list, "END2");
    cr_assert_eq(list->size, 2);
    list_insert(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 2);
    cr_assert_str_eq(list->head->data, "END");
    cr_assert_str_eq(list->head->next->data, "END2");
    cr_assert_str_eq(list->tail->data, "END2");
}

Test(list_concat, test_list_insert_empty_lists)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    list_insert(list, list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_eq(list->size, 0);
}
