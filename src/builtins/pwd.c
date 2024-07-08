/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:14 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/08 16:04:03 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

t_exit_code	pwd(void)
{
	char	buff[PWD_MAX_BUFF_SIZE];

	if (!getcwd(buff, PWD_MAX_BUFF_SIZE))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buff);
	return (EXIT_SUCCESS);
}
