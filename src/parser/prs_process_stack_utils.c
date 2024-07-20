/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_stack_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:47:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:47:18 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_bool	prs_is_end_of_name(char *str)
{
	if (*str && !prs_is_white_space(str)
		&& !prs_is_redir(str) && !prs_is_quote(str))
		return (TRUE);
	return (FALSE);
}

t_bool	prs_is_pipe(char *c)
{
	return (PRS_PIPE == *c);
}

t_bool	prs_is_end_of_str(char *str)
{
	return (*str == '\0');
}

t_bool	prs_is_equal(char *c)
{
	return ('=' == *c);
}

t_bool	prs_is_white_space(char *c)
{
	if (!*c)
		return (FALSE);
	return (ft_strchr(PRS_WHITE_SPACE, *c) != NULL);
}
