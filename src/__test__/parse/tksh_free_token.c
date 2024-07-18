/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_free_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:49:32 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 16:44:50 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include <stdlib.h>

void	prs_free_file_list(t_file_list **file)
{
	t_file_list	*tmp;

	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		if (tmp->file_name)
			free(tmp->file_name);
		if (tmp->limiter)
			free(tmp->limiter);
		free(tmp);
	}
}

void	tksh_free_token(t_token *token)
{
	if (token->cmd_path)
		free(token->cmd_path);
	if (token->argv)
		ft_free_strs(token->argv);
	if (token->file)
	{
		prs_free_file_list(token->file);
		free(token->file);
	}
	free(token);
}

void	tksh_free_token_list(t_token **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		tksh_free_token(token_list[i++]);
	free(token_list);
}
