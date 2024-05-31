#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_is_balanced_quote(t_prs_stack *stack)
{
	char	*start = stack->ori_str;
	while (*start)
	{
		if (!stack->is_double_quote && prs_is_single_quote(start))
		{
			if (stack->is_single_quote)
				prs_stack_pop(stack);
			else
				prs_stack_push(stack, *start);
			stack->is_single_quote = !stack->is_single_quote;
		}
		else if (!stack->is_single_quote && prs_is_double_quote(start))
		{
			if (stack->is_double_quote)
				prs_stack_pop(stack);
			else
				prs_stack_push(stack, *start);
			stack->is_double_quote = !stack->is_double_quote;
		}
		start++;
	}
	dbg_prs_stack_print(stack);
	return (prs_stack_is_empty(stack));
}

char	*prs_remove_quote(t_prs_stack *stack, char ***envp)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	stack->ori_str++;
	if (prs_is_single_quote(stack->ori_str - 1))
	{
		while (*(stack->ori_str + i) && !prs_is_single_quote(stack->ori_str + i))
			i++;
		result = ft_strndup(stack->ori_str, i);
	}
	else
	{
		while (*(stack->ori_str + i) && !prs_is_double_quote(stack->ori_str + i))
			i++;
		result = ft_strndup(stack->ori_str, i);
		if (ft_strchr(result, '$'))
			result = prs_find_envp(result, envp);
	}
	stack->ori_str += i + 1;
	return (result);
}
