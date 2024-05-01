# CC = Clang
CC = cc
CFLAGS = -Wall -Wextra

srcs = $(shell find . -name "*.c" | grep -v "libft")

OBJS = $(srcs:.c=.o)
NAME = tksh
LIBFT = libs/libft/libft.a


all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libs -lft -I includes -I libft/includes -lreadline

$(LIBFT): 
	make -C libft
	cp libft/libft.a libs/
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f libs/libft.a
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

