/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:49:32 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:49:35 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

char	*prs_process_stack(t_prs_stack *stack, t_token *token, char *result)
{
	char	*tmp;

	tmp = NULL;
	if (prs_is_quote(stack->ori_str))
		tmp = prs_process_quote(stack);
	else if (prs_is_redir(stack->ori_str))
	{
		prs_process_redir(token, stack, &result);
		return (result);
	}
	else if (!prs_is_white_space(stack->ori_str))
		tmp = prs_make_argv_str(stack);
	result = prs_handle_whitespace(stack, tmp, result);
	return (result);
}
char	*prs_process_quote(t_prs_stack *stack)
{
	return (prs_remove_quote(stack));
}

void	prs_process_redir(t_token *token, t_prs_stack *stack, char **result)
{
	prs_set_file_path_in_token(token, stack);
	if (**result)
	{
		prs_argv_list_add_node(*result, stack);
		*result = ft_strdup("");
	}
}
