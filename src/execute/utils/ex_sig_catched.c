/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_sig_catched.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:30:14 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/23 15:54:51 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
