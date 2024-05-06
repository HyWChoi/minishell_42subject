# CC = Clang
CC = cc
CFLAGS = -Wall -Wextra

srcs = $(shell find . -name "*.c" | grep -v "libft" | grep -v "src/tkshell.c" | grep -v "*test.c")
test_srcs = $(shell find . -name "*test.c")
OBJS := $(srcs:.c=.o)
NAME = tksh
TEST = test
TEST_EXEC = test_tksh
LIBFT = libs/libft/libft.a

ifdef WITH_TEST
	srcs := $(test_srcs)
	NAME = $(TEST_EXEC)
else
	srcs := src/tkshell.c
endif

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libs -lft -I includes -I libft/includes -lreadline

$(TEST):
	@make WITH_TEST=1 all


$(LIBFT):
	make -C libft
	cp libft/libft.a libs/


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes

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

