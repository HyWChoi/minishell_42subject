/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:35 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/09 21:15:12 by yechakim         ###   ########.fr       */
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

static int heredoc_rl_event_hook_placeholder(void)
{
	return (0);
}

static void heredoc_stop_readline(int sig)
{
	struct termios term;

	(void)sig;
	rl_done = 1;
	g_sig_flag = SIGINT_FLAG_ON;
	rl_replace_line("", 0);
	rl_redisplay();
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}


void heredoc_signal_hook()
{
	rl_event_hook = heredoc_rl_event_hook_placeholder;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_stop_readline);
}

void heredoc(char *filename, char *limiter)
{
	int fd;
	char *line;

	printf("filename: %s\n", filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc open");
		exit(1);
	}
	while (1)
	{
		heredoc_signal_hook();
		line = readline(STDIN_FILENO);
		if (line == NULL)
			break;
		if (g_sig_flag == SIGINT_FLAG_ON)
		{
			free(line);
			break;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			printf("heredoc end\n");
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
}

void heredoc_hook(t_token **token_list)
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
				heredoc(file_list->file_name, file_list->limiter);
			file_list = file_list->next;
		}
		token_list++;
	}
}
