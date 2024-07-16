/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:13:15 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/16 20:54:35 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

void	destroy_pipe(t_pipe *pipe, int i, int cmd_cnt)
{
	if (i == 0)
		close(pipe->curr[FD_OUT]);
	else if (i != (cmd_cnt - 1))
	{
		close(pipe->prev[FD_IN]);
		close(pipe->curr[FD_OUT]);
	}
	else
		close(pipe->prev[FD_IN]);
}

void	ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes)
{
	(void)ps_len;
	if (nth == 0)
		pipe(pipes->curr);
	else
	{
		pipes->prev[FD_IN] = pipes->curr[FD_IN];
		pipes->prev[FD_OUT] = pipes->curr[FD_OUT];
		if(nth != (ps_len - 1))
			pipe(pipes->curr);
	}
}

void	pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len)
{
	(void)ps_len;
	(void)ps;
	if (nth == 0)
	{
		close(pipes->curr[FD_IN]);
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
	}
	else if (nth == (ps_len - 1))
		ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
	else
	{
		ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
	}
}
