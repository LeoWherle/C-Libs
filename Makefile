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
SRC = $(shell find src/ -name "*.c" -type f)

OBJ = 	$(SRC:%.c=$(BUILD_DIR)%.o)
DEPS = 	$(OBJ:%.o=%.d)


LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
LIB_FLAGS = -L$(BUILD_DIR) $(addprefix -l, $(LIBS))

CFLAGS = -W -Wall -Wextra -Iinclude $(LIBINC)
LDFLAGS =
CRITFLAGS = -lcriterion --coverage

FLAGS =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	CFLAGS += -O2
	FLAGS = "DEBUG=n"
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS = -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	FLAGS = "DEBUG=y"
else
	CFLAGS += -g
endif


$(BUILD_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@

$(NAME): lib_build	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIB_FLAGS)

all:	$(NAME)
	@echo "$(GREEN)✓ Compiled $(NAME)$(RESET)"

lib_build:
	@for i in $(LIBS); do $(MAKE) -C $$i $(RULE); done

clean:
	@rm -f $(OBJ) *~ *.gcno *.gcda #*#
	@for i in $(LIBS); do $(MAKE) -C $$i clean; done

fclean: clean
	@rm -f $(NAME)
	@rm -f unit-tests
	@for i in $(LIBS); do $(MAKE) -C $$i fclean; done

re: fclean all

tests_run:
	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done

.PHONY: all clean fclean re debug tests_run lib_build

-include $(DEPS)
