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

ifeq ($(DEBUG), n)
	CFLAGS += -O2 -march=native -mtune=native -flto -fwhole-program
	RULE = "DEBUG=n"
	BUILD_PATH := $(BUILD_DIR)release/
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS += -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	RULE = "DEBUG=y"
	BUILD_PATH := $(BUILD_DIR)asan/
else
	CFLAGS += -g -fanalyzer -Wanalyzer-too-complex
	LDFLAGS += -fwhole-program -flto
	BUILD_PATH := $(BUILD_DIR)debug/
endif

SRC 	=	src/cbuffer_init.c \
			src/cbuffer_edit.c \
			src/cbuffer_get.c \


CRIT_LIST	=	\

SRC_CRIT = $(SRC)
TEST_CRIT = $(CRIT_LIST)

OBJ = 	$(SRC:%.c=$(BUILD_PATH)$(NAME)/%.o)
DEPS = 	$(OBJ:%.o=%.d)

CFLAGS = -W -Wall -Wextra -Iinclude
CFLAGS += -MMD -MP
CRITFLAGS = -lcriterion --coverage

$(BUILD_PATH)$(NAME)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -c -o $@

$(BUILD_PATH)$(LIBNAME): $(OBJ)
	ar rc $(BUILD_PATH)$(LIBNAME) $(OBJ)
	@echo "$(GREEN)✓ Compiled $(LIBNAME)$(RESET)"

all:	$(LIBNAME)

-include $(DEPS)

clean:
	@rm -f $(OBJ) *~ *.gcno *.gcda #*#
	@echo "[$(YELLOW)Cleaned $(LIBNAME)$(RESET)]"

fclean: clean
	@rm -f $(BUILD_PATH)$(LIBNAME)
	@rm -f unit-tests
	@echo "[$(YELLOW)Fcleaned $(LIBNAME)$(RESET)]"

re: fclean all

tests_run:
	@gcc -o unit-tests $(SRC_CRIT) $(TEST_CRIT) $(CFLAGS) $(CRITFLAGS)
	@echo "[$(GREEN)Launch tests $(LIBNAME)$(RESET)]"
	@./unit-tests

.PHONY: all clean fclean re
.NOTPARALLEL: re
