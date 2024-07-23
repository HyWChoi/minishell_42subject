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

#include <stdio.h>
#include "tksh_execute.h"
#include "tksh_builtins.h"

void	init_pipe(t_pipe *pipes)
{
	pipes->prev[FD_IN] = 0;
	pipes->prev[FD_OUT] = 0;
	pipes->curr[FD_IN] = 0;
	pipes->curr[FD_OUT] = 0;
}

static pid_t	execute_with_multi_cmd(
				t_token **token_list, size_t token_len, t_pipe *pipes)
{
	pid_t	last_pid;
	size_t	i;

	i = 0;
	while (i < token_len)
	{
		ex_prepare_pipe(token_len, i, pipes);
		last_pid = fork();
		if (ex_is_child(last_pid))
		{
			ex_fork_error_guard(last_pid, "fork error");
			ex_run_child(token_list[i], pipes, i, token_len);
		}
		destroy_pipe(pipes, i, token_len);
		i++;
	}
	return (last_pid);
}

unsigned char	execute(t_token **token_list)
{
	const t_io_fd	io_fd = io_store();
	size_t			token_len;
	t_pipe			pipes;
	pid_t			last_pid;
	t_exit_code		exitcode;

	shutout_signal();
	init_pipe(&pipes);
	token_len = get_token_len(token_list);
	heredoc_hook(token_list);
	if (ex_sig_catched(io_fd))
		return (1);
	if (token_len == 1)
	{
		exitcode = ex_run_singlecmd(*token_list);
		io_restore(io_fd);
		return (exitcode);
	}
	last_pid = execute_with_multi_cmd(token_list, token_len, &pipes);
	io_restore(io_fd);
	return (ex_wait_children_ended(token_len, last_pid));
}
