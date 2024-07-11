/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:19:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/11 15:27:59 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

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

/**
 * @brief echo
 *
 * This function repeats the input string that was entered.
 *
 * @param strings A list of strings that this function repeats on a single line.
 * @param option This option determines whether to add a newline character ('\n')
 * @return void
*/

t_exit_code	echo(char **strings, char *option)
{
	const size_t	len = ft_strs_len((const char **)strings);
	size_t			i;
	char 			*ret;

	if (!len_zero(len, option))
		return (EXIT_SUCCESS);
	if(ft_calloc_guard((void **)&ret, 1, sizeof(char *)) == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		ret = ft_strjoin_and_free(ret, strings[i], FREE_S1);
		ret = ft_strjoin_and_free(ret, " ", FREE_S1);
		i++;
	}
	if (ft_strncmp(option, "-n", 2))
		ret[ft_strlen(ret) - 1] = '\n';
	else
		ret[ft_strlen(ret) - 1] = '\0';
	printf("%s", ret);
	if (ret)
		free(ret);
	return (EXIT_SUCCESS);
}
