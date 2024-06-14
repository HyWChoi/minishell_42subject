/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:23:04 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/05/27 16:26:00 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Duplicates a string up to a specified length.
 * 
 * This function duplicates up to 'n' characters from the input string 's1'.
 * If the length of 's1' is less than 'n', it duplicates the entire string.
 * The resulting string is null-terminated.
 * 
 * @note The input string 's1' must not be a null pointer.
 *
 * @param s1 The null-terminated input string to duplicate.
 * @param n The maximum number of characters to duplicate.
 * @return A pointer to the newly allocated string, or NULL if the allocation fails.
 */
char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;
	const size_t	len = ft_strlen(s1);
	
	if (len < n)
		n = len;
	ret = NULL;
	if(!ft_calloc_guard((void **)&ret, 1, sizeof(char) * (n + 1)))
		return (NULL);
	ft_memcpy(ret, s1, n);
	return (ret);
}
