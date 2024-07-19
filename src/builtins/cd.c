/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 09:06:04 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

t_exit_code	cd(char *path)
{
	if (ft_strlen(path) == 0)
		return (0);
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
