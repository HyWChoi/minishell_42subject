/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:00:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/12 17:40:28 by hyeonwch         ###   ########.fr       */
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

static t_bool	export_is_correct_key(size_t key_len, char *str, char *key)
{
	return (
		(key_len == prs_count_str_using_func(str, prs_is_equal, FALSE))
		&& (ft_strncmp(key, str, key_len) == 0));
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
		return ;
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
	free(key_value);
	free(key);
}

int	is_exist_env(t_token *token, char *key_name)
{
	int		i;
	int		env_len;
	size_t	key_len;

	i = 0;
	env_len = ft_strs_len((const char **)*(token->envp));
	key_len = ft_strlen(key_name);
	while (i < env_len)
	{
		if (export_is_correct_key(key_len, (*(token->envp))[i], key_name))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static t_bool	invalid_char(char *str)
{
	while (*str)
	{
		if (!(ft_isalnum(*str) != FALSE || *str == '_'))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

t_bool	is_valid_key(char *key)
{
	return (!(ft_isdigit(*key) == TRUE || invalid_char(key)));
}

t_exit_code	export(t_token *token)
{
	int			i;
	int			argv_len;
	char		*key_name;
	t_exit_code	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	argv_len = ft_strs_len((const char **)(token->argv));
	while (i < argv_len)
	{
		key_name = ft_strndup(token->argv[i], prs_count_str_using_func(token->argv[i], prs_is_equal, FALSE));
		if (!is_valid_key(key_name))
		{
			printf("export: '%s': not a valid identifier\n", token->argv[i]);
			free(key_name);
			ret = EXIT_FAILURE;
			i++;
			continue ;
		}
		if (is_exist_env(token, key_name))
			replace_value(token, key_name, token->argv[i]);
		else
		{
			add_env(token, token->argv[i]); //TODO: if key is exist, update value
			free(key_name);
		}
		i++;
	}
	return (ret);
}
