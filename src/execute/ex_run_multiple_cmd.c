/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_run_multiple_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:09:12 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/23 12:50:42 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

void	ex_run_child(t_token *token, t_pipe *pipes, int nth, int ps_len)
{
	pipe_connect(token, pipes, nth, ps_len);
	if (io_redirection(token) == -1)
		exit(1);
	if (token->cmd_path == NULL)
		exit(0);
	run_cmd(token);
}
