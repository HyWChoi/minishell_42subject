/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_file_process_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 13:54:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 13:54:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

char	*prs_make_heredoc_file(int count)
{
	char				*result;
	const char *const	tty = ttyname(STDIN_FILENO);
	char				**splited_strs;
	char				*tty_name;

	splited_strs = ft_split(tty, '/');
	tty_name = splited_strs[ft_strs_len((const char **)splited_strs) - 1];
	result = ft_strjoin(tty_name, "_");
	result = ft_strjoin_and_free(TK_HEREDOC_PATH, result, FREE_S2);
	ft_free_strs(splited_strs);
	return (ft_strjoin_and_free(result, ft_itoa(count), FREE_BOTH));
}

void	prs_set_heredoc_file(t_token *token, t_prs_stack *stack,
			t_file_type type)
{
	char	*limiter;

	limiter = prs_find_file_name(stack);
	prs_file_list_add_node(
		prs_create_file_list(NULL, type, limiter), token->file);
}
