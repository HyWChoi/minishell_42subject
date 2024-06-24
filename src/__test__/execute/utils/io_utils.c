/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 00:39:33 by yechakim          #+#    #+#             */
/*   Updated: 2024/06/24 20:58:06 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "tksh_parse.h"
#include <fcntl.h>
/* 
typedef enum	e_file_type
{
	APPEND,
	HEREDOC,
	IN_FILE,
	OUT_FILE
}	t_file_type;

typedef struct	s_file_list
{
	char				*file_name;
	char				*limiter;
	t_file_type			type;
	int					fd;
	struct s_file_list	*next;
}	t_file_list;

token {
    t_file_list **file;
}
*/

void ex_move2fd((int from, int to)
{
	dup2(from, to);
	close(from);
}

void ex_setup_infile(t_file_list *file)
{
    if(file->type == IN_FILE)
    {
        file->fd = open(file->file_name, O_RDONLY);
        if (file->fd == -1)
        {
            perror("open");
            exit(1);
        }
    }
}
void ex_setup_outfile(t_file_list *file)
{
    if (file->type == OUT_FILE)
    {
        file->fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file->fd == -1)
        {
            perror("open");
            exit(1);
        }
    }
}
void ex_setup_here_doc(t_file_list *file)
{
    if (file->type == HEREDOC)
    {
        file->fd = open(file->file_name, O_RDONLY);
        if (file->fd == -1)
        {
            perror("open");
            exit(1);
        }
    }
}
void ex_setup_append(t_file_list *file)
{
    if (file->type == APPEND)
    {
        file->fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (file->fd == -1)
        {
            perror("open");
            exit(1);
        }
    }
}
t_bool ex_file_has_next(t_file_list *file)
{
    return (file->next != NULL);
}


void infile_redirection(t_file_list *file)
{
    t_file_list *last_infile_node;

    last_infile_node = NULL;
    while(file)
    {
        if (file->type == IN_FILE || file->type == HEREDOC)
        {
            if (last_infile_node != file)
            {
                if (last_infile_node)
                    close(last_infile_node->fd);
            }
            last_infile_node = file;
            file->fd = open(file->file_name, O_RDONLY);
            if (file->fd == -1)
            {
                perror("open");
                exit(1);
            }
        }
        file = file->next;
    }
	if (last_infile_node)
		move2fd(last_infile_ndoe->fd, STDIN_FILENO);
	
		
}




void    io_redirection(t_token *token)
{
    t_file_list	*file;
    int			last_in_fd;
    int			last_out_fd;
    
    if (!token->file)
        return ;
    file = *token->file;
    infile_redirection(file);
    output_redirection(file);
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