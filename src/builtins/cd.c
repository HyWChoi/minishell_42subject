/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:27:24 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/26 20:11:09 by hyeonwch         ###   ########.fr       */
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
		perror("cd");
		return (NULL);
	}
	*result = prs_safety_strdup(path);
	return (*result);
}

char	*cd_renew_path(t_token *token, char *new_path, char *s_old_path)
{
	char	*oldpwd;
	char	*pwd;
	char	*result;

	pwd = NULL;
	if (export_is_exist_env(token, "PWD"))
	{
		if (export_is_exist_env(token, "OLDPWD"))
		{
			oldpwd = prs_safety_strjoin_and_free("OLDPWD=", prs_parse_variable("$PWD", token->envp), FREE_S2);
			replace_value(token, "OLDPWD", oldpwd);
		}
		if (!cd_get_path(&pwd))
		{
			pwd = prs_safety_strjoin_and_free(prs_parse_variable("$PWD", token->envp), "/", FREE_S1);
			pwd = prs_safety_strjoin_and_free(pwd, new_path, FREE_BOTH);
		}
		result = prs_safety_strdup(pwd);
		pwd = prs_safety_strjoin_and_free("PWD=", prs_safety_strdup(pwd), FREE_S2);
		replace_value(token, "PWD", pwd);
		return (result);
	}
	if (export_is_exist_env(token, "OLDPWD"))
	{
		oldpwd = prs_safety_strjoin_and_free("OLDPWD=", (*token->envp)[1], FREE_S2);
		replace_value(token, "OLDPWD", oldpwd);
		if (!cd_get_path(&pwd))
		{
			pwd = prs_safety_strjoin_and_free(prs_safety_strdup(s_old_path), "/", FREE_S1);
			pwd = prs_safety_strjoin_and_free(pwd, new_path, FREE_BOTH);
		}
		result = prs_safety_strdup(pwd);
		pwd = prs_safety_strjoin_and_free("?PWD=", prs_safety_strdup(pwd), FREE_S2);
		replace_value(token, "?PWD", pwd);
	}
}

t_exit_code	cd(t_token *token, char *path)
{
	static char	*pwd = prs_parse_variable("$PWD", token->envp);

	if (ft_strlen(path) == 0)
		return (0);
	if (chdir(path) != 0)
	{
		write(2, "cd: ", 4);
		perror(path);
		return (EXIT_FAILURE);
	}
	cd_renew_path(token, path, pwd);
	return (EXIT_SUCCESS);
}
