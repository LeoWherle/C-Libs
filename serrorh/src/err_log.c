/*
** EPITECH PROJECT, 2024
** ntml-lib [WSL: fedora]
** File description:
** err_log
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "serrorh.h"

static const char *level_str_color[] = {RED, MAGENTA, BLUE, YELLOW, GREEN};
static const char *level_str[] = {
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "TRACE",
};

static enum LogLevel global_log_level(enum LogLevel level, bool set)
{
    static enum LogLevel global_verbose_mode = LG_INFO;

    if (set) {
        global_verbose_mode = level;
    }
    return global_verbose_mode;
}

void log_set_level(enum LogLevel level)
{
    (void) global_log_level(level, 1);
}

int log_msg(enum LogLevel level, const char *__restrict format, ...)
{
    int ret = 0;
    va_list args;

    if ((unsigned int) level <= global_log_level(0, 0)) {
        va_start(args, format);
        ret += fprintf(stdout, "[%s" BOLD "%s" RESET "] ",
            level_str_color[level], level_str[level]);
        ret += vfprintf(stdout, format, args);
        ret += fprintf(stdout, "\n");
        va_end(args);
    }
    return ret;
}

void expr_assert(int expr, const char *str)
{
    if (!expr) {
        log_msg(LG_ERROR, "Assertion failed: %s", str);
    }
}
