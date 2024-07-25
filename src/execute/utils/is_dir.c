/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:12:36 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/25 12:13:22 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <dirent.h>

int	isdir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (ACCESS_ERROR);
	closedir(dir);
	return (ACCESS_SUCESS);
}