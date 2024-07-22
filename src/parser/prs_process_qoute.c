/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_qoute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:41:59 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 02:13:55 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	prs_process_judge_qoute(t_prs_stack *stack, char *start)
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
		if (!*result)
		{
			free(tmp);
			stack->ori_str += i;
			return ;
		}
		free(tmp);
	}
	stack->ori_str += i + 1;
}

char	*prs_remove_quote(t_prs_stack *stack)
{
	char	*result;

	result = NULL;
	stack->ori_str++;
	if (prs_is_single_quote(stack->ori_str - 1))
		prs_process_single_qoute(stack, &result);
	else
		prs_process_double_qoute(stack, &result);
	return (result);
}
