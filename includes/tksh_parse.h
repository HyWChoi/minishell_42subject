/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_parse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:39:59 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/20 16:37:54 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_PARSE_H
# define TKSH_PARSE_H
# include "tksh.h"

/* Definitions for parsing */
# define PRS_WHITE_SPACE " \t\n\r\v\f"
# define PRS_IN_FILE '<'
# define PRS_OUT_FILE '>'
# define PRS_REDIRECTION "><"
# define PRS_PIPE '|'
# define PRS_APPEND ">>"
# define PRS_HEREDOC "<<"
# define PRS_SINGLE_QUOTE '\''
# define PRS_DOUBLE_QUOTE '\"'
# define PRS_VARIABLE '$'
# define PRS_UNDERBAR '_'

/* Structure definitions */
typedef struct s_argv_list	t_argv_list;

typedef struct s_argv_list
{
	char		*argv;
	t_argv_list	*next;
}	t_argv_list;

typedef struct s_prs_stack
{
	char		*stack;
	char		*ori_str;
	char		***envp;
	t_argv_list	**argv_list;
	ssize_t		top;
	size_t		size;
	t_bool		is_double_quote;
	t_bool		is_single_quote;
	t_bool		var_flag;
	t_bool		err_flag;
}	t_prs_stack;

/* Parser functions */
void		prs_init_stack_token_lists(t_prs_stack ***stack_list,
				t_token ***token_list, char *usr_input, char ***envp);
t_token		**prs_parse(char *usr_input, char ***envp);

/* Initialization functions */
t_token		**prs_init_token_list(size_t size, char ***envp);
void		prs_init_token(t_token **token, char	***envp);
t_prs_stack	**prs_init_stack_list(char *ori_str, char ***envp);
void		prs_stack_init(t_prs_stack	**stack, char *ori_str, char ***envp);
void		init_free(t_prs_stack **stack, char *ori_str, char ***envp);

/* argv_list utility functions */
t_argv_list	*prs_argv_list_new_node(char *str);
void		prs_argv_list_add_node(char *str, t_prs_stack *stack);
char		*prs_argv_list_get_str(t_argv_list *argv_list);
t_argv_list	*prs_argv_list_find_last(t_argv_list **start);
size_t		prs_argv_list_count(t_argv_list **start);

/* File list utility functions */
t_file_list	*prs_create_file_list(char *file_name, t_file_type type,
				void *limiter, t_bool expand);
t_file_list	*prs_file_list_find_last(t_file_list **start);
void		prs_file_list_add_node(t_file_list *new, t_file_list **head);
void		prs_file_check_and_add_node(char *file_name, t_prs_stack *stack,
				t_token *token, t_file_type type);

/* Token setting functions */
void		*prs_set_token(t_prs_stack *stack, t_token *token);
void		prs_set_cmd_path_in_token(t_token *token);
void		prs_set_argv_into_token(t_token *token, t_prs_stack *stack);
void		prs_set_file_path_in_token(t_token *token, t_prs_stack *stack);
void		prs_set_heredoc_path(t_token **token);

/* Resource cleaning functions - stack */
void		prs_free_stack_list(t_prs_stack **stack_list);
void		prs_free_stack(t_prs_stack *stack);
void		prs_free_arg_list(t_argv_list **start);

/* Resource cleaning functions - token */
void		tksh_free_token_list(t_token **token_list);
void		tksh_free_token(t_token *token);
void		prs_free_file_list(t_file_list **file);

/* Error handling functions */
void		*prs_err_free_all(char *usr_input,
				t_prs_stack **stack_list, t_token **token_list);

/* String making functions */
char		*prs_make_argv_str(t_prs_stack *stack);
char		*prs_extract_var_by_split(char **result, t_prs_stack *stack);
void		prs_finalize_result(char *result, t_prs_stack *stack);
char		*prs_handle_whitespace(t_prs_stack *stack, char *tmp, char *result);

/* Input processing functions */
char		*prs_process_stack(t_prs_stack *stack,
				t_token *token, char *result);
char		*prs_process_quote(t_prs_stack *stack);
void		prs_process_redir(t_token *token, t_prs_stack *stack, char **result);

/* File setting functions */
void		prs_setting_file(t_token *token, t_prs_stack *stack,
				t_bool (*judge_file_type)(char *str), t_file_type type);
size_t		prs_skip_redir_and_whitespace(t_prs_stack *stack);
char		*prs_process_quote_or_variable(t_prs_stack *stack,
				char *result, char **start);
char		*prs_find_file_name(t_prs_stack *stack);
char		*prs_finalize_file_result(t_prs_stack *stack,
				char *result, char *start);

/* Heredoc processing functions */
void		prs_set_heredoc_file(t_token *token, t_prs_stack *stack,
				t_file_type type);
char		*prs_make_heredoc_file(int count);
char		*prs_remove_quote_in_heredoc(t_prs_stack *stack);
void		prs_skip_for_heredoc_limiter(t_prs_stack *stack, char **start);
char		*prs_find_heredoc_limiter(t_prs_stack *stack, t_bool *flag);

/* Redirection processing utility functions */
t_bool		prs_is_redir(char *c);
t_bool		prs_is_in_file(char *c);
t_bool		prs_is_out_file(char *c);
t_bool		prs_is_append(char *c);
t_bool		prs_is_heredoc(char *c);

/* Error checking functions */
void		*handle_unbalanced_quote(char *result);
void		prs_redir_err(t_prs_stack *stack);
t_bool		is_check_err_in_stack(t_prs_stack *stack);

/* Quote processing utility functions */
t_bool		prs_is_double_quote(char *c);
t_bool		prs_is_single_quote(char *c);
t_bool		prs_is_quote(char *c);
t_bool		prs_is_balanced_quote(char *start);
void		prs_skip_qoute(char **ori_str);

/* Quote processing functions */
void	prs_process_judge_qoute(t_prs_stack *stack, char *start);
void		prs_process_single_qoute(t_prs_stack *stack, char **result);
void		prs_process_double_qoute(t_prs_stack *stack, char **result);
char		*prs_remove_quote(t_prs_stack *stack);

/* Stack utility functions */
t_bool		prs_stack_is_empty(t_prs_stack *stack);
t_bool		prs_stack_is_full(t_prs_stack *stack);
void		prs_stack_push(t_prs_stack *stack, char elem);
char		prs_stack_pop(t_prs_stack *stack);
char		prs_stack_pick(t_prs_stack *stack);

/* Parsing utility functions */
t_bool		prs_is_pipe(char *c);
t_bool		prs_is_end_of_str(char *str);
t_bool		prs_is_equal(char *c);
t_bool		prs_is_white_space(char *c);
t_bool		prs_is_end_of_name(char *str);

/* Variable utility functions */
t_bool		prs_is_variable(char *c);
t_bool		prs_is_underbar(char *c);
t_bool		prs_is_possible_var_space(char *c);
t_bool		prs_is_possible_var_name(char *c);

/* Count utility functions */
int			prs_count_pipe(char *ori_str);
size_t		prs_count_str_using_func(char *str,
				t_bool (*f)(char *), t_bool count_if_true);

/* Variable parsing functions */
char		*prs_find_value_in_envp(char *str, char ***envp);
char		*prs_handle_possible_var_space(char **str, char ***envp, char *result);
char		*prs_process_variable(char **str, char **start, char ***envp, char *result);
char		*prs_parse_variable(char *str, char ***envp);

#endif
