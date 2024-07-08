/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:00:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/08 16:06:11 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "tksh.h"
#include "tksh_parse.h"
#include <stdio.h>

void	add_env(t_token *token, char *key_value)
{
	const int origin_env_len = ft_strs_len((const char **)(*(token->envp)));
	int i;
	char **new_envp;
	
	i = 0;
	if (!ft_calloc_guard((void **)&new_envp, (origin_env_len + 2), sizeof(char *)))
		return ; // TODO: signal error;
	while(i < origin_env_len)
	{
		new_envp[i] = ft_strdup((*(token->envp))[i]);
		i++;
	}
	new_envp[i] = ft_strdup(key_value);
	new_envp[i + 1] = NULL;
	ft_free_strs(*(token->envp));
	*token->envp = new_envp;
}


static t_bool invalid_char(char *str)
{
	if(ft_strchr(" \t\n\r\v\f=$*?\\\"\'", *str) != NULL)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief export function
 *
 * This function
 * to the path specified by the argument.
 *
 * @param path The path to change the current working directory to.
 * @return void
*/
//TODO: when key is exist, update value
t_exit_code	export(t_token *token)
{
	int			i;
	int			argv_len = ft_strs_len((const char **)(token->argv));
	t_exit_code ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (i < argv_len)
	{
		if (ft_isdigit(*token->argv[i]) == TRUE || ft_strchr(token->argv[i], ' ') != NULL || ft_strchr(token->argv[i], '\t') != NULL || *token->argv[i] == '=' || invalid_char(token->argv[i])){
			printf("export: '%s': not a valid identifier\n", token->argv[i]);
			ret = EXIT_FAILURE;
		}
		// else if (is_exist_env(token->argv))

			add_env(token, token->argv[i]); //TODO: if key is exist, update value
		i++;
	}
	return (ret);
}