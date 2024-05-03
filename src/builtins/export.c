/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:20:47 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/03 18:31:13 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"

char **merge_strs(char **dst, char **strs)
{
	size_t i = 0;
	size_t j = 0;
	size_t len = ft_strs_len(dst);
	size_t len2 = ft_strs_len(strs);
	char **new_strs = (char **)malloc(sizeof(char *) * (len + len2 + 1));
	
	if (!new_strs)
		return (NULL);
	while (i < len)
	{
		new_strs[i] = ft_strdup(dst[i]);
		i++;
	}
	while (j < len2)
	{
		new_strs[i] = ft_strdup(strs[j]);
		i++;
		j++;
	}
	new_strs[i] = NULL;
	ft_strs_free(dst);
	return (new_strs);
}


/**
 * @brief export environment variable
 * 
 * This function will add or modify the environment variable
 * specified by the argument.
 * 
 * @param name The name of the environment variable to add or modify.
 * @param value The value of the environment variable to add or modify.
 * @return void
*/
void	export(char *new_key_value_raw, char ***envp)
{
	size_t	i;
	char 	**incoming_key_values;
	char	*delimeter;
	
	incoming_key_values = ft_split(new_key_value_raw, ' ');
	i = 0;
	while(incoming_key_values[i])
	{
		delimeter = ft_strchr(incoming_key_values[i], '=');
		if(delimeter == incoming_key_values[i])
			write("export: '=' not found in the argument\n");
		else if(delimeter)
		{
			
		}
		free(incoming_key_values[i]);
		i++;
	}	
}
