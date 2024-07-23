/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:35 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 20:33:50 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "tksh_parse.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>
#include "get_next_line.h"

int	heredoc(char *filename, char *limiter, char ***envp, t_bool expand)
{
	int		fd;
	char	*line;

	if (safety_open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644, &fd) == -1)
		return (-1);
	while (1)
	{
		heredoc_signal_hook();
		if (g_sig_flag)
			break ;
		line = readline("heredoc> ");
		if (heredoc_need_stop(line, limiter))
			break ;
		if (expand)
			line = expand_line(line, envp);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

void	heredoc_hook(t_token **token_list)
{
	t_file_list	*file_list;

	file_list = NULL;
	while (*token_list)
	{
		if ((*token_list)->file)
			file_list = (*(*token_list)->file);
		while (file_list)
		{
			if (file_list->type == HEREDOC)
			{
				if (heredoc(file_list->file_name, file_list->limiter,
						(*token_list)->envp, file_list->expand) == -1)
					return ;
			}
			file_list = file_list->next;
		}
		token_list++;
	}
}
