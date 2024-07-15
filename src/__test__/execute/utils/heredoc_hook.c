/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:35 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/14 14:34:54 by hyeonwch         ###   ########.fr       */
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

static int	heredoc_rl_event_hook(void)
{
	struct termios	term;

	if (g_sig_flag == SIGINT_FLAG_ON)
	{
		rl_done = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &term);
		return (0);
	}
	return (0);
}

static void	heredoc_stop_readline(int sig)
{
	(void)sig;
	rl_done = 1;
	g_sig_flag = SIGINT_FLAG_ON;
}

static void	heredoc_signal_hook(void)
{
	rl_event_hook = heredoc_rl_event_hook;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_stop_readline);
}

int	heredoc(char *filename, char *limiter)
{
	int		fd;
	char	*line;

	if (safety_open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644, &fd) == -1)
		return (-1);
	while (1)
	{
		heredoc_signal_hook();
		line = readline("heredoc> ");
		if (line == NULL || g_sig_flag
			|| ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
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
				if (heredoc(file_list->file_name, file_list->limiter) == -1)
					return ;
			}
			file_list = file_list->next;
		}
		token_list++;
	}
}
