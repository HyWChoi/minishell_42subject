/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_qoute_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:40:41 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:41:06 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_bool	prs_is_balanced_quote(char *start)
{
	t_prs_stack	*stack;
	t_bool		result;

	prs_stack_init(&stack, start, NULL);
	while (*start)
	{
		prs_process_judge_qoute(stack, start);
		start++;
	}
	result = prs_stack_is_empty(stack);
	prs_free_stack(stack);
	return (result);
}

t_bool	prs_is_double_quote(char *c)
{
	return (PRS_DOUBLE_QUOTE == *c);
}

t_bool	prs_is_single_quote(char *c)
{
	return (PRS_SINGLE_QUOTE == *c);
}

t_bool	prs_is_quote(char *c)
{
	return (prs_is_double_quote(c) || prs_is_single_quote(c));
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
