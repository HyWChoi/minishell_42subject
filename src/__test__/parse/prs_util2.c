/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:10:52 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/14 14:11:52 by hyeonwch         ###   ########.fr       */
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
