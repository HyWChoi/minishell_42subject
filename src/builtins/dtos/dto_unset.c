/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:31 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:30:32 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdio.h>

t_exit_code	dto_unset(t_token *token)
{
	return (unset(token->argv, *(token->envp)));
}
