/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/25 18:01:07 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"
#include <errno.h>

void	run_cmd(t_token *token)
{
	char		*cmd_abs_path;
	t_exit_code	exit_code;

	reset_signal();
	if (is_builtin_cmd(token->cmd_path) == TRUE)
	{
		exit_code = builtin_handler(token);
		exit(exit_code);
	}
	cmd_abs_path = get_cmd_path_from_env(token->cmd_path, *token->envp);
	if (cmd_abs_path == NULL)
		exit(ECODE_CMD_NOT_FOUND);
	if (execve(cmd_abs_path, token->argv, *token->envp) == -1)
	{
		perror(token->cmd_path);
		if (errno == EACCES || errno == EISDIR)
			exit(ECODE_PERMISSION_DENIED);
		exit(ECODE_CMD_NOT_FOUND);
	}
}
