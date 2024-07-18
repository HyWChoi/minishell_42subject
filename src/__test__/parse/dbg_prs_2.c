/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_prs_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:35:51 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:36:13 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	dbg_balanced_test(t_prs_stack **stack_list)
{
	while (*stack_list)
	{
		printf("is_balanced_quotation? -> ");
		if (prs_is_balanced_quote((*stack_list)->ori_str))
			printf("TRUE\n");
		else
			printf("FALSE\n");
		stack_list++;
	}
}

void	dbg_prs_stack_print(t_prs_stack *stack)
{
	ssize_t	i;

	i = 0;
	while (i < stack->top)
	{
		printf("stack[%zu]: %c\n", i, stack->stack[i]);
		i++;
	}
}

void	dbg_print_argv(char **argv)
{
	printf("argv: [");
	while (argv && *argv)
	{
		if (*(argv + 1) == NULL)
			printf("`%s`", *argv++);
		else
			printf("`%s`, ", *argv++);
	}
	printf("]\n");
}
