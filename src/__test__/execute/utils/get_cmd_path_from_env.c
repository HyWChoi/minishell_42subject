/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_from_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:45:44 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 16:37:57 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
char	*ex_get_abs_path_of_cmd(char *cmd, char **paths)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(temp, cmd);
		if (access(ret, F_OK) == 0)
		{
			free(temp);
			return (ret);
		}
		free(temp);
		free(ret);
		i++;
	}
	temp = ft_strjoin("./", cmd);
	if (access(temp, F_OK) == 0)
		return (temp);
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
	if (!paths) // TODO: signal error 처리
		return (NULL);
	ret = ex_get_abs_path_of_cmd(cmd, paths);
	ft_free_strs(paths);
	if (!ret) // TODO: signal error 처리
		return (NULL);
	return (ret);
}
