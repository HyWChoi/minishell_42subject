#ifndef TKSHELL_PARSE_H
# define TKSHELL_PARSE_H
# include "tksh.h"

typedef struct	s_parse_stack
{
	char	*stack;
	ssize_t	top;
	size_t	size;
}	t_parse_stack;

void	init_parse(t_parse_stack	**stack, size_t	size);
t_bool	parse_is_empty(t_parse_stack *stack);
t_bool	parse_is_full(t_parse_stack *stack);
void	parse_push(t_parse_stack *stack, char elem);
char	parse_pop(t_parse_stack *stack);
char	parse_pick(t_parse_stack *stack);
void	free_parse(t_parse_stack *stack);
void	print_stack(t_parse_stack *stack);

#endif
