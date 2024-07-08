#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

size_t	prs_count_str_using_func(char *str, t_bool (*f)(char *), t_bool count_if_true)
{
	size_t	count;

	count = 0;
	if (count_if_true)
	{
		while (*str && f(str))
		{
			count++;
			str++;
		}
	}
	else
	{
		while (*str && !f(str))
		{
			count++;
			str++;
		}
	}
	return (count);
}

char	*prs_find_value_in_envp(char *str, char ***envp)
{
	size_t	count;
	char	*envp_key;
	int		i;

	i = 0;
	envp_key = NULL;
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

char	*prs_parse_variable(char *str, char ***envp)
{
	char	*start;
	char	*result;
	char	*parsed_var;
	size_t	count;

	start = str;
	result = ft_strdup("");
	parsed_var = NULL; //$앞까지 저장
	count = 0;
	while (*str)
	{
		if (prs_is_variable(str)) // $뒤에 가능한 공간이면 파싱
		{
			count = prs_count_str_using_func(start, prs_is_variable, FALSE);
			result = ft_strjoin_and_free(result, ft_strndup(start, count), FREE_BOTH);
			if (prs_is_possible_var_space(str + 1))
			{
				count = prs_count_str_using_func(str + 1, prs_is_possible_var_name, TRUE);
				parsed_var = prs_find_value_in_envp(str + 1, envp);
				if (parsed_var)
					result = ft_strjoin_and_free(result, parsed_var, FREE_BOTH);
				str += count;
			}
			else
			{
				result = ft_strjoin_and_free(result, "", FREE_S1);
				str += 1;
			}
			start = str + 1;
		}
		else
			str++;
	}
	if (*start)
		result = ft_strjoin_and_free(result, start, FREE_S1);
	return (result);
}
