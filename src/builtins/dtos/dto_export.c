/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:14:53 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/01 21:18:26 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief display declare
 * 
 * This function
 * to dipslay declare.
 * 
 * @param void
 * @return void
*/
void	display_declare(char **envp)
{
	char **key_value;
	
		
	while(*envp)
	{
		key_value = ft_split(*envp, '=');
		if(!key_value)
			return ;
			
		if (ft_strncmp(*key_value, "?", 1) != 0)
		{
			if (ft_strs_len((const char **)key_value) == 1)
				printf("%s\n", *key_value);
			else
				printf("%s=\"%s\"\n", *key_value, *(key_value + 1));
		}
		envp++;
	}
}

/**
 * @brief export dto
 *
 * This function
 * to the path specified by the argument.
 *
 * @param path The path to change the current working directory to.
 * @return void
*/

void	dto_export(t_token *token)
{
	if (token->argv[1] == NULL)
		display_declare(*(token->envp));
	else 
		export(token);	
}
