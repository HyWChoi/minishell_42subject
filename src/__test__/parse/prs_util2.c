/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:10:52 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 17:15:40 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

t_bool	prs_is_underbar(char *c)
{
	return (*c == PRS_UNDERBAR);
}

t_bool	prs_is_possible_var_space(char *c)
{
	return (ft_isalpha(*c) || prs_is_underbar(c));
}

t_bool	prs_is_possible_var_name(char *c)
{
	return (ft_isalnum(*c) || prs_is_underbar(c));
}

t_bool	prs_is_end_of_name(char *str)
{
	if (*str && !prs_is_white_space(str)
		&& !prs_is_redir(str) && !prs_is_quote(str))
		return (TRUE);
	return (FALSE);
}

int	prs_count_pipe(char *ori_str)
{
	int	count;

	count = 0;
	while (*ori_str)
	{
		prs_skip_qoute(&ori_str);
		if (*ori_str == '|')
			count++;
		ori_str++;
	}
	return (count);
}
