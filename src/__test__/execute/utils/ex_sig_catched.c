/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_sig_catched.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:30:14 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 20:11:20 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_signal.h"
#include "tksh_execute.h"

t_bool	ex_sig_catched(t_io_fd io_fd)
{
	if (g_sig_flag)
	{
		g_sig_flag = SIGINT_FLAG_OFF;
		io_restore(io_fd);
		return (TRUE);
	}
	return (FALSE);
}
