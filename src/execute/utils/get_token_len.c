/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:27:14 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/12 16:22:21 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_execute.h"

size_t	get_token_len(t_token **token_list)
{
	size_t	len;

	len = 0;
	while (token_list[len])
		len++;
	return (len);
}
