/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_from_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:37 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/25 18:01:56 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>
#include "tksh_error.h"

static char	**get_paths_from_env(char **envp);
static char	*ex_get_abs_path_of_cmd(char *cmd, char **paths);
static char *ex_handle_cmd_without_slash(char *cmd, char **paths);
static char	*ex_handle_cmd_with_slash(char *cmd, char *err_cmd);

char	*get_cmd_path_from_env(char *cmd, char **envp)
{
	char	**paths;
	char	*ret;
	
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ex_handle_cmd_with_slash(cmd, cmd));
	paths = get_paths_from_env(envp);
	ret = ex_get_abs_path_of_cmd(cmd, paths);
	if (paths)
		ft_free_strs(paths);
	if (!ret)
		return (NULL);
	return (ret);
}


static char	*ex_handle_cmd_with_slash(char *cmd, char *err_cmd)
{
	if (access(cmd, F_OK) == ACCESS_ERROR)
	{
		put_err_msg(err_cmd, "No such file or directory\n");
		exit(ECODE_NO_SEARCH_FILE_OR_DIR);
	}
	if (isdir(cmd) == ACCESS_SUCESS)
	{
		put_err_msg(err_cmd, "is a directory\n");
		exit(ECODE_CMD_IS_DIR);
	}
	if (access(cmd, X_OK) == ACCESS_ERROR)
	{
		put_err_msg(err_cmd, "Permission denied\n");
		exit(ECODE_PERMISSION_DENIED);
	}
	return (prs_safety_strdup(cmd));
}

static char *ex_handle_cmd_without_slash(char *cmd, char **paths)
{
	char	*ret;
	char	*temp;
	char	*available_path;
	int		i;

	i = 0;
	available_path = NULL;
	while (paths && paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if(!temp)
			exit(ECODE_MALLOC_FAIL);
		ret = ft_strjoin_and_free(temp, cmd, FREE_S1);
		if (!ret)
			exit(ECODE_MALLOC_FAIL);
		if (access(ret, F_OK) == ACCESS_SUCESS
			&& isdir(ret) != ACCESS_SUCESS)
		{
			if (access(ret, X_OK) == ACCESS_SUCESS)
			{
				if (available_path)
				{
					free(available_path);
					available_path = NULL;
				}
				return (ret);
			}
			else
			{
				if (available_path == NULL)
					available_path = ret;
			}
		}
		i++;
	}
	if (available_path)
		return (available_path);
	return (NULL);
}

static char	*ex_get_abs_path_of_cmd(char *cmd, char **paths)
{
	char	*ret;
	char	*temp;

	ret = ex_handle_cmd_without_slash(cmd, paths);
	if (ret)
		return (ret);
	if(!paths || (paths && !paths[0]))
	{
		temp = ft_strjoin("./", cmd);
		if (!temp)
			exit(ECODE_MALLOC_FAIL);
		ret = ex_handle_cmd_with_slash(temp, cmd);
		free(temp);
		if (ret)
			return (ret);
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
			path = prs_safety_strdup(envp[i] + 5);
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
