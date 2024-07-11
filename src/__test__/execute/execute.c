/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   execute.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yechakim <yechakim@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/20 23:26:03 by yechakim		  #+#	#+#			 */
/*   Updated: 2024/06/21 00:38:24 by yechakim		 ###   ########seoul.kr  */
/*																			*/
/* ************************************************************************** */

#include "tksh_execute.h"
#include <stdio.h>
#include "tksh_builtins.h"

t_bool ex_is_parent(pid_t pid)
{
	if (pid > 0)
		return (TRUE);
	return (FALSE);
}

void ex_run_subprocess(t_token *token, t_pipe *pipes, int nth, int ps_len)
{
	pipe_connect(token, pipes, nth, ps_len);
	io_redirection(token);
	if(token->cmd_path == NULL)
		exit(0);
	run_cmd(token);
}
t_exit_code ex_return_exit_code(int status)
{
	if (WIFSIGNALED(status)){
		return (WTERMSIG(status) + 128);
	}
	else if (WIFEXITED(status)){
		return (WEXITSTATUS(status));
	}
	return (0);
}

t_exit_code ex_run_singlecmd(t_token *token)
{
	pid_t pid;
	int status;
	if (io_redirection(token) == -1)
		return (1);
	if (token->cmd_path == NULL)
		return (0);
  	if (is_builtin_cmd(token->cmd_path))
        return (builtin_handler(token));
	pid = fork();
	ex_fork_error_guard(pid, "fork error");
	if (!ex_is_parent(pid))
		run_cmd(token);
	waitpid(pid, &status, 0);
	return (ex_return_exit_code(status));
}

void shutout_signal()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void ex_wait_children_ended(int token_len, int last_pid, int *endstatus)
{
	int	ended_pid;
	int	status;
	while (token_len)
	{
		ended_pid = waitpid(-1, &status, 0);
		if (ended_pid == -1)
			continue;
		if (ended_pid == last_pid)
			*endstatus = status;
		token_len--;
	}
}

unsigned char execute(t_token **token_list)
{
	const io_fd_t	io_fd = io_store();
	size_t			token_len;
	size_t			i;
	pid_t			last_pid;
	t_pipe			pipes;
	int				endstatus;

	i = 0;
	shutout_signal();
	if(!token_list)
		return (1); // TODO : parse error에 대한 exitcode정의 처리	
	token_len = get_token_len(token_list);
	heredoc_hook(token_list);
	if(g_sig_flag == SIGINT_FLAG_ON)
	{
		g_sig_flag = SIGINT_FLAG_OFF;
		io_restore(io_fd);
		return (1);
	}
	if (token_len == 1)
	{
		endstatus = ex_run_singlecmd(*token_list);
		io_restore(io_fd);
		return (endstatus);
	}
	while (i < token_len)
	{
		ex_prepare_pipe(token_len, i, &pipes);
		last_pid = fork();
		if (!ex_is_parent(last_pid))
		{
			ex_fork_error_guard(last_pid, "fork error");
			ex_run_subprocess(token_list[i], &pipes, i, token_len);
		}
		destroy_pipe(&pipes, i, token_len);
		i++;
	}
	io_restore(io_fd);
	ex_wait_children_ended(token_len, last_pid, &endstatus);
	return (ex_return_exit_code(endstatus));
	(void)last_pid;
}
