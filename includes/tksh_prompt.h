/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tksh_prompt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:14:12 by yechakim          #+#    #+#             */
/*   Updated: 2024/05/01 14:19:20 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSH_PROMPT_H
# define TKSH_PROMPT_H


# define SHELL_NAME "tekkenshell "
# define PROMPT SHELL_NAME "$ "

char *tksh_prompt(char *envp);

#endif