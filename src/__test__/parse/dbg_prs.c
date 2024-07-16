/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_prs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:49:00 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/17 01:22:36 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

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

void	dbg_print_arg_list(t_argv_list **argv)
{
	t_argv_list	*start;

	start = *argv;
	printf("files: [");
	while (start)
	{
		if (start->next)
			printf("`%s`, ", start->argv);
		else
			printf("`%s`", start->argv);
		start = start->next;
	}
	printf("]\n");
}

void	dbg_print_file_list(t_file_list **argv)
{
	t_file_list	*start;

	start = *argv;
	printf("argv: [\n");
	while (start)
	{
		printf("file path: `%s`, ", start->file_name);
		printf("fd: %d, ", start->fd);
		if (start->type == IN_FILE)
			printf("type: IN_FILE\n");
		else if (start->type == OUT_FILE)
			printf("type: OUT_FILE\n");
		else if (start->type == APPEND)
			printf("type: APPEND\n");
		else if (start->type == HEREDOC)
		{
			printf("type: HEREDOC\n");
			printf("limiter: `%s`\n", start->limiter);
		}
		if (start->expand)
			printf("expand: TRUE\n");
		else
			printf("expand: FALSE\n");
		if (start->next)
			printf(", ");
		start = start->next;
	}
	printf("]\n");
}

void	dbg_print_token(t_token **token_list)
{
	if (!token_list)
	{
		printf("token_list is EMPTY!\n");
		return ;
	}
	while (*token_list)
	{
		printf("cmd_path: %s\n", (*token_list)->cmd_path);
		dbg_print_argv((*token_list)->argv);
		if ((*token_list)->envp)
			printf("envp[0]: %p -> %s\n", *((*token_list)->envp),
				**(*token_list)->envp);
		dbg_print_file_list((*token_list)->file);
		printf("-----------------------------\n");
		token_list++;
	}
}

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
