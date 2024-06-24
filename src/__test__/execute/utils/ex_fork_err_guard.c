/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_fork_err_guard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:35:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 16:35:53 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <stdio.h>

void	ex_fork_error_guard(int pid, char *msg)
{
	if (pid >= 0)
		return ;
	perror(msg);
	exit(0);
}
