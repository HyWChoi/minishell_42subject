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

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	if (len < n)
		n = len;
	ret = NULL;
	if(!ft_calloc_guard((void **)&ret, 1, sizeof(char) * (n + 1)))
		return (NULL);
	ft_memcpy(ret, s1, n);
	return (ret);
}
