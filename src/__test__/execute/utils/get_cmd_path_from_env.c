/* ************************************************************************** */
/*                                                                            */
/*                                                        ::     :::::::  */
/*   get_cmd_path_from_env.c                            :+     :+   :+  */
/*                                                    +:+ +:+         +:+     */
/*   Byyechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created2024/06/24 15:45:44 by yechakim          #+#    #+#             */
/*   Updated2024/07/11 16:56:57 by yechakim         ###   ########.fr       */
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

char	*ex_get_abs_path_of_cmd(char *cmd, char **paths) // cmd == "a"
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
	 	if (access(cmd, F_OK | X_OK) == ACCESS_SUCESS)
		{
			if(isdir(cmd) != ACCESS_SUCESS) 
				return (ft_strdup(cmd)); //  commnad found
			else {
				put_err_msg(cmd, "is a directory\n");
				exit(ECODE_CMD_NOT_EXECUTABLE);
			}
		}
		put_err_msg(cmd, "command not found\n");
		exit(ECODE_CMD_NOT_FOUND);
	}
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
	put_err_msg(cmd, "command not found\n");
	exit(ECODE_CMD_NOT_FOUND);
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
			if (!path) // TODOsignal error 처리
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths) // TODOsignal error 처리
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
