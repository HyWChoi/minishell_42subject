/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:50 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/22 17:28:01 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_prompt.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include "get_next_line.h"

static void	tks_stop_readline(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sig_flag = SIGINT_FLAG_ON;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_code(1, NULL);
}

static int	sig_hook(void)
{
	if (g_sig_flag == SIGINT_FLAG_ON)
		g_sig_flag = SIGINT_FLAG_OFF;
	return (0);
}

static void	tksh_sig_hook(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	signal(SIGINT, tks_stop_readline);
	signal(SIGQUIT, SIG_IGN);
	rl_signal_event_hook = sig_hook;
}

char	*tksh_prompt(char *envp)
{
	char	*input;

	(void)envp;
	tksh_sig_hook();
	if (isatty(STDOUT_FILENO))
		input = readline(PROMPT);
	else
	{
		if (isatty(STDIN_FILENO) != 0)
			write(STDERR_FILENO, PROMPT, ft_strlen(PROMPT));
		input = get_next_line(0);
	}
	if (!input)
	{
		printf("exit\n");
		exit(0);
	}
	else if (*input)
		add_history(input);
	else
	{
		free(input);
		return (NULL);
	}
	return (input);
}
