/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:45:55 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/01 21:13:15 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	*us_get_key_idx(char *name, char **envp)
{
	const size_t	len = ft_strs_len((const char **)envp);
	char			*key;
	char			*delimeter_position;
	size_t			idx;
	size_t			*ret;

	idx = 0;
	while (idx < len)
	{
		delimeter_position = ft_strchr(envp[idx], '=');
		if (!delimeter_position)
			return (NULL);
		key = ft_substr(envp[idx], 0, delimeter_position - envp[idx]);
		if (!key)
			return (NULL);
		if (ft_strncmp(name, key, ft_strlen(key) +1) == 0)
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


void	unset(char **argv, char **envp)
{
	size_t			env_len; 
	size_t 			*key_idx;

	while (*argv)
	{
		env_len = ft_strs_len((const char **)envp);
		if (ft_strlen(*argv) == 0 || get_key_idx(*argv, envp) == NULL)
		{
			argv++;
			continue ;
		}
		key_idx = get_key_idx(*argv, envp);
		free(envp[*key_idx]);
		ft_memmove((envp + *key_idx), (envp + *key_idx + 1), (env_len - *key_idx) * sizeof(char *));
		envp[env_len] = NULL;
		argv++;
	}
}
