/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_redir_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:42:33 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:42:39 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_bool	prs_is_redir(char *c)
{
	return (prs_is_in_file(c) || prs_is_out_file(c));
}

t_bool	prs_is_in_file(char *c)
{
	return (*c == PRS_IN_FILE);
}

t_bool	prs_is_out_file(char *c)
{
	return (*c == PRS_OUT_FILE);
}

t_bool	prs_is_append(char *c)
{
	if (prs_is_out_file(c) && prs_is_out_file(c + 1))
		return (TRUE);
	return (FALSE);
}

t_bool	prs_is_heredoc(char *c)
{
	if (prs_is_in_file(c) && prs_is_in_file(c + 1))
		return (TRUE);
	return (FALSE);
}
