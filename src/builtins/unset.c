/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:45:55 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/08 15:30:54 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static size_t *us_get_key_idx(char *name, char **envp)
{
	const size_t len = ft_strs_len((const char **)envp);
	char 		*key;
	size_t		idx;
	size_t		*ret;

	idx = 0;
	while (idx < len)
	{
		key = ft_substr(envp[idx], 0, ft_strchr(envp[idx], '=') - envp[idx]);
		if (!key)
			return (NULL);
		if (ft_strncmp(name, key, ft_strlen(key) + 1) == 0)
		{
			free(key);
			if (ft_calloc_guard((void **)&ret, 1, sizeof(size_t)) == NULL)
				return (NULL);
			*ret = idx;
			return (ret);
		}
		free(key);
		idx++;
	}
	return (NULL);
}

/**
 * @brief Unset the environment variables.
 *
 * @param argv The arguments.
 * @param envp The environment variables.
 * @return void
*/
// TODO: unset 유효하지 않은 변수명이 올 경우 1 리턴 - 하나라도 유효하지 않은 변수명이 있다면 1 리턴
// 대신 동작은 다해야함
t_exit_code unset(char **argv, char **envp)
{
	size_t env_len;
	size_t *key_idx;

	while (*argv)
	{
		env_len = ft_strs_len((const char **)envp);
		if (ft_strlen(*argv) == 0 || us_get_key_idx(*argv, envp) == NULL)
		{
			argv++;
			continue;
		}
		key_idx = us_get_key_idx(*argv, envp);
		free(envp[*key_idx]);
		ft_memmove((envp + *key_idx), (envp + *key_idx + 1), (env_len - *key_idx) * sizeof(char *));
		envp[env_len] = NULL;
		argv++;
	}
	return (0);
}
