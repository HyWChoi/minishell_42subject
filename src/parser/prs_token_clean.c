/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_token_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:54:36 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:54:38 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"

void	tksh_free_token_list(t_token **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		tksh_free_token(token_list[i++]);
	free(token_list);
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
