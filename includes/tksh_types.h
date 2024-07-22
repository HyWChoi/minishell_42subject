/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:39:28 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/23 02:47:21 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_TYPES_H
# define TKSH_TYPES_H

# include "libft.h"
# include <termios.h>

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
	t_bool				expand;
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
	ECODE_SYNTAX = 2,
	ECODE_BAD_FILE_DESCRIPTOR = 9,
	ECODE_CMD_NOT_EXECUTABLE = 126,
	ECODE_CMD_IS_DIR = 126,
	ECODE_PERMISSION_DENIED = 126,
	ECODE_CMD_NOT_FOUND = 127,
	ECODE_NO_SEARCH_FILE_OR_DIR = 127,
	ECODE_SIGNAL_SALT = 128,
	ECODE_FORK_FAILED = 130,
};

enum e_corect{
	ACCESS_SUCESS = 0,
	ACCESS_ERROR = -1
};

typedef struct s_term
{
	struct termios	term;
	struct termios	term_backup;
}	t_term;

#endif
