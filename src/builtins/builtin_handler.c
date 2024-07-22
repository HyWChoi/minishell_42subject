/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:21:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/22 14:50:55 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

void	handle_sig(int sig)
{
	if (sig == SIGPIPE)
	{
		write(STDERR_FILENO, "Borken pipe\n", 12);
		exit(SIGPIPE);
	}
}

static ssize_t	builtin_handler_helper_get_cmd(char *cmd)
{
	ssize_t		cmd_idx;
	const char	*builtin_cmds[BUITIN_CMD_AMOUNT]
		= {CD, ECHO_STR, ENV, EXIT, PWD, UNSET, EXPORT};

	cmd_idx = 0;
	while (cmd_idx < BUITIN_CMD_AMOUNT)
	{
		if (ft_strncmp(builtin_cmds[cmd_idx],
				cmd, ft_strlen(builtin_cmds[cmd_idx]) + 1) == 0)
			return (cmd_idx);
		cmd_idx++;
	}
	return (-1);
}

static void	initialize_builtin_dtos(
				t_builtin_dto *builtin_dtos[BUITIN_CMD_AMOUNT])
{
	builtin_dtos[0] = dto_cd;
	builtin_dtos[1] = dto_echo;
	builtin_dtos[2] = dto_env;
	builtin_dtos[3] = dto_exit;
	builtin_dtos[4] = dto_pwd;
	builtin_dtos[5] = dto_unset;
	builtin_dtos[6] = dto_export;
}

t_exit_code	builtin_handler(t_token *token)
{
	t_builtin_dto	*builtin_dtos[BUITIN_CMD_AMOUNT];
	const ssize_t	cmd_idx = builtin_handler_helper_get_cmd(token->cmd_path);

	signal(SIGPIPE, handle_sig);
	initialize_builtin_dtos(builtin_dtos);
	if (cmd_idx == -1)
		return (ECODE_CMD_NOT_FOUND);
	return (builtin_dtos[cmd_idx](token));
}
