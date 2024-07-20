/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_err_free_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:36:36 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:36:39 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh.h"
#include "tksh_parse.h"

void	*prs_err_free_all(char *usr_input,
		t_prs_stack **stack_list, t_token **token_list)
{
	free(usr_input);
	prs_free_stack_list(stack_list);
	tksh_free_token_list(token_list);
	return (NULL);
}
