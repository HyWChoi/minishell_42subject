/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/06 14:28:43 by hyeonwch         ###   ########.fr       */
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
	char	*error_msg;

	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
	}
}
