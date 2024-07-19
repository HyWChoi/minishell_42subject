/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_clean_resources.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:50:40 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 10:32:43 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	prs_free_stack(t_prs_stack *stack)
{
	free(stack->stack);
	free(stack->ori_str);
	prs_free_arg_list(stack->argv_list);
	free(stack->argv_list);
	free(stack);
}

void	prs_free_arg_list(t_argv_list **start)
{
	t_argv_list	*tmp;

	while (*start)
	{
		tmp = *start;
		*start = (*start)->next;
		if (tmp->argv)
			free(tmp->argv);
		free(tmp);
	}
}

void	prs_free_stack_list(t_prs_stack **stack_list)
{
	int	i;

	i = 0;
	while (stack_list && stack_list[i])
	{
		free((stack_list[i])->stack);
		free((stack_list[i])->ori_str);
		prs_free_arg_list(stack_list[i]->argv_list);
		free(stack_list[i]->argv_list);
		free(stack_list[i]);
		i++;
	}
	free(stack_list);
}
