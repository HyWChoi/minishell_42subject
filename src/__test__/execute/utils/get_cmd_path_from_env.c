/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_from_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:44 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/09 18:42:17 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>

static int isdir(char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
		return (ACCESS_ERROR);
	closedir(dir);
	return (ACCESS_SUCESS);
}



char	*ex_get_abs_path_of_cmd(char *cmd, char **paths)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == ACCESS_SUCESS)
	{
		if(isdir(cmd) != ACCESS_SUCESS)
			return (ft_strdup(cmd));
		else {
			printf("tksh: %s: is a directory\n", cmd);
			exit(ECODE_CMD_NOT_EXECUTABLE);
		}
	}
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	while (paths[i])
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
	temp = ft_strjoin("./", cmd);
	if (access(temp, F_OK | X_OK) == 0)
	{
		if(isdir(temp) != 0)
			return (temp);
	}
	free(temp);
	return (ft_strdup(cmd));
}

static char **get_paths_from_env(char **envp)
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
			if (!path) // TODO: signal error 처리
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths) // TODO: signal error 처리
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char        *get_cmd_path_from_env(char *cmd, char **envp)
{
	char **paths;
	char *ret;

	if (ft_strchr(cmd, '/') == cmd)
		return (ft_strdup(cmd));
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	ret = ex_get_abs_path_of_cmd(cmd, paths);
	ft_free_strs(paths);
	if (!ret)
		return (NULL);
	return (ret);
}
