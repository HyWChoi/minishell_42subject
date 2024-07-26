/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:45:55 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/26 19:28:03 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

static ssize_t	us_get_key_idx(char *name, char **envp)
{
	const size_t	len = ft_strs_len((const char **)envp);
	char			*key;
	size_t			idx;

	idx = 0;
	while (idx < len)
	{
		key = ft_substr(envp[idx], 0, ft_strchr(envp[idx], '=') - envp[idx]);
		if (!key)
			return (-1);
		if (ft_strncmp(name, key, ft_strlen(key) + 1) == 0)
		{
			free(key);
			return (idx);
		}
		free(key);
		idx++;
	}
	return (-1);
}

static void	us_remove_key(char **envp, size_t key_idx)
{
	const size_t	env_len = ft_strs_len((const char **)envp);

	free(envp[key_idx]);
	ft_memmove((envp + key_idx), (envp + key_idx + 1),
		(env_len - key_idx - 1) * sizeof(char *));
	envp[env_len - 1] = NULL;
}

t_exit_code	unset(char **argv, char **envp)
{
	size_t		key_idx;
	t_exit_code	exit_code;

	exit_code = EXIT_SUCCESS;
	while (*argv)
	{
		if (ft_strlen(*argv) == 0 || us_get_key_idx(*argv, envp) == -1)
		{
			if (export_is_valid_key(*argv) == FALSE)
			{
				printf("unset: `%s': not a valid identifier\n", *argv);
				exit_code = EXIT_FAILURE;
			}
			argv++;
			continue ;
		}
		key_idx = us_get_key_idx(*argv, envp);
		if (*envp)
		us_remove_key(envp, key_idx);
		argv++;
	}
	return (exit_code);
}
