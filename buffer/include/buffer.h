/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** buffer
*/

#pragma once

#include "vector.h"

typedef struct buffer_s {
    vector_t vector;
    size_t pos;
    size_t filled;
} buffer_t;
