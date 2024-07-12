/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:12:46 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/12 16:10:34 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

void	run_cmd(t_token *token)
{
	char		*cmd_abs_path;
	t_exit_code	exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin_cmd(token->cmd_path) == TRUE)
	{
		exit_code = builtin_handler(token);
		exit(exit_code);
	}
	cmd_abs_path = get_cmd_path_from_env(token->cmd_path, *token->envp);
	if (cmd_abs_path == NULL)
		exit(127);
	if (execve(cmd_abs_path, token->argv, *token->envp) == -1)
	{
		perror(cmd_abs_path);
		exit(EXIT_FAILURE);
	}
}
