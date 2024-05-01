NAME= libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

# TODO: 제출하기 전에 shell find 명령어를 사용하지 않도록 수정해야 함
SRCS := $(shell find . -name ft_\*.c | grep -v bonus) 
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I includes

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

