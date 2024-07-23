/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/14 14:52:38 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

void	io_restore(t_io_fd io_fd)
{
	dup2(io_fd.stdin_fd, STDIN_FILENO);
	dup2(io_fd.stdout_fd, STDOUT_FILENO);
	close(io_fd.stdin_fd);
	close(io_fd.stdout_fd);
}

t_io_fd	io_store(void)
{
	t_io_fd	io_fd;

	io_fd.stdin_fd = dup(STDIN_FILENO);
	io_fd.stdout_fd = dup(STDOUT_FILENO);
	return (io_fd);
}
