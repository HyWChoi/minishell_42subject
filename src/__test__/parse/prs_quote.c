#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

/**
 * @brief prs_is_balanced_quote
 *
 * This function checks if the quotes in the stack's original string are balanced.
 * It updates the stack's quote status and uses a stack to track unmatched quotes.
 *
 * @param t_prs_stack* stack - The stack containing the original string and quote status.
 * @return t_bool - TRUE if quotes are balanced, FALSE otherwise.
 */
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

/**
 * @brief prs_remove_quote
 *
 * This function removes the surrounding quotes from the stack's original string.
 * It handles both single and double quotes and resolves environment variables if needed.
 *
 * @param t_prs_stack* stack - The stack containing the original string and quote status.
 * @param char*** envp - The environment variables for resolving variables inside double quotes.
 * @return char* - The string with quotes removed, or NULL if an error occurs.
 */
char	*prs_remove_quote(t_prs_stack *stack)
{
	size_t	i;
	char	*result;
	char	*tmp;

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
		tmp = result;
		if (ft_strchr(result, '$'))
		{
			result = prs_parse_variable(result, stack->envp);
			free(tmp);
		}
	}
	stack->ori_str += i + 1;
	return (result);
}
