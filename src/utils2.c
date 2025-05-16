/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:51:50 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 11:51:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	ft_strcat(result, s3);
	return (result);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin3(dirs[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}

// En `env_utils.c`
char	**env_to_array(char **env)
{
	return (env);
}

// En `env_utils.c`
static int	compare_env_vars(const void *a, const void *b)
{
	return (ft_strcmp(*(const char **)a, *(const char **)b));
}

/* void	print_env_sorted(char **env)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = 0;
	while (env[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return ;
	ft_memcpy(sorted_env, env, sizeof(char *) * (count + 1));
	ft_qsort(sorted_env, count, sizeof(char *), compare_env_vars);
	i = 0;
	while (sorted_env[i])
	{
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
} */

void	print_export_entry(char *entry)
{
	char	*equal;
	char	*key;
	char	*value;

	ft_putstr_fd("declare -x ", 1);
	equal = ft_strchr(entry, '=');
	if (equal)
	{
		*equal = '\0';
		key = entry;
		value = equal + 1;
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putstr_fd("\"\n", 1);
		*equal = '=';
	}
	else
	{
		ft_putstr_fd(entry, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	print_env_sorted(char **env)
{
	char	**sorted_env;
	int		count;
	int		i;

	count = 0;
	while (env[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return ;
	ft_memcpy(sorted_env, env, sizeof(char *) * (count + 1));
	ft_qsort(sorted_env, count, sizeof(char *), compare_env_vars);
	i = 0;
	while (sorted_env[i])
	{
		print_export_entry(sorted_env[i]);
		i++;
	}
	free(sorted_env);
}
