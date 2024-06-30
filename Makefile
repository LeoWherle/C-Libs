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
CLEAR_COL	=	\033[2K\033[A
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

BUILD_DIR = build/

MAKE  = make --no-print-directory
CC = gcc

RULE =
# used with make DEBUG=n
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
	CFLAGS += -g -fanalyzer
	LDFLAGS += -fwhole-program -flto
	BUILD_PATH := $(BUILD_DIR)debug/
endif

SRC = $(shell find src/ -name "*.c" -type f)

OBJ = 	$(SRC:%.c=$(BUILD_DIR)%.o)
DEPS = 	$(OBJ:%.o=%.d)

LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
LIB_FLAGS = -L$(BUILD_PATH) $(addprefix -l, $(LIBS))

CFLAGS += -W -Wall -Wextra -Iinclude $(LIBINC)
CFLAGS += -MMD -MP
LDFLAGS += $(LIB_FLAGS)
CRITFLAGS = -lcriterion --coverage

$(BUILD_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): lib_build	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

all:	$(NAME)
	@echo "$(GREEN)✓ Compiled $(NAME)$(RESET)"

-include $(DEPS_SERV)

lib_build:
	@for i in $(LIBS); do $(MAKE) -C $$i $(RULE); done

clean:
	@rm -rf $(BUILD_DIR)asan $(BUILD_DIR)debug $(BUILD_DIR)release
	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i clean $$j; done \
	done

fclean: clean
	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i fclean $$j; done \
	done
	@rm -f unit-tests
	@rm -f $(BIN)
	@rm -f $(BUILD_DIR)asan/$(BIN)
	@rm -f $(BUILD_DIR)debug/$(BIN)
	@rm -f $(BUILD_DIR)release/$(BIN)
	@rm -f ../server.log

re: fclean all

tests_run:
	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done

.PHONY: all clean fclean re debug tests_run lib_build
.NOTPARALLEL: re