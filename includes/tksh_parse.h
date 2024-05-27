#ifndef TKSHELL_prs_H
# define TKSHELL_prs_H
# include "tksh.h"

typedef struct s_argv_list	t_argv_list;

typedef struct s_argv_list
{
	char			*argv;
	t_argv_list	*next;
} t_argv_list;


typedef struct	s_prs_stack
{
	char	*stack;
	ssize_t	top;
	size_t	size;
}	t_prs_stack;

void	prs_stack_init(t_prs_stack	**stack, size_t	size);
t_bool	prs_stack_is_empty(t_prs_stack *stack);
t_bool	prs_stack_is_full(t_prs_stack *stack);
void	prs_stack_push(t_prs_stack *stack, char elem);
char	prs_stack_pop(t_prs_stack *stack);
char	prs_stack_pick(t_prs_stack *stack);
void	prs_stack_free(t_prs_stack *stack);
void	dbg_prs_stack_print(t_prs_stack *stack);

#endif
