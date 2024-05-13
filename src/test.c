/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:37:09 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/13 20:09:04 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tksh.h"
#include "tksh_prompt.h"
#include "tksh_builtins.h"
#include <stdio.h>

static t_token	*set_token(char *cmd, char **argv, char ***env)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd_path = cmd;
	token->argv = argv;
	token->envp = env;
	return (token);

}
/**
 * @brief main of test
 * IMPORTANT: This is a MAIN Function of "test_shell"
*/
int main(int argc, char **argv, const char **initial_envp)
{
	char	***envp = NULL;
	char	**splited_str;
	t_token	*token;
	(void)argc;
	(void)argv;
	
	*envp = ft_strs_copy(initial_envp);
	while (1)
	{
		char *origin_str = tksh_prompt(**envp);
		printf("ori str: %s\n", origin_str);
		splited_str = ft_split(origin_str, ' ');
		token = set_token(splited_str[0], splited_str + 1, &initial_envp);
		printf("tokens cmd: %s\n", token->cmd_path);
		printf("tokens argv: %s\n", *(token->argv));
		printf("tokens envp: %s\n", *(*(token->envp)));
		builtin_hander(token);
	}
	return (0);
}
