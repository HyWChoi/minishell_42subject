#ifndef TKSH_IO_UTILS_H
# define TKSH_IO_UTILS_H

# include "tksh_types.h"
# include "tksh_error.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/fcntl.h>

typedef struct s_io_fd
{
	int	stdin_fd;
	int	stdout_fd;
}	t_io_fd;

typedef struct s_pipe
{
	int	prev[2];
	int	curr[2];
}	t_pipe;

typedef enum e_pipe
{
	FD_IN = 0,
	FD_OUT = 1
}	t_pipe_fd;

ssize_t	ex_move_2_fd(int from, int to, t_error_behavior error_behavior);
ssize_t	safety_open(char *filename, int option, int mode, int *fd);
ssize_t	infile_open(t_file_list *file, t_file_list **last_infile_node);
ssize_t	outfile_open(t_file_list *file, t_file_list **last_infile_node);
ssize_t	redirect_2_file(t_file_list *file);
ssize_t	io_redirection(t_token *token);
void	destroy_pipe(t_pipe *pipe, int i, int cmd_cnt);
void	io_restore(t_io_fd io_fd);
t_io_fd	io_store(void);
void	ex_prepare_pipe(int ps_len, int nth, t_pipe *pipes);
void	pipe_connect(t_token *ps, t_pipe *pipes, int nth, int ps_len);

#endif
