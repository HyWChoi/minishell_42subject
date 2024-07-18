/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:45:55 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/18 22:09:40 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static size_t	*us_get_key_idx(char *name, char **envp)
{
	const size_t	len = ft_strs_len((const char **)envp);
	char			*key;
	size_t			idx;
	size_t			*ret;

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

t_exit_code	unset(char **argv, char **envp)
{
	size_t	env_len;
	size_t	*key_idx;
	t_exit_code	exit_code;

	exit_code = EXIT_SUCCESS;
	while (*argv)
	{
		env_len = ft_strs_len((const char **)envp);
		if (ft_strlen(*argv) == 0 || us_get_key_idx(*argv, envp) == NULL)
		{
			if (export_is_valid_key(*argv) == FALSE)
				printf("unset: `%s': not a valid identifier\n");
			exit_code = EXIT_FAILURE;
			argv++;
			continue ;
		}
		key_idx = us_get_key_idx(*argv, envp);
		free(envp[*key_idx]);
		ft_memmove((envp + *key_idx), (envp + *key_idx + 1),
			(env_len - *key_idx) * sizeof(char *));
		envp[env_len] = NULL;
		argv++;
	}
	return (exit_code);
}
