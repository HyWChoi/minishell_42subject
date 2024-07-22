/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_safety_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:11:40 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 06:12:23 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

char	*prs_safety_strdup(char *str)
{
	char	*target;

	target = ft_strdup(str);
	if (!target)
		exit(EXIT_FAILURE);
	return (target);
}

char	*prs_safety_strndup(char *str, size_t n)
{
	char	*target;

	target = ft_strndup(str, n);
	if (!target)
		exit(EXIT_FAILURE);
	return (target);
}

char	*prs_safety_strtrim(char *str, const char *set)
{
	char	*target;

	target = ft_strtrim(str, set);
	if (!target)
		exit(EXIT_FAILURE);
	return (target);
}

char	*prs_safety_strjoin_and_free(char *s1, char *s2, int free_target)
{
	char	*target;

	target = ft_strjoin(s1, s2);
	if (!target)
		exit(EXIT_FAILURE);
	if (free_target == FREE_BOTH || free_target == FREE_S1)
		free(s1);
	if (free_target == FREE_BOTH || free_target == FREE_S2)
		free(s2);
	return (target);
}
