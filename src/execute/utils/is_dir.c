/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:12:36 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/26 23:43:00 by yechakim         ###   ########seoul.kr  */
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
