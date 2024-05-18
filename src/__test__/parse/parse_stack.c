#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	init_parse(t_parse_stack	**stack, size_t	size)
{
	if(ft_calloc_guard((void **)stack, 1, sizeof(t_parse_stack)) == NULL)
		return ;
	if(ft_calloc_guard((void **)&((*stack)->stack), size + 1, sizeof(char *)) == NULL)
		return ;
	(*stack)->top = -1;
	(*stack)->size = size;
}

t_bool	parse_is_empty(t_parse_stack *stack)
{
	return (stack->top == -1);
}

t_bool	parse_is_full(t_parse_stack *stack)
{
	return (stack->top == (ssize_t)stack->size - 1);
}

void	parse_push(t_parse_stack *stack, char elem)
{
	if (parse_is_full(stack))
		return ;
	stack->top += 1;
	stack->stack[stack->top] = elem;
}

char	parse_pop(t_parse_stack *stack)
{
	char	result;

	if (parse_is_empty(stack))
		return (0);
	result = stack->stack[stack->top];
	stack->stack[stack->top] = 0;
	stack->top -= 1;
	return (result);
}

char	parse_pick(t_parse_stack *stack)
{
	if (parse_is_empty(stack))
		return (0);
	return (stack->stack[stack->top]);
}

void	free_parse(t_parse_stack *stack)
{
	free(stack->stack);
	free(stack);
}

void	print_stack(t_parse_stack *stack)
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
