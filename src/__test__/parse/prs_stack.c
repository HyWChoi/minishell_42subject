#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_stack_is_empty(t_prs_stack *stack)
{
	return (stack->top == -1);
}

t_bool	prs_stack_is_full(t_prs_stack *stack)
{
	return (stack->top == (ssize_t)stack->size - 1);
}

void	prs_stack_push(t_prs_stack *stack, char elem)
{
	if (prs_stack_is_full(stack))
		return ;
	stack->top += 1;
	stack->stack[stack->top] = elem;
}

char	prs_stack_pop(t_prs_stack *stack)
{
	char	result;

	if (prs_stack_is_empty(stack))
		return (0);
	result = stack->stack[stack->top];
	stack->stack[stack->top] = 0;
	stack->top -= 1;
	return (result);
}

char	prs_stack_pick(t_prs_stack *stack)
{
	if (prs_stack_is_empty(stack))
		return (0);
	return (stack->stack[stack->top]);
}

void	dbg_prs_stack_print(t_prs_stack *stack)
{
	ssize_t	i;

	i = 0;
	// printf("\n----current stack----\n");
	while (i < stack->top)
	{
		printf("stack[%zu]: %c\n", i, stack->stack[i]);
		i++;
	}
}
