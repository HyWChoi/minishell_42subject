/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:50:34 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 19:49:29 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_file_list	*prs_create_file_list(char *file_name, t_file_type type,
				void *limiter, t_bool expand)
{
	t_file_list	*file;

	file = (t_file_list *)malloc(sizeof(t_file_list));
	if (!file)
		return (NULL);
	file->file_name = file_name;
	file->type = type;
	file->limiter = (char *)limiter;
	file->fd = -1;
	file->expand = expand;
	file->next = NULL;
	return (file);
}

t_file_list	*prs_file_list_find_last(t_file_list **start)
{
	if (start == NULL || *start == NULL)
		return (NULL);
	while ((*start)->next)
	{
		start = &(*start)->next;
	}
	return (*start);
}

void	prs_file_list_add_node(t_file_list *new, t_file_list **head)
{
	t_file_list	*last;

	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = prs_file_list_find_last(head);
		last->next = new;
	}
}

void	prs_file_check_and_add_node(
	char *file_name, t_prs_stack *stack, t_token *token, t_file_type type)
{
	if (!file_name)
		stack->err_flag = TRUE;
	if (!stack->err_flag)
		prs_file_list_add_node(
			prs_create_file_list(file_name, type, NULL, TRUE), token->file);
}

void	prs_setting_file(
	t_token *token, t_prs_stack *stack,
	t_bool (*judge_file_type)(char *str), t_file_type type)
{
	char	*file_name;

	file_name = NULL;
	prs_redir_err(stack);
	if (judge_file_type(stack->ori_str + 1))
	{
		if (type == OUT_FILE)
			type = APPEND;
		else
		{
			type = HEREDOC;
			prs_set_heredoc_file(token, stack, type);
			return ;
		}
	}
	else
		if (prs_is_redir(stack->ori_str + 1))
			stack->err_flag = TRUE;
	file_name = prs_find_file_name(stack);
	if (!*file_name)
	{
		free(file_name);
		stack->err_flag = TRUE;
	}
	prs_file_check_and_add_node(file_name, stack, token, type);
}
