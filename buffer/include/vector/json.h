/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** json
*/

#pragma once

#include "sstrings.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/********** Helper functions AND Macros to print vectors as JSON **********/

/**
 * @brief prints a key-value pair to a file
 *
 * @param file the file to print to
 * @param name the key
 * @param value the value
 *
 * @note only supports print in a single line
 *
 * @example
 * typedef struct human_s {
 *     string_t name;
 *     bool adult;
 * } human_t;
 *
 * typedef struct test_s {
 *     int a;
 *     human_t king;
 *     vector_t humans;
 * } test_t;
 *
 * static
 * void jsn_obj_fprint_human_t(
 *     file_data_t file, const char *name, human_t *data)
 * {
 *     JSON_OBJ_BEGIN(file, name);
 *     JSON_PRINT(string_t, file, data, name);
 *     JSON_OBJ_SEP(file);
 *     JSON_PRINT(bool, file, data, adult);
 *     JSON_OBJ_END(file);
 * }
 *
 * static
 * void jsn_obj_fprint_test_t(
 *     file_data_t file, const char *name, test_t *data)
 * {
 *     JSON_OBJ_BEGIN(file, name);
 *     JSON_PRINT(int, file, data, a);
 *     JSON_OBJ_SEP(file);
 *     JSON_PRINT(human_t, file, data, king);
 *     JSON_OBJ_SEP(file);
 *     JSON_PRINT_VEC(file, data, humans, human_t);
 *     JSON_OBJ_END(file);
 * }
 *
 * int main(int ac, char *av[])
 * {
 *     test_t test = {42, .king = {.adult = true}};
 *     human_t human = {.adult = false};
 *
 *     // Create a test object
 *     {
 *         if (str_init(&human.name, "randomguy") != 0)
 *             return 1;
 *         if (str_init(&test.king.name, "test") != 0)
 *             return 1;
 *         if (vec_init(&test.humans, sizeof(human), NULL, NULL) != 0)
 *             return 1;
 *         if (vec_push(&test.humans, &human) != 0)
 *             return 1;
 *         str_clear(&human.name);
 *         if (str_init(&human.name, "clone") != 0)
 *             return 1;
 *         if (vec_push(&test.humans, &human) != 0)
 *             return 1;
 *         if (vec_extend_with(&test.humans, &human, 5) != 0)
 *             return 1;
 *     }
 *     jsn_obj_fprint_test_t(stdout, NULL, &test);
 *     fflush(stdout);
 *     // memory leaks but it's just an example
 *     return 0;
 * }
 */
#ifdef VEC_JSON_PRINT_DESCRIPTORS
    #define JFPRINTF dprintf
typedef int file_data_t;
#elif VEC_JSON_PRINT_CUSTOM
    #ifndef JFPRINTF
        #error "VEC_JSON_PRINT_CUSTOM is defined but JFPRINTF is not defined"
    #endif
#else /* VEC_JSON_PRINT_STREAM */
    #define JFPRINTF fprintf
typedef FILE *file_data_t;
#endif

// JSON_FUNCTION_NAME(type)
#define JF(t) jsn_obj_fprint_##t

#define JSON_PRINT(t, f, strc, vl) JF(t)(f, #vl, &(strc)->vl)
#define JSON_PRINT_VEC(f, s, v, n) json_print_vec(f, #v, &(s)->v, (jp_t) JF(n))

#define JSON_SEP(f)     JFPRINTF(f, ", ")
#define JSON_OBJ_SEP(f) JSON_SEP(f)
#define JSON_ARR_SEP(f) JSON_SEP(f)

#define JSON_OBJ_BEGIN(f, n) n ? JFPRINTF(f, "\"%s\": {", n) : JFPRINTF(f, "{")
#define JSON_OBJ_END(f)      JFPRINTF(f, "}")

#define JSON_ARR_BEGIN(f, n) n ? JFPRINTF(f, "\"%s\": [", n) : JFPRINTF(f, "[")
#define JSON_ARR_END(f)      JFPRINTF(f, "]")

typedef const char *cstring_t;

void jsn_obj_fprint_int(file_data_t file, const char *name, int *);
void jsn_obj_fprint_float(file_data_t file, const char *name, float *);
void jsn_obj_fprint_double(file_data_t file, const char *name, double *);
void jsn_obj_fprint_long(file_data_t file, const char *name, long *);
void jsn_obj_fprint_uint32_t(file_data_t file, const char *name, uint32_t *);
void jsn_obj_fprint_uint64_t(file_data_t file, const char *name, uint64_t *);
void jsn_obj_fprint_int32_t(file_data_t file, const char *name, int32_t *);
void jsn_obj_fprint_int64_t(file_data_t file, const char *name, int64_t *);
void jsn_obj_fprint_size_t(file_data_t file, const char *name, size_t *);
void jsn_obj_fprint_ssize_t(file_data_t file, const char *name, ssize_t *);

void jsn_obj_fprint_bool(file_data_t file, const char *name, bool *);
void jsn_obj_fprint__Bool(file_data_t file, const char *name, bool *);

void jsn_obj_fprint_string_t(file_data_t file, const char *name, string_t *);
void jsn_obj_fprint_cstring_t(file_data_t file, const char *name, cstring_t *);

typedef void (*jp_t)(file_data_t f, char *n, void *d);

void json_print_vec(
    file_data_t file, const char *name, vector_t *vec, jp_t print);
