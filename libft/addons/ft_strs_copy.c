/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:26:04 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/03 14:38:01 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy the strings in the array of strings.
 * 
 * This function will copy the strings in the array of strings.
 * 
 * @param strs The array of strings to copy.
 * @return The copied array of strings.
 * @return NULL if the allocation fails.
*/
char	**ft_strs_copy(const char **strs)
{
	const size_t	len = ft_strs_len(strs);
	char 			**ret;
	size_t			i;

	if(ft_calloc_guard((void **)&ret, len + 1, sizeof(char *)))
		return (NULL);
	i = 0;
	while(strs[i])
	{
		ret[i] = ft_strdup(strs[i]);
		if(ret[i] == NULL)
		{
			ft_strs_free(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
