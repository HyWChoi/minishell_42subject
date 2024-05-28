# CC = Clang
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

srcs = $(shell find . -name "*.c" | grep -v "libft" | grep -v "src/tkshell.c" | grep -v "test")
# test_main = $(shell find . -name "*test.c")
test_main = src/__test__/shell/main.c
OBJS := $(srcs:.c=.o)
NAME = tksh
TEST = test
TEST_EXEC = test_tksh

PARSE = parse
prs_test_main = src/__test__/parse/main.c
prs_srcs = src/__test__/parse/prs_init.c src/__test__/parse/prs_stack.c
prs_TEST_EXEC = prs_test

EXECUTE = excute
execute_test_main = src/__test__/excute/main.c
EXECUTE_TEST_EXEC = excute_test

LIBFT = libs/libft/libft.a
READLINE_FLAGS = -lreadline


# arm architecture compatibility
ifeq ($(shell uname -p), arm)
	READLINE_PATH = -I /opt/homebrew/opt/readline/include
	READLINE_FLAGS += $(READLINE_PATH) -L/opt/homebrew/opt/readline/lib
endif

ifdef WITH_TEST
	srcs += $(test_main)
	OBJS := $(srcs:.c=.o)
	NAME = $(TEST_EXEC)
else
	ifdef WITH_PARSE
		srcs += $(prs_test_main) $(prs_srcs)
		OBJS := $(srcs:.c=.o)
		NAME = $(prs_TEST_EXEC)
	else
		ifdef WITH_EXCUTE
			srcs += src/__test__/excute/main.c
			OBJS := $(srcs:.c=.o)
			NAME = $(EXECUTE_TEST_EXEC)
		else
			srcs += src/tkshell.c
			OBJS := $(srcs:.c=.o)
			NAME = tksh
		endif
	endif
endif


all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libs -lft -I includes -I libft/includes $(READLINE_FLAGS)

$(TEST):
	@make WITH_TEST=1 all

$(PARSE):
	@make WITH_PARSE=1 all

$(EXECUTE):
	@make WITH_EXCUTE=1 all

$(LIBFT):
	make -C libft
	cp libft/libft.a libs/


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes $(READLINE_PATH)

clean:
	make -C libft clean
	rm -f $(OBJS)
	rm -rf **/**.o

fclean: clean
	make -C libft fclean
	rm -f libs/libft.a
	rm -f $(NAME) $(TEST_EXEC) $(prs_TEST_EXEC) $(EXECUTE_TEST_EXEC)

re: fclean all

.PHONY: all clean fclean re
