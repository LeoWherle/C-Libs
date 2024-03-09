##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

include config.mk

BEGINL		= 	\033[A
CLEARL		= 	\033[2K
COL_END		= 	\033[0m
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

BUILD_DIR = ../build/
CC = gcc

SRC 	=	src/chained_list_concat.c		\
			src/chained_list_create.c 	\
			src/chained_list_data_destructor.c	\
			src/chained_list_destroy.c	\
			src/chained_list_exec.c	\
			src/chained_list_find.c	\
			src/chained_list_print.c	\
			src/chained_list_remove.c	\
			src/chained_list_build.c	\
			src/chained_list_dup.c	\

CRIT_LIST	=	../tests/lib/clist/test_list_init.c \
				../tests/lib/clist/test_list_concat.c \
				../tests/lib/clist/test_list_data_destructor.c \
				../tests/lib/clist/test_list_destroy.c \
				../tests/lib/clist/test_list_exec.c \
				../tests/lib/clist/test_list_find.c \
				../tests/lib/clist/test_list_print.c \
				../tests/lib/clist/test_list_remove.c \
				../tests/lib/clist/test_list_build.c \
				../tests/lib/clist/test_list_dup.c \
				../tests/lib/clist/test_string.c \

SRC_CRIT = $(SRC)
TEST_CRIT = $(CRIT_LIST)

OBJ = 	$(SRC:%.c=$(BUILD_DIR)$(NAME)/%.o)
OBJ_CRIT = $(CRIT_LIST:%.c=$(BUILD_DIR)$(NAME)/%.o)
OBJ_SRC_CRIT = $(SRC:%.c=$(BUILD_DIR)tests/$(NAME)/%.o)
DEPS = 	$(OBJ:%.o=%.d)


CFLAGS = -W -Wall -Wextra -Iinclude
CRITFLAGS = -lcriterion --coverage

ifeq ($(DEBUG), n)
	CFLAGS += -O2
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS = -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
else
	CFLAGS += -g
endif

$(BUILD_DIR)tests/$(NAME)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@

$(BUILD_DIR)$(NAME)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@

$(BUILD_DIR)$(LIBNAME): $(OBJ)
	ar rc $(BUILD_DIR)$(LIBNAME) $(OBJ)
	@echo "$(GREEN)✓ Compiled $(LIBNAME)$(RESET)"

all:	$(LIBNAME)

clean:
	@rm -f $(OBJ) *~ *.gcno *.gcda #*#
	@echo "[$(YELLOW)Cleaned $(LIBNAME)$(RESET)]"

fclean: clean
	@rm -f $(BUILD_DIR)$(LIBNAME)
	@rm -f unit-tests
	@echo "[$(YELLOW)Fcleaned $(LIBNAME)$(RESET)]"

re: fclean all

tests_run: $(CFLAGS) += $(CRITFLAGS)
tests_run: $(OBJ_CRIT) $(OBJ_SRC_CRIT)
	@gcc -o unit-tests $(OBJ_SRC_CRIT) $(OBJ_CRIT) $(CFLAGS) $(CRITFLAGS)
	@echo "[$(GREEN)Launch tests $(LIBNAME)$(RESET)]"
	@./unit-tests

.PHONY: all clean fclean re

-include $(DEPS)
