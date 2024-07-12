/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/12 16:21:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "tksh_parse.h"
#include <fcntl.h>
#include <stdio.h>

void	ex_move_2_fd(int from, int to)
{
	dup2(from, to);
	close(from);
}

ssize_t	throw_open_error(char *filename, int fd)
{
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	return (0);
}

ssize_t	infile_open(t_file_list *file, t_file_list **last_infile_node)
{
	if (file->type == IN_FILE || file->type == HEREDOC)
	{
		if (*last_infile_node != file)
		{
			if (*last_infile_node && (*last_infile_node)->fd != -1)
				close((*last_infile_node)->fd);
		}
		*last_infile_node = file;
		file->fd = open(file->file_name, O_RDONLY);
		if (file->fd == -1)
			return (throw_open_error(file->file_name, file->fd));
		return (0);
	}
	return (0);
}

ssize_t	outfile_open(t_file_list *file, t_file_list **last_infile_node)
{
	if (file->type == OUT_FILE || file->type == APPEND)
	{
		if (*last_infile_node != file)
		{
			if (*last_infile_node && (*last_infile_node)->fd != -1)
				close((*last_infile_node)->fd);
		}
		*last_infile_node = file;
		if (file->type == OUT_FILE)
			file->fd = open(file->file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			file->fd = open(file->file_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->fd == -1)
			return (throw_open_error(file->file_name, file->fd));
		return (0);
	}
	return (0);
}

ssize_t	redirect_2_file(t_file_list *file)
{
	t_file_list	*last_infile_node;
	t_file_list	*last_outfile_node;

	last_infile_node = NULL;
	last_outfile_node = NULL;
	while (file)
	{
		if (infile_open(file, &last_infile_node) == -1)
			return (-1);
		if (outfile_open(file, &last_outfile_node) == -1)
			return (-1);
		file = file->next;
	}
	if (last_infile_node)
		ex_move_2_fd(last_infile_node->fd, STDIN_FILENO);
	if (last_outfile_node)
		ex_move_2_fd(last_outfile_node->fd, STDOUT_FILENO);
	return (0);
}

ssize_t	io_redirection(t_token *token)
{
	t_file_list	*file;

	if (!token->file)
		return (0);
	file = *token->file;
	if (redirect_2_file(file) == -1)
		return (-1);
	return (0);
}

void	destroy_pipe(t_pipe *pipe, int i, int cmd_cnt)
{
	if (i == 0)
		close(pipe->curr[FD_OUT]);
	else if (i != (cmd_cnt - 1))
	{
		close(pipe->prev[FD_IN]);
		close(pipe->curr[FD_OUT]);
	}
	else
	{
		close(pipe->prev[FD_IN]);
		close(pipe->curr[FD_OUT]);
		close(pipe->curr[FD_IN]);
	}
}

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

void	ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes)
{
	(void)ps_len;
	if (nth == 0)
		pipe(pipes->curr);
	else
	{
		pipes->prev[FD_IN] = pipes->curr[FD_IN];
		pipes->prev[FD_OUT] = pipes->curr[FD_OUT];
		pipe(pipes->curr);
	}
}

void	pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len)
{
	(void)ps_len;
	(void)ps;
	if (nth == 0)
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
	else if (nth == (ps_len - 1))
		ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
	else
	{
		ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
	}
}
