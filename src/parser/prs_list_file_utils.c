/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:34:03 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 16:34:45 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

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
