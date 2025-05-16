/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/03/27 11:51:02 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 11:51:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *name, char **env)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

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

void	set_env_var(const char *name, const char *value, t_shell *shell)
{
	int		i;
	char	*new_var;

	if (value)
		new_var = ft_strjoin3(name, "=", value);
	else
		new_var = ft_strdup(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& (shell->env[i][ft_strlen(name)] == '='
			|| shell->env[i][ft_strlen(name)] == '\0'))
		{
			free(shell->env[i]);
			shell->env[i] = new_var;
			return ;
		}
		i++;
	}
	shell->env = ft_realloc(shell->env, (i + 2) * sizeof(char *));
	shell->env[i] = new_var;
	shell->env[i + 1] = NULL;
}

void	unset_env_var(const char *name, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, ft_strlen(name)) == 0
			&& shell->env[i][ft_strlen(name)] == '=')
		{
			free(shell->env[i]);
			j = i;
			while (shell->env[j + 1])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->env[j] = NULL;
			return ;
		}
		i++;
	}
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
