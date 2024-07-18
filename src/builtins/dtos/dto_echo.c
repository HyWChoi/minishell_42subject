/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:41 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:30:46 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_bool	is_option(char **str)
{
	char	*tmp;

	tmp = *str;
	if (!*str)
		return (FALSE);
	if (ft_strncmp("-n", *str, 2) == 0)
	{
		tmp++;
		while (*tmp)
		{
			if (*tmp != 'n')
				return (FALSE);
			tmp++;
		}
		return (TRUE);
	}
	return (FALSE);
}

t_exit_code	dto_echo(t_token *token)
{
	char	*option;
	char	**argv;

	option = "";
	argv = token-> argv + 1;
	while (argv)
	{
		if (is_option(argv))
		{
			option = *(argv);
			argv = argv + 1;
		}
		else
			break ;
	}
	return (echo(argv, option));
}
