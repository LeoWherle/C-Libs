/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** log_file
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "serrorh.h"

FILE *global_log_file(bool set, FILE *value)
{
    static FILE *log_file = NULL;

    if (set) {
        log_file = value;
    }
    return log_file;
}

static bool load_env_log_file_open(const char *log_file)
{
    FILE *file = NULL;

    if (access(log_file, F_OK) == 0)
        remove(log_file);
    file = fopen(log_file, "a");
    if (file == NULL) {
        LOG_ERROR("Failed to open log file %s", log_file);
        return false;
    }
    LOG_TRACE("Loaded log file \"%s\"", log_file);
    global_log_file(true, file);
    return true;
}

void load_env_log_file(void)
{
    char *log_file = getenv(LOG_FILE_ENV);
    bool loaded = false;

    printf("log_file: %s\n", log_file);
    fflush(stdout);
    if (log_file != NULL && log_file[0] != '\0') {
        loaded = load_env_log_file_open(log_file);
    }
    if (!loaded) {
        global_log_file(true, stdout);
    }
}
