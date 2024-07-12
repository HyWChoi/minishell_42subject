/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/12 18:04:24 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

void	io_restore(io_fd_t io_fd)
{
	dup2(io_fd.stdin_fd, STDIN_FILENO);
	dup2(io_fd.stdout_fd, STDOUT_FILENO);
	close(io_fd.stdin_fd);
	close(io_fd.stdout_fd);
}

io_fd_t	io_store(void)
{
	io_fd_t	io_fd;

	io_fd.stdin_fd = dup(STDIN_FILENO);
	io_fd.stdout_fd = dup(STDOUT_FILENO);
	return (io_fd);
}
