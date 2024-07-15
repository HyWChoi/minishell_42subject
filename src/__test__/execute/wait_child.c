/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:05:58 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 12:06:13 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

void	ex_wait_children_ended(int token_len, int last_pid, int *endstatus)
{
	int	ended_pid;
	int	status;

	while (token_len)
	{
		ended_pid = waitpid(-1, &status, 0);
		if (ended_pid == -1)
			continue ;
		if (ended_pid == last_pid)
			*endstatus = status;
		token_len--;
	}
}
