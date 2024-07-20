/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_argv_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:33:16 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 16:33:17 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_argv_list	*prs_argv_list_new_node(char *str)
{
	t_argv_list	*new;

	new = NULL;
	if (!str)
		return (new);
	if (!ft_calloc_guard((void **)&new, 1, sizeof(t_argv_list)))
		return (NULL);
	new->argv = str;
	new->next = NULL;
	return (new);
}
void	prs_argv_list_add_node(char *str, t_prs_stack *stack)
{
	t_argv_list	*last;
	t_argv_list	**head;

	head = stack->argv_list;
	if (!str)
		return ;
	if (!*str && stack->var_flag)
	{
		stack->var_flag = FALSE;
		free(str);
		return ;
	}
	if (!*head)
		*head = prs_argv_list_new_node(str);
	else
	{
		last = prs_argv_list_find_last(head);
		last->next = prs_argv_list_new_node(str);
	}
}

char	*prs_argv_list_get_str(t_argv_list *argv_list)
{
	if (!argv_list)
		return (NULL);
	return (argv_list->argv);
}

t_argv_list	*prs_argv_list_find_last(t_argv_list **start)
{
	if (start == NULL || *start == NULL)
		return (NULL);
	while ((*start)->next)
	{
		start = &(*start)->next;
	}
	return (*start);
}

size_t	prs_argv_list_count(t_argv_list **start)
{
	size_t		i;
	t_argv_list	*tmp;

	i = 0;
	tmp = *start;
	if (start == NULL || *start == NULL)
		return (i);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
