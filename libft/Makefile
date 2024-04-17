NAME= libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
# TODO: 제출하기 전에 shell find 명령어를 사용하지 않도록 수정해야 함
SRCS := $(shell find . -name ft_\*.c | grep -v bonus)

SRCS := get_next_line/get_next_line.c \
		$(SRCS) \
		$(shell find addons -name ft_\*.c)
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(@:.o=.c) -o $@ -I includes

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

