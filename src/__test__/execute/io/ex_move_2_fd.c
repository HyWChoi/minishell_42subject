/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_move_2_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:59:47 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 20:12:43 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

ssize_t	ex_move_2_fd(int from, int to, t_error_behavior error_behavior)
{
	if (dup2(from, to) == -1)
	{
		perror("dup2");
		if (error_behavior == EXIT_ON_ERROR)
			exit(1);
		else if (error_behavior == CONTINUE_ON_ERROR)
			return (-1);
	}
	if (close(from) == -1)
	{
		perror("close");
		if (error_behavior == EXIT_ON_ERROR)
			exit(1);
		else if (error_behavior == CONTINUE_ON_ERROR)
			return (-1);
	}
	return (0);
}
