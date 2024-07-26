/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:51 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/26 15:38:47 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"

t_exit_code	dto_cd(t_token *token)
{
	char		*result_home;
	t_exit_code	code;

	if (ft_strs_len((const char **)token->argv) == 1)
	{
		result_home = NULL;
		result_home = prs_parse_variable("$HOME", token->envp);
		if (!*result_home)
		{
			free(result_home);
			put_err_msg("cd", "HOME not set\n");
			return (EXIT_FAILURE);
		}
		code = cd(token, result_home);
		free(result_home);
		return (code);
	}
	return (cd(token, *(token->argv + 1)));
}
