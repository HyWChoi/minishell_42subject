#ifndef TKSH_TYPES_H
# define TKSH_TYPES_H

typedef enum e_file_type
{
	APPEND,
	HEREDOC,
	IN_FILE,
	OUT_FILE
}	t_file_type;

typedef struct s_file_list
{
	char				*file_name;
	char				*limiter;
	t_file_type			type;
	int					fd;
	struct s_file_list	*next;
}	t_file_list;

typedef struct s_token
{
	char		*cmd;
	char		*cmd_path;
	char		**argv;
	char		***envp;
	t_file_list	**file;
}	t_token;

typedef unsigned char	t_exit_code;

enum e_exit_code {
	ECODE_SUCCESS = 0,
	ECODE_ERROR = 1,
	ECODE_CMD_NOT_EXECUTABLE = 126,
	ECODE_CMD_NOT_FOUND = 127,
	ECODE_SIGNAL_SALT = 128,
	ECODE_FORK_FAILED = 130
};

enum e_corect{
	ACCESS_SUCESS = 0,
	ACCESS_ERROR = -1
};

#endif
