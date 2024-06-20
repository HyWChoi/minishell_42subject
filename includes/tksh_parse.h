#ifndef TKSHELL_prs_H
# define TKSHELL_prs_H
# include "tksh.h"

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

typedef struct s_argv_list	t_argv_list;

typedef struct s_argv_list
{
	char			*argv;
	t_argv_list	*next;
} t_argv_list;

typedef struct	s_prs_stack
{
	char	*stack;
	char	*ori_str;
	char	***envp;
	ssize_t	top;
	size_t	size;
	t_bool	is_double_quote;
	t_bool	is_single_quote;
	t_bool	err_flag;
}	t_prs_stack;

// description: main func for parsing user input
t_token		**prs_parse(char *usr_input, char ***envp);

// description: func about stack list from the user input
t_prs_stack	**prs_init_stack_list(char *ori_str, char ***envp);
void		prs_stack_init(t_prs_stack	**stack, char *ori_str, char ***envp);

// description: func for handling stack
t_bool		prs_stack_is_empty(t_prs_stack *stack);
t_bool		prs_stack_is_full(t_prs_stack *stack);
void		prs_stack_push(t_prs_stack *stack, char elem);
char		prs_stack_pop(t_prs_stack *stack);
char		prs_stack_pick(t_prs_stack *stack);

// description: func about token list from the stack list
t_token		**prs_init_token_list(size_t size, char ***envp);
void		prs_init_token(t_token **token, char	***envp);

// description: func about linked list for making 2d array for argv
t_argv_list	*prs_argv_list_new_node(char *str);
void		prs_argv_list_add_node(char *str, t_argv_list	**head);
char		*prs_argv_list_get_str(t_argv_list *argv_list);
t_argv_list	*prs_argv_list_find_last(t_argv_list **start);
size_t		prs_argv_list_count(t_argv_list **start);

// description: func for setting parsed string into token
char		*prs_make_argv_str(t_prs_stack *stack);
void		prs_set_argv_into_token(t_token *token, t_argv_list **argv_list, t_prs_stack *stack);

// description: func for judging that quote is balanced, if it is TRUE, remove quote
t_bool		prs_is_balanced_quote(t_prs_stack *stack);
char		*prs_remove_quote(t_prs_stack *stack);

// description: func for setting file path in token
void		prs_set_file_path_in_token(t_token *token, t_prs_stack *stack);
char		*prs_find_file_name(t_prs_stack *stack);

// description: func for find value in envp and judging that it is valid variable name
char		*prs_find_value_in_envp(char *str, char ***envp);
char		*prs_parse_variable(char *str, char ***envp);

// description: uitliteis for checking that char is valid characte
t_bool		prs_is_double_quote(char *c);
t_bool		prs_is_single_quote(char *c);
t_bool		prs_is_quote(char *c);
t_bool		prs_is_redir(char *c);
t_bool		prs_is_in_file(char *c);
t_bool		prs_is_out_file(char *c);
t_bool		prs_is_append(char *c);
t_bool		prs_is_heredoc(char *c);
t_bool		prs_is_pipe(char *c);
t_bool		prs_is_white_space(char *c);
t_bool		prs_is_variable(char *c);
t_bool		prs_is_underbar(char *c);
t_bool		prs_is_possible_var_space(char *c);
t_bool		prs_is_possible_var_name(char *c);
t_bool		prs_is_end_of_name(char *str);

// description: func for cleaning up
void		prs_free_stack_list(t_prs_stack **stack_list);
void		prs_free_arg_list(t_argv_list **start);

// description: func for debugging
void		dbg_prs_stack_print(t_prs_stack *stack);
void		dbg_print_token(t_token **token_list);

t_file_list *prs_create_file_list(char *file_name, t_file_type type);
void		prs_free_file_list(t_file_list *file);
t_file_list	*prs_file_list_find_last(t_file_list **start);
void		prs_file_list_add_node(t_file_list *new, t_file_list **head);
void		prs_setting_file(t_token *token, t_prs_stack *stack, t_bool (*judge_file_type)(char *str), t_file_type type);

#endif
