/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_exitcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:06:34 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 12:13:27 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

t_exit_code	ex_return_exit_code(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
