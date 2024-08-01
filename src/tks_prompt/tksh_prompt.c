/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:59:50 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/01 16:06:03 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_prompt.h"

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

static int	signal_event_hook(void)
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
	rl_event_hook = NULL;
	rl_signal_event_hook = signal_event_hook;
}

char	*tksh_readline(void)
{
	char	*input;

	tksh_sig_hook();
	if (isatty(STDOUT_FILENO))
		input = readline(PROMPT);
	else
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, PROMPT, ft_strlen(PROMPT));
		input = get_next_line(STDIN_FILENO);
	}
	return (input);
}

char	*tksh_prompt(void)
{
	char	*input;
	char	*temp;

	input = tksh_readline();
	if (!input)
		exit_on_eof();
	else if (*input)
	{
		add_history(input);
		temp = prs_safety_strtrim(input, PRS_WHITE_SPACE);
		free(input);
		input = temp;
	}
	if (input && *input == '\0')
	{
		free(input);
		return (NULL);
	}
	return (input);
}
