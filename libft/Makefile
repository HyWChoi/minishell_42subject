NAME= libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

# TODO: 제출하기 전에 shell find 명령어를 사용하지 않도록 수정해야 함
SRCS := $(shell find . -name ft_\*.c | grep -v bonus)  get_next_line/get_next_line.c
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
	@printf "$(MOVE_UP)$(CLEAR_LINE)			$(BLUE)~~ $(RESET)Making object $(BLUE)~~$(RESET)\n"
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

