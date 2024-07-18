/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:32:31 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:32:31 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "tksh_parse.h"

t_bool	export_is_correct_key(size_t key_len, char *str, char *key)
{
	return (
		(key_len == prs_count_str_using_func(str, prs_is_equal, FALSE))
		&& (ft_strncmp(key, str, key_len) == 0));
}

int	export_is_exist_env(t_token *token, char *key_name)
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

t_bool	export_invalid_char(char *str)
{
	while (*str)
	{
		if (!(ft_isalnum(*str) != FALSE || *str == '_'))
			return (TRUE);
		str++;
	}
	return (FALSE);
}

t_bool	export_is_valid_key(char *key)
{
	return (!(ft_isdigit(*key) == TRUE || export_invalid_char(key)
			|| ft_strchr(key, ' ') || ft_strchr(key, '\t')
			|| ft_strchr(key, '\n') || ft_strchr(key, '\v')
			|| ft_strchr(key, '\f') || ft_strchr(key, '\r')));
}
