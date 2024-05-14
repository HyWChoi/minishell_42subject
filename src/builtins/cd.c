/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/14 18:04:14 by yechakim         ###   ########seoul.kr  */
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
void	cd(char *path)
{


	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
	}
}
