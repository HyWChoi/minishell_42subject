/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:32 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

t_exit_code	pwd(void)
{
	char	buff[PWD_MAX_BUFF_SIZE];

	ft_memset(buff, 0, PWD_MAX_BUFF_SIZE);
	if (!getcwd(buff, PWD_MAX_BUFF_SIZE))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	buff[ft_strlen(buff)] = '\n';
	write(1, buff, ft_strlen(buff));
	return (EXIT_SUCCESS);
}
