/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:13:15 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/23 02:14:07 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

void	destroy_pipe(t_pipe *pipe, int i, int cmd_cnt)
{
	if (i != (cmd_cnt - 1))
		close(pipe->curr[FD_OUT]);
	if (i != 0)
		close(pipe->prev[FD_IN]);
}

void	ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes)
{
	pipes->prev[FD_IN] = pipes->curr[FD_IN];
	pipes->prev[FD_OUT] = pipes->curr[FD_OUT];
	if (nth < ps_len - 1 && pipe(pipes->curr) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len)
{
	(void)ps_len;
	(void)ps;
	if (nth < ps_len - 1)
	{
		close(pipes->curr[FD_IN]);
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO, EXIT_ON_ERROR);
	}
	if (nth != 0)
		ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO, EXIT_ON_ERROR);
}
