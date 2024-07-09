/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:00:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/09 17:52:25 by hyeonwch         ###   ########.fr       */
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

void	replace_value(t_token *token, char *key, char *new_key)
{
	int		i;
	int		env_len = ft_strs_len((const char **)*(token->envp));
	char	*key_value;
	size_t	key_len = ft_strlen(key);

	i = 0;
	key_value = ft_strndup(new_key + key_len, prs_count_str_using_func(new_key, prs_is_end_of_str, FALSE));
	if (!*key_value)
		return ;
	while (i < env_len)
	{
		if (key_len == prs_count_str_using_func((*(token->envp))[i], prs_is_equal, FALSE) && ft_strncmp(key, (*(token->envp))[i], key_len) == 0)
		{
			free((*(token->envp))[i]);
			(*(token->envp))[i] = ft_strjoin(key, key_value);
			break ;
		}
		i++;
	}
	free(key_value);
	free(key);
}

static t_bool invalid_char(char *str)
{
	if(ft_strchr(" \t\n\r\v\f=$*?\\\"\'", *str) != NULL)
		return (TRUE);
	return (FALSE);
}


int	is_exist_env(t_token *token, char *key_name)
{
	int	i;
	int	env_len = ft_strs_len((const char **)*(token->envp));
	size_t	key_len = ft_strlen(key_name);

	i = 0;
	while (i < env_len)
	{
		if (key_len == prs_count_str_using_func((*(token->envp))[i], prs_is_equal, FALSE) && ft_strncmp(key_name, (*(token->envp))[i], key_len) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_valid_key(char *key)
{
	if (ft_isdigit(*key) == TRUE || ft_strchr(key, ' ') != NULL || ft_strchr(key, '\t') != NULL || *key == '=' || invalid_char(key))
		return (FALSE);
	return (TRUE);
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
	char		*key_name;
	t_exit_code ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (i < argv_len)
	{
		if (!is_valid_key(token->argv[i]))
		{
			printf("export: '%s': not a valid identifier\n", token->argv[i]);
			ret = EXIT_FAILURE;
			i++;
			continue ;
		}
		key_name = ft_strndup(token->argv[i], prs_count_str_using_func(token->argv[i], prs_is_equal, FALSE));
		if (is_exist_env(token, key_name))
			replace_value(token, key_name, token->argv[i]);
		else
			add_env(token, token->argv[i]); //TODO: if key is exist, update value
		i++;
	}
	return (ret);
}
