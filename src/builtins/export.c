/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:00:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 21:25:13 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "tksh.h"
#include "tksh_parse.h"
#include <stdio.h>

void	add_env(t_token *token, char *key_value)
{
	const int	origin_env_len = ft_strs_len((const char **)(*(token->envp)));
	int			i;
	char		**new_envp;

	i = 0;
	if (!ft_calloc_guard((void **)&new_envp, (origin_env_len + 2),
			sizeof(char *)))
		return ;
	while (i < origin_env_len)
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
	int		env_len;
	char	*key_value;
	size_t	key_len;

	i = 0;
	env_len = ft_strs_len((const char **)*(token->envp));
	key_len = ft_strlen(key);
	key_value = ft_strndup(new_key + key_len,
			prs_count_str_using_func(new_key, prs_is_end_of_str, FALSE));
	if (!*key_value)
		return (free_keys(key, key_value));
	while (i < env_len)
	{
		if (export_is_correct_key(key_len, (*(token->envp))[i], key))
		{
			free((*(token->envp))[i]);
			(*(token->envp))[i] = ft_strjoin(key, key_value);
			break ;
		}
		i++;
	}
	free_keys(key, key_value);
}

static void	handle_export_key(t_token *token, char *key_name, char *arg)
{
	if (export_is_exist_env(token, key_name))
		replace_value(token, key_name, arg);
	else
	{
		add_env(token, arg);
		free(key_name);
	}
}

static t_exit_code	process_export_argument(t_token *token,
												int i, t_exit_code ret)
{
	char	*key_name;

	key_name = ft_strndup(token->argv[i], prs_count_str_using_func(
				token->argv[i], prs_is_equal, FALSE));
	if (!key_name || !*key_name || !export_is_valid_key(key_name))
	{
		printf("export: '%s': not a valid identifier\n", token->argv[i]);
		if (key_name)
			free(key_name);
		return (EXIT_FAILURE);
	}
	handle_export_key(token, key_name, token->argv[i]);
	return (ret);
}

t_exit_code	export(t_token *token)
{
	int			i;
	int			argv_len;
	t_exit_code	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	argv_len = ft_strs_len((const char **)(token->argv));
	while (i < argv_len)
	{
		ret = process_export_argument(token, i, ret);
		i++;
	}
	return (ret);
}
