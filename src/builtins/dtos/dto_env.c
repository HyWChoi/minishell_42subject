/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dto_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:38 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/18 20:30:39 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_exit_code	dto_env(t_token *token)
{
	return (env((const char **)*(token->envp)));
}
