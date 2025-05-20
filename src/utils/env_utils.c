/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:24:08 by mmendiol          #+#    #+#             */
/*   Updated: 2025/05/16 21:24:08 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *name, char **env)
{
	int	i;
	int	len;

	if (!name || !env)
		return (NULL);
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

/* void	set_env_var(const char *name, const char *value, t_shell *shell)
{
	int		i;
	char	*new_var;
	int		old_size;

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
	old_size = 0;
	while (shell->env[old_size])
		old_size++;
	shell->env = ft_realloc(shell->env, (old_size + 1) *
	sizeof(char *), (old_size + 2) * sizeof(char *));
	shell->env[i] = new_var;
	shell->env[i + 1] = NULL;
} */

static void	update_env_var(const char *name, char *new_var, t_shell *shell)
{
	int	i;
	int	old_size;

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
	old_size = 0;
	while (shell->env[old_size])
		old_size++;
	shell->env = ft_realloc(shell->env, (old_size + 1) * sizeof(char *),
			(old_size + 2) * sizeof(char *));
	shell->env[old_size] = new_var;
	shell->env[old_size + 1] = NULL;
}

void	set_env_var(const char *name, const char *value, t_shell *shell)
{
	char	*new_var;

	if (value)
		new_var = ft_strjoin3(name, "=", value);
	else
		new_var = ft_strdup(name);
	update_env_var(name, new_var, shell);
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
