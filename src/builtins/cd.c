/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/08 15:26:33 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief change directory
 *
 * This function will change the current working directory
 * to the path specified by the argunment.
 *
 * @param path The path to change the current working directory to.
 * @return void
*/
t_exit_code	cd(char *path)
{
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
	}
}
