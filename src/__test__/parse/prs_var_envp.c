#include "tksh_parse.h"
#include "libft.h"
#include <stdio.h>

static size_t	prs_count_str_using_func(char *str, t_bool (*f)(char *), t_bool count_if_true)
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
	return (NULL);
}

char	*prs_parse_variable(char *str, char ***envp)
{
	char	*start;
	char	*result;
	char	*parsed_var;
	size_t	count;

	start = str;
	result = NULL;
	parsed_var = NULL;
	count = prs_count_str_using_func(str, prs_is_variable, FALSE);
	result = ft_strndup(start, count);
	// printf("count : %zu\n", count);
	str += count + 1;
	if (prs_is_possible_var_space(str))
	{
		count = prs_count_str_using_func(str, prs_is_possible_var_name, TRUE);
		parsed_var = prs_find_value_in_envp(str, envp);
		str += count;
	}
	if (parsed_var)
		result = ft_strjoin_and_free(result, parsed_var, FREE_BOTH);
	if (*str != '\0')
		result = ft_strjoin_and_free(result, str, FREE_S1);
	free(start);
	return (result);
}
