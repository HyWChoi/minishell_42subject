#include "tksh_parse.h"
#include "libft.h"

char	*prs_find_value_in_envp(char *str, char ***envp)
{
	const size_t	len = ft_strlen(str);
	t_bool			is_found;
	size_t			i;

	i = 0;
	is_found = FALSE;
	while (*envp[i])
	{
		if (ft_strncmp(*envp[i], str, len) == 0)
		{
			is_found = TRUE;
			break ;
		}
		i++;
	}
	free(str);
	if (is_found)
		return (*envp[i] + len);
	return (NULL);
}

char	*prs_find_envp(char *str, char ***envp)
{
	char	*start;
	char	*envp_value;
	char	*result;
	size_t	i;

	i = 0;
	start = str;
	while (*start && !prs_is_variable(start))
		start++;
	result = ft_strndup(start, start - str - 1);
	if (prs_is_variable(start) && prs_is_possible_var_space(start + 1))
	{
		str++;
		while (*(start + i) && prs_is_possible_var_name(start + i))
			i++;
		envp_value = ft_strjoin_and_free(ft_strndup(start, i - 1), "=", FREE_S1);
		envp_value = prs_find_value_in_envp(envp_value, envp);
		if (envp_value)
			result = ft_strjoin_and_free(result, envp_value, FREE_BOTH);
	}
	result = ft_strjoin_and_free(result, ft_strdup(start + i), FREE_S1);
	free(str);
	return (result);
}
