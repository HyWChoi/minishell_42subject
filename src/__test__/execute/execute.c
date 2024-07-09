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
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int ex_run_singlecmd(t_token *token)
{
	pid_t pid;
	int status;
	io_redirection(token);

	if (token->cmd_path == NULL)
		return (0);
  	if (is_builtin_cmd(token->cmd_path))
    {
        builtin_handler(token);
        // TODO: signal 처리
        return (0);
    }
	pid = fork();
	if(pid == 0)
		run_cmd(token);
    while(waitpid(pid, &status, 0) != pid) ;
	return status;
}

void shutout_signal()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}



unsigned char execute(t_token **token_list)
{
	const io_fd_t	io_fd = io_store();
	size_t			token_len;
	int				endstatus;
	size_t			i;
	pid_t			last_pid;
    pid_t           ended_pid;
	t_pipe			pipes;


	i = 0;
	shutout_signal();
	if(!token_list)
		return (1); // TODO : parse error에 대한 exitcode정의 처리	
	token_len = get_token_len(token_list);
	heredoc_hook(token_list);
	if (token_len == 1)
	{
		endstatus = ex_run_singlecmd(*token_list);
		io_restore(io_fd);
		return (ex_return_exit_code(endstatus));
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
	while (token_len)
	{
		ended_pid = waitpid(-1, &endstatus, WNOHANG);
		if (ended_pid == -1)
			continue;
		if (last_pid == ended_pid)
			break ;
		token_len--;
	}
	return (ex_return_exit_code(endstatus));
	(void)last_pid;
}