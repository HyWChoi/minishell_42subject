/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:49:54 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/17 07:03:37 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

static void	prs_process_judge_qoute(t_prs_stack *stack, char *start)
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
		char	**splited_str;
		size_t	j;
		size_t	len;
		splited_str = ft_split(*result, ' ');
		len = ft_strs_len((const char **)splited_str);
		j = 0;
		while (j < len - 1)
		{
			if (splited_str[j])
				prs_argv_list_add_node(ft_strdup(splited_str[j]), stack);
			j++;
		}
		free(*result);
		*result = ft_strdup(splited_str[j]);
		ft_free_strs(splited_str);
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
