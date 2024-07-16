/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_parse_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:08:20 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/17 06:57:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

void	prs_set_cmd_path_in_token(t_token *token)
{
	if (token->argv && token->argv[0])
		token->cmd_path = ft_strdup(token->argv[0]);
}

char	*prs_process_quote(t_prs_stack *stack)
{
	return (prs_remove_quote(stack));
}

void	prs_process_redir(t_token *token,
		t_prs_stack *stack, char **result)
{
	prs_set_file_path_in_token(token, stack);
	if (**result)
	{
		prs_argv_list_add_node(*result, stack);
		*result = ft_strdup("");
	}
}

char	*prs_process_regular_char(t_prs_stack *stack)
{
	return (prs_make_argv_str(stack));
}

void	finalize_result(char *result,
		t_prs_stack *stack)
{
	if (!(*result))
		free(result);
	else
	{
		prs_argv_list_add_node(result, stack);
		free(result);
	}
}
