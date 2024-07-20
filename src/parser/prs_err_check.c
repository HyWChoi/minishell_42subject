/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_err_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:36:10 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:36:14 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	*handle_unbalanced_quote(char *result)
{
	free(result);
	return (NULL);
}

void	prs_redir_err(t_prs_stack *stack)
{
	if ((ft_strlen(stack->ori_str) > 1) && prs_is_redir(stack->ori_str + 2))
	{
		stack->err_flag = TRUE;
		return ;
	}
}

t_bool	is_check_err_in_stack(t_prs_stack *stack)
{
	if (stack->err_flag)
		return (TRUE);
	return (FALSE);
}
