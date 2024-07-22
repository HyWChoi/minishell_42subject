/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_from_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:37 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/22 17:05:47 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>

static int	isdir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (ACCESS_ERROR);
	closedir(dir);
	return (ACCESS_SUCESS);
}

char	*ex_handle_cmd_with_slash(char *cmd)
{
	if (access(cmd, F_OK) == ACCESS_ERROR)
	{
		put_err_msg(cmd, "No such file or directory\n");
		exit(ECODE_NO_SEARCH_FILE_OR_DIR);
	}
	if (isdir(cmd) == ACCESS_SUCESS)
	{
		put_err_msg(cmd, "is a directory\n");
		exit(ECODE_CMD_IS_DIR);
	}
	if (access(cmd, X_OK) == ACCESS_ERROR)
	{
		put_err_msg(cmd, "Permission denied\n");
		exit(ECODE_PERMISSION_DENIED);
	}
	return (ft_strdup(cmd));
}

char	*ex_get_abs_path_of_cmd(char *cmd, char **paths)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ex_handle_cmd_with_slash(cmd));
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(temp, cmd);
		if (access(ret, F_OK | X_OK) == ACCESS_SUCESS
			&& isdir(ret) != ACCESS_SUCESS)
		{
			free(temp);
			return (ret);
		}
		free(temp);
		free(ret);
		i++;
	}
	put_err_msg(cmd, "command not found\n");
	exit(ECODE_CMD_NOT_FOUND);
}

static char	**get_paths_from_env(char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			if (!path)
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path_from_env(char *cmd, char **envp)
{
	char	**paths;
	char	*ret;

	paths = get_paths_from_env(envp);
	ret = ex_get_abs_path_of_cmd(cmd, paths);
	if (paths)
		ft_free_strs(paths);
	if (!ret)
		return (NULL);
	return (ret);
}
