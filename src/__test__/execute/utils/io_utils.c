/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/09 21:22:59 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "tksh_parse.h"
#include <fcntl.h>
#include <stdio.h>

void ex_move_2_fd(int from, int to)
{
	dup2(from, to);
	close(from);
}

void throw_open_error(char *filename, int fd)
{
    if (fd == -1)
    {
        perror(filename);
        exit(1);
    }
    
}

void infile_open(t_file_list *file, t_file_list **last_infile_node){
    
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
            throw_open_error(file->file_name, file->fd);
    }
}

void outfile_open(t_file_list *file, t_file_list **last_infile_node)
{
    if (file->type == OUT_FILE || file->type == APPEND)
    {
        if (*last_infile_node != file)
        {
            if (*last_infile_node && (*last_infile_node)->fd != -1)
                close((*last_infile_node)->fd);
        }
        *last_infile_node = file;
        if(file->type == OUT_FILE)
            file->fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (file->type == APPEND)
            file->fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (file->fd == -1)
            throw_open_error(file->file_name, file->fd);
    }
}

void redirect_2_file(t_file_list *file)
{
    t_file_list *last_infile_node;
    t_file_list *last_outfile_node;

    last_infile_node = NULL;
    last_outfile_node = NULL;
    while(file)
    {
        infile_open(file, &last_infile_node);
        outfile_open(file, &last_outfile_node);
        file = file->next;
    }
	if (last_infile_node)
		ex_move_2_fd(last_infile_node->fd, STDIN_FILENO);
    if (last_outfile_node)
        ex_move_2_fd(last_outfile_node->fd, STDOUT_FILENO);
}

void    io_redirection(t_token *token)
{
    t_file_list	*file;
    
    if (!token->file)
        return ;
    file = *token->file;
    redirect_2_file(file);
}

void destroy_pipe(t_pipe *pipe, int i, int cmd_cnt)
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

void ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes)
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
void pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len)
{
    (void)ps_len;
    (void)ps;
    
	if (nth == 0)
		ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
	else if(nth == (ps_len - 1))
        ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
    else
    {
        ex_move_2_fd(pipes->prev[FD_IN], STDIN_FILENO);
        ex_move_2_fd(pipes->curr[FD_OUT], STDOUT_FILENO);
    }
}