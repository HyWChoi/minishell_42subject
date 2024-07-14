/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:49:54 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 17:14:30 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_is_balanced_quote(char *start)
{
	t_prs_stack	*stack;

	prs_stack_init(&stack, start, NULL);
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
	prs_free_stack(stack);
	return (prs_stack_is_empty(stack));
}

void	prs_skip_qoute(char **ori_str)
{
	if (**ori_str == '\"')
	{
		(*ori_str)++;
		*ori_str += prs_count_str_using_func(*ori_str,
				prs_is_double_quote, FALSE);
	}
	else if (**ori_str == '\'')
	{
		(*ori_str)++;
		*ori_str += prs_count_str_using_func(*ori_str,
				prs_is_single_quote, FALSE);
	}
}

void	prs_process_single_qoute(t_prs_stack *stack, char **result)
{
	int	i;

	i = 0;
	while (*(stack->ori_str + i) && !prs_is_single_quote(stack->ori_str + i))
			i++;
	*result = ft_strndup(stack->ori_str, i);
	stack->ori_str += i + 1;
}

void	prs_process_double_qoute(t_prs_stack *stack, char **result)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(stack->ori_str + i) && !prs_is_double_quote(stack->ori_str + i))
			i++;
	*result = ft_strndup(stack->ori_str, i);
	tmp = *result;
	if (ft_strchr(*result, '$'))
	{
		*result = prs_parse_variable(*result, stack->envp);
		free(tmp);
	}
	stack->ori_str += i + 1;
}

char	*prs_remove_quote(t_prs_stack *stack)
{
	size_t	i;
	char	*result;

	i = 0;
	result = NULL;
	stack->ori_str++;
	if (prs_is_single_quote(stack->ori_str - 1))
		prs_process_single_qoute(stack, &result);
	else
		prs_process_double_qoute(stack, &result);
	return (result);
}
