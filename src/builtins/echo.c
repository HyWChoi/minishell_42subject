/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:19:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/03 16:58:17 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include <stdio.h>

/**
 * @brief echo
 *
 * This function repeats the input string that was entered.
 *
 * @param strings A list of strings that this function repeats on a single line.
 * @param option This option determines whether to add a newline character ('\n')
 * @return void
*/

void	echo(char **strings, char *option)
{
	const size_t	len = ft_strs_len((const char **)strings);
	size_t			i;
	char 			*ret;

	if(ft_calloc_guard((void **)&ret, 1, sizeof(char *)) == NULL)
		return (NULL);
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
}
