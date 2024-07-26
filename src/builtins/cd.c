/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:15:00 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/27 00:15:21 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

char	*cd_get_path(char **result)
{
	char	path[PWD_MAX_BUFF_SIZE];

	ft_memset(path, 0, PWD_MAX_BUFF_SIZE);
	if (!getcwd(path, PWD_MAX_BUFF_SIZE))
	{
		write(2, "cd: error retrieving current directory: ", 39);
		write(2, "getcwd: cannot access parent directories: ", 42);
		perror("");
		return (NULL);
	}
	*result = prs_safety_strdup(path);
	return (*result);
}

void	cd_set_path_in_buffer(char *path, char saved_pwd[PWD_MAX_BUFF_SIZE])
{
	size_t	path_len;
	size_t	i;

	path_len = ft_strlen(path);
	if (path_len > PWD_MAX_BUFF_SIZE)
	{
		ft_memset(saved_pwd, 0, PWD_MAX_BUFF_SIZE);
		return ;
	}
	i = 0;
	while (i < path_len)
	{
		saved_pwd[i] = path[i];
		i++;
	}
	saved_pwd[i] = '\0';
}

void	cd_renew_path(t_token *token, char *new_path,
			char saved_pwd[PWD_MAX_BUFF_SIZE])
{
	if (export_is_exist_env(token, "PWD"))
	{
		update_oldpwd(token);
		update_pwd(token, new_path, saved_pwd);
		return ;
	}
	update_oldpwd_without_pwd(token);
	update_pwd_without_get_path(token, new_path, saved_pwd);
}

t_exit_code	cd(t_token *token, char *path)
{
	static char	saved_pwd[PWD_MAX_BUFF_SIZE];

	if (ft_strlen(path) == 0)
		return (0);
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
		return (EXIT_FAILURE);
	}
	cd_renew_path(token, path, saved_pwd);
	return (EXIT_SUCCESS);
}
