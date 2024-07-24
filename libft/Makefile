NAME= libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS := ft_strnstr.c \
	ft_isdigit.c \
	ft_putstr_fd.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_memcmp.c \
	ft_putnbr_fd.c \
	ft_strchr.c \
	ft_striteri.c \
	ft_bzero.c \
	ft_strjoin.c \
	ft_isascii.c \
	ft_memcpy.c \
	ft_isprint.c \
	ft_putendl_fd.c \
	ft_toupper.c \
	ft_split.c \
	ft_strrchr.c \
	ft_isalpha.c \
	ft_memchr.c \
	ft_putchar_fd.c \
	ft_memset.c \
	ft_substr.c \
	ft_strncmp.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_memmove.c \
	ft_strlcat.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_atoi.c \
	ft_isalnum.c \
	ft_itoa.c \
	ft_tolower.c \
	addons/ft_free_strs.c \
	addons/ft_strjoin_and_free.c \
	addons/ft_strs_len.c \
	addons/ft_strs_copy.c \
	addons/ft_calloc_guard.c \
	addons/ft_strndup.c \
	get_next_line/get_next_line.c

OBJS := $(SRCS:.c=.o)

# 색상 정의
BLUE=\033[0;34m
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
RESET=\033[0m
CLEAR_LINE=\033[2K\r
MOVE_UP=\033[1A

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "$(CLEAR_LINE)		[ $(BLUE)libft.a $(RESET)] $(GREEN)created$(RESET)"
	
%.o: %.c
	@printf "$(MOVE_UP)$(CLEAR_LINE)			$(BLUE)~~ $(RESET)Making object $(BLUE)($(NAME)) $(BLUE)~~$(RESET)\n"
	@printf "$(CLEAR_LINE)		$(BLUE)~~$(RESET) $(GREEN)Libft$(RESET) Making $(YELLOW)$@$(RESET) from $(YELLOW)$<$(RESET) $(BLUE)~~$(RESET)"
	@$(CC) $(CFLAGS) -I includes -c $< -o $@

clean:
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing object files$(RESET)"
	@sleep 0.3
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing object files..$(RESET)"
	@sleep 0.2
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing object files...$(RESET)"
	@rm -f $(OBJS)
	@sleep 0.1
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(YELLOW)Object files$(RESET) $(RED)removed$(RESET)"

fclean: clean
	@sleep 0.5
	@rm -rf $(NAME)
	@echo "$(MOVE_UP)$(CLEAR_LINE)		[ $(BLUE)$(NAME)$(RESET) ]$(RED) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus

