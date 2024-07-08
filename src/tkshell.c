/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/08 17:28:14 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"
#include "tksh_execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

void setup_tty()
{
	int pid = fork();
	int status;
	const char *const tty = ttyname(STDIN_FILENO);
	char *dirname;
	
	dirname = ft_strjoin(TK_HEREDOC_PATH, tty);
	if (dirname == NULL)
	{
		ft_putendl_fd("cannot prepare the shell", 2);
		exit(1);
	}
	if (pid == 0)
	{
		if (execve("/bin/mkdir", (char *[]){"mkdir", "-p", dirname, NULL}, NULL) == -1)
		{
			perror("cannot prepare the shell");
			exit(1);
		}	
	}
	free((void *)dirname);
	waitpid(pid, &status, 0);
	if (status != 0)
	{
		perror("cannot start the shell");
		exit(1);
	}
}


int main(int argc, char **argv, const char **initial_envp)
{
	t_token	**token_list;
	char	***envp;
	t_exit_code exit_code = 0;
	(void)argc;
	(void)argv;

	token_list = NULL;
	char **tmp = ft_strs_copy(initial_envp);
	envp = &tmp;
	// set_exit_code(0);
	setup_tty();
	while (1)
	{
		char *origin_str = tksh_prompt(**envp);
		token_list = prs_parse(origin_str, envp);
		// dbg_print_token(token_list);
		exit_code = execute(token_list);
		if (token_list)
		{
			tksh_free_token_list(token_list);
		}
		// rl_on_new_line();
	}
	return (0);
}
