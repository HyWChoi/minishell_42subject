/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_parse_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:08:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 15:57:01 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	*handle_unbalanced_quote(char *result)
{
	free(result);
	return (NULL);
}

char	*prs_handle_whitespace(t_prs_stack *stack,
		char *tmp, char *result, t_argv_list **argv_list)
{
	if (prs_is_white_space(stack->ori_str))
	{
		stack->ori_str++;
		if (tmp)
		{
			result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
			prs_argv_list_add_node(result, argv_list, stack);
			result = ft_strdup("");
		}
	}
	else
		result = ft_strjoin_and_free(result, tmp, FREE_BOTH);
	if (!*stack->ori_str)
	{
		prs_argv_list_add_node(result, argv_list, stack);
		result = ft_strdup("");
	}
	return (result);
}

t_bool	is_check_err_in_stack(t_prs_stack *stack)
{
	if (stack->err_flag)
		return (TRUE);
	return (FALSE);
}

char	*prs_process_stack(t_prs_stack *stack,
		t_token *token, char *result, t_argv_list **argv_list)
{
	char	*tmp;

	tmp = NULL;
	if (prs_is_quote(stack->ori_str))
		tmp = prs_process_quote(stack);
	else if (prs_is_redir(stack->ori_str))
	{
		prs_process_redir(token, argv_list, stack, &result);
		return (result);
	}
	else if (!prs_is_white_space(stack->ori_str))
		tmp = prs_process_regular_char(stack);
	result = prs_handle_whitespace(stack, tmp, result, argv_list);
	return (result);
}
