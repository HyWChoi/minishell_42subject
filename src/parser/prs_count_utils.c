/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_count_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:35:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:35:19 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_parse.h"
#include "libft.h"

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

size_t	prs_count_str_using_func(char *str,
		t_bool (*f)(char *), t_bool count_if_true)
{
	size_t	count;

	count = 0;
	if (count_if_true)
	{
		while (*str && f(str))
		{
			count++;
			str++;
		}
	}
	else
	{
		while (*str && !f(str))
		{
			count++;
			str++;
		}
	}
	return (count);
}
