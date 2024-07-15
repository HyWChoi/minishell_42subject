/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:13:19 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 12:13:20 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_io_utils.h"

ssize_t	safety_open(char *filename, int option, int mode, int *fd)
{
	*fd = open(filename, option, mode);
	if (*fd == -1)
	{
		perror("heredoc");
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
		return (safety_open(file->file_name, O_RDONLY, 0644, &file->fd));
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
			return (safety_open(file->file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644, &file->fd));
		else if (file->type == APPEND)
			return (safety_open(file->file_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644, &file->fd));
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
