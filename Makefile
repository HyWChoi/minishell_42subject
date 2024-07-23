# CC = Clang
CC = cc
SAN = -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g -fno-pie

srcs = builtins/builtin_handler.c\
		builtins/cd.c \
		builtins/dtos/dto_cd.c \
		builtins/dtos/dto_echo.c \
		builtins/dtos/dto_env.c \
		builtins/dtos/dto_exit.c \
		builtins/dtos/dto_export.c \
		builtins/dtos/dto_pwd.c \
		builtins/dtos/dto_unset.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/pwd.c \
		builtins/unset.c \
		error/ex_err_msg.c \
		error/throw_syntax_error.c \
		execute/ex_run_multiple_cmd.c \
		execute/execute.c \
		execute/io/ex_move_2_fd.c \
		execute/io/file_redirection.c \
		execute/io/io_utils.c \
		execute/io/pipe_utils.c \
		execute/ret_exitcode.c \
		execute/run_cmd.c \
		execute/sig_utils.c \
		execute/utils/ex_fork_err_guard.c \
		execute/utils/ex_is_child.c \
		execute/utils/ex_sig_catched.c \
		execute/utils/ex_single_cmd.c \
		execute/utils/get_cmd_path_from_env.c \
		execute/utils/get_token_len.c \
		execute/utils/heredoc_hook.c \
		execute/utils/heredoc_hook_utils.c \
		execute/utils/is_builtin.c \
		execute/wait_child.c \
		parser/prs_count_utils.c \
		parser/prs_err_check.c \
		parser/prs_err_free_all.c \
		parser/prs_init_stack_token.c \
		parser/prs_list_argv_utils.c \
		parser/prs_list_file_utils.c \
		parser/prs_make_argv_str.c \
		parser/prs_parser.c \
		parser/prs_process_heredoc.c \
		parser/prs_process_qoute.c \
		parser/prs_process_qoute_utils.c \
		parser/prs_process_redir.c \
		parser/prs_process_redir_utils.c \
		parser/prs_process_stack.c \
		parser/prs_process_stack_utils.c \
		parser/prs_process_var.c \
		parser/prs_process_var_utils.c \
		parser/prs_safety_funcs.c \
		parser/prs_set_in_token.c \
		parser/prs_stack_clean.c \
		parser/prs_stack_utils.c \
		parser/prs_token_clean.c \
		tks_prompt/exit_on_eof.c \
		tks_prompt/tksh_prompt.c \
		tkshell.c \

srcs := $(addprefix src/, $(srcs))
OBJS := $(srcs:.c=.o)
NAME = minishell
TEST = test
TEST_EXEC = test_tksh

PARSE = parse
prs_test_main = src/__test__/parse/main.c
prs_srcs = $(shell find "src/__test__/parse" -name "*.c" | grep -v "main")
prs_obj = $(shell find "src/__test__/parse" -name "*.o")
prs_TEST_EXEC = prs_test

EXECUTE = execute
execute_test_main = src/__test__/execute/main.c
execute_test_srcs = $(shell find "src/__test__/execute" -name "*.c" | grep -v "main") \
# execute_obj = $(shell find "src/__test__/execute" -name "*.o")
EXECUTE_TEST_EXEC = execute_test

LIBFT = libs/libft/libft.a
READLINE_FLAGS = -lreadline

# 색상 정의
SKYBLUE=\033[0;36m
BLUE=\033[0;34m
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
RESET=\033[0m
CLEAR_LINE=\033[2K\r
MOVE_UP=\033[1A
MOVE_DOWN=\033[1B
# arm architecture compatibility
ifeq ($(shell uname -p), arm)
	READLINE_PATH = -I /opt/homebrew/opt/readline/include
	READLINE_FLAGS += $(READLINE_PATH) -L/opt/homebrew/opt/readline/lib
endif


all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(CLEAR_LINE)		[ $(BLUE)$(NAME) $(RESET)] $(GREEN)created$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L libs -lft -I includes -I libft/includes $(READLINE_FLAGS)

$(LIBFT):
	@make -C libft
	@mkdir -p libs
	@cp libft/libft.a libs/


%.o : %.c
	@printf "$(CLEAR_LINE)			$(BLUE)~~ $(RESET)Making object $(BLUE)~~$(RESET)\n"
	@printf "$(CLEAR_LINE)		$(BLUE)~~$(RESET) $(GREEN)Libft$(RESET) Making $(YELLOW)$@$(RESET) from $(YELLOW)$<$(RESET) $(BLUE)~~$(RESET)($MOVE_UP)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes -I libft/includes $(READLINE_PATH)

clean:
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(YELLOW)~~$(RED)Remove $(BLUE)Library $(RED)files $(YELLOW)~~$(RESET)$(MOVE_DOWN)"
	make -C libft clean
	@sleep 0.5
	@echo "$(CLEAR_LINE)		$(YELLOW)~~$(RED)Cleaing Object files $(YELLOW)~~$(RESET)\n$(MOVE_DOWN)"
	@rm -rf $(OBJS)
	@sleep 0.1
	@echo "$(CLEAR_LINE)		$(RED)Removing Object files.$(RESET)"
	@sleep 0.2
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing Object files..$(RESET)"
	@sleep 0.1
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(RED)Removing Object files...$(RESET)"
	@sleep 0.1
	@echo "$(MOVE_UP)$(CLEAR_LINE)		$(YELLOW)Object files$(RESET) $(RED)removed$(RESET)$(MOVE_DOWN)"

fclean: clean

	@make -C libft fclean
	@rm -rf libs
	@rm -f libs/libft.a
	@rm -f $(NAME) $(TEST_EXEC) $(prs_TEST_EXEC) $(EXECUTE_TEST_EXEC)
	@sleep 0.5
	@echo "$(CLEAR_LINE)		[ $(SKYBLUE)$(NAME) $(RESET)] $(RED)removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
