/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:51 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:30:51 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

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
			return (1);
		}
		code = cd(result_home);
		free(result_home);
		return (code);
	}
	else if (ft_strs_len((const char **)token->argv) == 2)
		return (cd(*(token->argv + 1)));
	else
	{
		write(2, "cd: too many arguments\n", 24);
		return (1);
	}
}
