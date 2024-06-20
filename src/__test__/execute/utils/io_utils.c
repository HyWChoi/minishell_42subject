/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/21 01:48:21 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

void    io_redirection(t_token *token)
{
    (void)token;
}

void io_restore(io_fd_t io_fd)
{
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    dup2(io_fd.stdin_fd, STDIN_FILENO);
    dup2(io_fd.stdout_fd, STDOUT_FILENO);
}

io_fd_t io_store(void)
{
    io_fd_t io_fd;

    io_fd.stdin_fd = dup(STDIN_FILENO);
    io_fd.stdout_fd = dup(STDOUT_FILENO);
    return (io_fd);
}