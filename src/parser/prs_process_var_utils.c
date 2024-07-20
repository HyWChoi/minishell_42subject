/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:49:39 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:50:15 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

t_bool	prs_is_variable(char *c)
{
	return (*c == PRS_VARIABLE);
}

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
