/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_process_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonwch <hyeonwch@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:51:23 by hyeonwch          #+#    #+#             */
/*   Updated: 2024/07/19 17:51:26 by hyeonwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tksh_parse.h"
#include "libft.h"

char	*prs_find_value_in_envp(char *str, char ***envp)
{
	size_t	count;
	char	*envp_key;
	int		i;

	i = 0;
	envp_key = NULL;
	if (*str == '?')
		count = 1;
	else
		count = prs_count_str_using_func(str, prs_is_possible_var_name, TRUE);
	envp_key = ft_strjoin_and_free(ft_strndup(str, count), "=", FREE_S1);
	while (*(*envp + i))
	{
		if (ft_strncmp(envp_key, *(*envp + i), count + 1) == 0)
		{
			free(envp_key);
			return (ft_strdup(*(*envp + i) + count + 1));
		}
		i++;
	}
	free(envp_key);
	return (NULL);
}
char	*prs_handle_possible_var_space(char **str, char ***envp, char *result)
{
	char	*parsed_var;
	size_t	count;

	count = prs_count_str_using_func(*str + 1, prs_is_possible_var_name, TRUE);
	parsed_var = prs_find_value_in_envp(*str + 1, envp);
	if (parsed_var)
		result = ft_strjoin_and_free(result, parsed_var, FREE_BOTH);
	*str += count;
	return (result);
}
char	*prs_process_variable(char **str,
			char **start, char ***envp, char *result)
{
	char	*temp;
	size_t	count;

	count = prs_count_str_using_func(*start, prs_is_variable, FALSE);
	result = ft_strjoin_and_free(result,
			ft_strndup(*start, count), FREE_BOTH);
	if (prs_is_possible_var_space(*str + 1))
	{
		result = prs_handle_possible_var_space(str, envp, result);
		*start = *str + 1;
	}
	else if (*(*str + 1) == '?')
	{
		temp = prs_find_value_in_envp(*str + 1, envp);
		result = ft_strjoin_and_free(result, temp, FREE_BOTH);
		(*str)++;
		*start = *str + 1;
	}
	else
	{
		result = ft_strjoin_and_free(result, "$", FREE_S1);
		(*str)++;
		*start = *str;
	}
	return (result);
}

char	*prs_parse_variable(char *str, char ***envp)
{
	char	*start;
	char	*result;

	start = str;
	result = ft_strdup("");
	while (*str)
	{
		if (prs_is_variable(str))
			result = prs_process_variable(&str, &start, envp, result);
		else
			str++;
	}
	if (*start)
		result = ft_strjoin_and_free(result, start, FREE_S1);
	return (result);
}
