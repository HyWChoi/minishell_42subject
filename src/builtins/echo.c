/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:19:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 06:05:10 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

char	*ft_concat(char **strs, char *sep)
{
	size_t	len;
	size_t	i;
	char	*ret;

	len = ft_strs_len((const char **)strs);
	if (len == 0)
		return (NULL);
	if (len == 1)
		return (prs_safety_strdup(strs[0]));
	ret = prs_safety_strdup(strs[0]);
	if (!ret)
		return (NULL);
	i = 1;
	while (i < len)
	{
		ret = prs_safety_strjoin_and_free(ret, sep, FREE_S1);
		ret = prs_safety_strjoin_and_free(ret, strs[i], FREE_S1);
		i++;
	}
	return (ret);
}

int	len_zero(size_t len, char *option)
{
	if (len == 0)
	{
		if (option && !ft_strncmp(option, "-n", 2))
			printf("");
		else
			printf("\n");
		return (0);
	}
	return (-1);
}

t_exit_code	echo(char **strings, char *option)
{
	const size_t	len = ft_strs_len((const char **)strings);
	char			*ret;

	if (!len_zero(len, option))
		return (EXIT_SUCCESS);
	if (ft_calloc_guard((void **)&ret, 1, sizeof(char *)) == NULL)
		return (EXIT_FAILURE);
	ret = ft_concat(strings, " ");
	if (!ret)
		return (EXIT_FAILURE);
	ret = prs_safety_strjoin_and_free(ret, " ", FREE_S1);
	if (!ret)
		return (EXIT_FAILURE);
	if (ft_strncmp(option, "-n", 2))
		ret[ft_strlen(ret) - 1] = '\n';
	else
		ret[ft_strlen(ret) - 1] = '\0';
	write(1, ret, ft_strlen(ret));
	free(ret);
	return (EXIT_SUCCESS);
}
