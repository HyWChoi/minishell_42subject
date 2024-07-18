/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_prs_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:49:00 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:37:48 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

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

void	dbg_print_file_type(t_file_type type, t_file_list *start)
{
	if (type == IN_FILE)
		printf("type: IN_FILE\n");
	else if (type == OUT_FILE)
		printf("type: OUT_FILE\n");
	else if (type == APPEND)
		printf("type: APPEND\n");
	else if (type == HEREDOC)
	{
		printf("type: HEREDOC\n");
		printf("limiter: `%s`\n", start->limiter);
	}
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
		dbg_print_file_type(start->type, start);
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
