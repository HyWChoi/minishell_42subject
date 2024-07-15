/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_run_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:09:12 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 12:09:43 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

void	ex_run_child(t_token *token, t_pipe *pipes, int nth, int ps_len)
{
	pipe_connect(token, pipes, nth, ps_len);
	io_redirection(token);
	if (token->cmd_path == NULL)
		exit(0);
	run_cmd(token);
}
