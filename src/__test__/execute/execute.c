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

typedef struct s_pipe
{
	int prev[2];
	int curr[2];
} t_pipe;

typedef enum e_pipe
{
	FD_IN,
	FD_OUT
} t_pipe_fd;



void ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes)
{
	(void)ps_len;
	if (nth == 0)
		pipe(pipes->curr);
	else
	{
		pipes->prev[FD_IN] = pipes->curr[FD_IN];
		pipes->prev[FD_OUT] = pipes->curr[FD_OUT];
		pipe(pipes->curr);
	}
}


void pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len)
{
	int	infile_fd;
	int	outfile_fd;

	if (nth == 0)
		ex_move2fd((pipes->curr[FD_OUT], STDOUT_FILENO);
	else
	{
		ex_move2fd((pipes->prev[FD_IN], STDIN_FILENO);
		ex_move2fd((pipes->curr[FD_OUT], STDOUT_FILENO);
	}
}

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
	run_cmd(token);
}

void	execute(t_token **token_list)
{
	const io_fd_t	io_fd = io_store();
	size_t			token_len;
	int				endstatus;
	size_t			i;
	pid_t			last_pid;
	t_pipe			*pipes;


	i = 0;
	token_len = get_token_len(token_list);

	heredoc_hook(token_list);
	if (token_len == 1)
	{
		ex_run_singlecmd(*token_list);
		return ;
	}
	while (i < token_len)
	{
		ex_prepare_pipe(token_len, i, pipe);
		last_pid = fork();
		if (!ex_is_parent(last_pid))
		{
			ex_fork_error_guard(last_pid, "fork error");
			ex_run_subprocess(token_list[i], pipe, i, token_len);
		}
		destroy_pipe(pipe, i);
		i++;
	}
	io_restore(io_fd);
	while(token_len)
	{
		end_pid = waitpid(-1, &endstatus, 0);
		if (end_pid == -1)
			break;
		if (end_pid == 0)
			continue;
		token_len--;
	}
	(void)end_pid;
}
