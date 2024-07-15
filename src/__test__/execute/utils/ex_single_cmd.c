/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:58 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 16:51:48 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "tksh_builtins.h"

t_exit_code	ex_run_singlecmd(t_token *token, t_io_fd io_fd)
{
	pid_t	pid;
	int		status;
	t_exit_code exit_code;

	if (io_redirection(token) == -1)
		return (1);
	if (token->cmd_path == NULL)
		return (0);
	if (is_builtin_cmd(token->cmd_path))
	{
		exit_code = builtin_handler(token);
		io_restore(io_fd);
		return (exit_code);
	}
	pid = fork();
	ex_fork_error_guard(pid, "fork error");
	if (ex_is_child(pid))
		run_cmd(token);
	waitpid(pid, &status, 0);
	io_restore(io_fd);
	return (ex_return_exit_code(status));
}
