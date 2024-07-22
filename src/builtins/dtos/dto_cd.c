/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:51 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/22 13:22:03 by yechakim         ###   ########.fr       */
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
			return (EXIT_FAILURE);
		}
		code = cd(result_home);
		free(result_home);
		return (code);
	}
	return (cd(*(token->argv + 1)));
}
