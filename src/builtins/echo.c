/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:19:17 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/08 16:04:50 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
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

t_exit_code	echo(char **strings, char *option)
{
	const size_t	len = ft_strs_len((const char **)strings);
	size_t			i;
	char 			*ret;

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
