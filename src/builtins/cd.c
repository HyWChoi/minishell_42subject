/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/03 11:00:28 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tksh.h"
#include <unistd.h>
#include <stdio.h>

void	cd(char *path)
{
	char	*error_msg;

	error_msg = "cd: no such file or directory: ";
	if (chdir(path) != 0)
	{
		write(2, error_msg, ft_strlen(error_msg));
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
}
