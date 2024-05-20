#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	prs_stack_init(t_prs_stack	**stack, size_t	size)
{
	if(ft_calloc_guard((void **)stack, 1, sizeof(t_prs_stack)) == NULL)
		return ;
	if(ft_calloc_guard((void **)&((*stack)->stack), size + 1, sizeof(char *)) == NULL)
		return ;
	(*stack)->top = -1;
	(*stack)->size = size;
}

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

void	prs_free_stack(t_prs_stack *stack)
{
	free(stack->stack);
	free(stack);
}

void	prs_print_stack(t_prs_stack *stack)
{
	ssize_t	i;

	i = 0;
	printf("\n----current stack----\n");
	while (i < stack->top)
	{
		printf("stack[%zu]: %c\n", i, stack->stack[i]);
		i++;
	}
}
