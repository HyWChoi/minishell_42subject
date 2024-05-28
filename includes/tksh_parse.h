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

t_prs_stack	**prs_init_stack_list(char *ori_str, char ***envp);
void		prs_stack_init(t_prs_stack	**stack, char *ori_str, char ***envp);
t_bool		prs_stack_is_empty(t_prs_stack *stack);
t_bool		prs_stack_is_full(t_prs_stack *stack);
void		prs_stack_push(t_prs_stack *stack, char elem);
char		prs_stack_pop(t_prs_stack *stack);
char		prs_stack_pick(t_prs_stack *stack);
void		prs_stack_free(t_prs_stack *stack);
t_token		**prs_init_token_list(size_t size, char ***envp);
void		prs_init_token(t_token **token, char	***envp);

void		dbg_prs_stack_print(t_prs_stack *stack);
#endif
