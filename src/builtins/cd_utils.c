/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:11:47 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/27 00:16:54 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include <unistd.h>
#include <stdio.h>

void	update_oldpwd(t_token *token)
{
	char	*oldpwd;

	if (export_is_exist_env(token, "OLDPWD"))
	{
		oldpwd = prs_parse_variable("$PWD", token->envp);
		oldpwd = prs_safety_strjoin_and_free("OLDPWD=", oldpwd, FREE_S2);
		export_replace_value(token, prs_safety_strdup("OLDPWD"), oldpwd);
		free(oldpwd);
	}
}

void	update_pwd(t_token *token, char *new_path,
			char saved_pwd[PWD_MAX_BUFF_SIZE])
{
	char	*pwd;

	if (!cd_get_path(&pwd))
	{
		pwd = prs_safety_strdup(saved_pwd);
		pwd = prs_safety_strjoin_and_free(pwd, "/", FREE_S1);
		pwd = prs_safety_strjoin_and_free(pwd, new_path, FREE_S1);
	}
	cd_set_path_in_buffer(pwd, saved_pwd);
	pwd = prs_safety_strjoin_and_free("PWD=", pwd, FREE_S2);
	export_replace_value(token, prs_safety_strdup("PWD"), pwd);
	free(pwd);
}

void	update_oldpwd_without_pwd(t_token *token)
{
	char	*oldpwd;

	if (export_is_exist_env(token, "OLDPWD"))
	{
		oldpwd = prs_safety_strdup(ft_strchr((*token->envp)[1], '=') + 1);
		oldpwd = prs_safety_strjoin_and_free("OLDPWD=", oldpwd, FREE_S2);
		export_replace_value(token, prs_safety_strdup("OLDPWD"), oldpwd);
		free(oldpwd);
	}
}

void	update_pwd_without_get_path(t_token *token, char *new_path,
			char saved_pwd[PWD_MAX_BUFF_SIZE])
{
	char	*pwd;

	if (!cd_get_path(&pwd))
	{
		pwd = prs_safety_strdup(saved_pwd);
		pwd = prs_safety_strjoin_and_free(pwd, "/", FREE_S1);
		pwd = prs_safety_strjoin_and_free(pwd, new_path, FREE_S1);
	}
	cd_set_path_in_buffer(pwd, saved_pwd);
	pwd = prs_safety_strjoin_and_free("?PWD=", pwd, FREE_S2);
	export_replace_value(token, prs_safety_strdup("?PWD"), pwd);
	free(pwd);
}
