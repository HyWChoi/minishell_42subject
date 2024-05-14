# CC = Clang
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

srcs = $(shell find . -name "*.c" | grep -v "libft" | grep -v "src/tkshell.c" | grep -v "*test.c")
test_srcs = $(shell find . -name "*test.c")
OBJS := $(srcs:.c=.o)
NAME = tksh
TEST = test
TEST_EXEC = test_tksh
LIBFT = libs/libft/libft.a
READLINE_FLAGS = -lreadline


# arm architecture compatibility
ifeq ($(shell uname -p), arm)
	READLINE_PATH = -I /opt/homebrew/opt/readline/include
	READLINE_FLAGS += $(READLINE_PATH) -L/opt/homebrew/opt/readline/lib
endif

ifdef WITH_TEST
	srcs := $(test_srcs)
	NAME = $(TEST_EXEC)
else
	srcs := src/tkshell.c
endif

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libs -lft -I includes -I libft/includes $(READLINE_FLAGS)

$(TEST):
	@make WITH_TEST=1 all


$(LIBFT):
	make -C libft
	cp libft/libft.a libs/


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes $(READLINE_PATH)

clean:
	make -C libft clean
	rm -f $(OBJS)
	rm -rf */**.o

fclean: clean
	make -C libft fclean
	rm -f libs/libft.a
	rm -f $(NAME) $(TEST_EXEC)

re: fclean all

.PHONY: all clean fclean re

