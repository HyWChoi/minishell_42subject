/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:14:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/16 23:29:27 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include "tksh_parse.h"
#include <stdlib.h>
#include <stdio.h>

void	display_declare(char **envp)
{
	char	*key_value;
	char	*key_name;
	int		len_key_name;

	while (*envp)
	{
		key_name = ft_strndup(*envp,
				prs_count_str_using_func(*envp, prs_is_equal, FALSE) + 1);
		len_key_name = ft_strlen(key_name);
		key_value = ft_strndup(*envp + len_key_name,
				prs_count_str_using_func(*envp + len_key_name,
					prs_is_end_of_str, FALSE));
		if (ft_strncmp(key_name, "?", 1) != 0)
		{
			if (key_name[len_key_name - 1] == '=')
				printf("%s\"%s\"\n", key_name, key_value);
			else
				printf("%s\n", key_name);
		}
		free(key_name);
		free(key_value);
		envp++;
	}
}

t_exit_code	dto_export(t_token *token)
{
	if (token->argv[1] == NULL)
	{
		display_declare(*(token->envp));
		return (EXIT_SUCCESS);
	}
	else
		return (export(token));
}
