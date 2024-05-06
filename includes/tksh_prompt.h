/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:14:12 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/06 15:16:57 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_PROMPT_H
# define TKSH_PROMPT_H

# define SHELL_NAME "tekkenshell "
# define PROMPT SHELL_NAME "$ "

char *tksh_prompt(char *envp);

#endif
