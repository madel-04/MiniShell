/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:06:10 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/19 20:06:10 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_shlvl(char **env)
{
	int		i;
	int		shlvl;
	char	*value;
	char	*new_value;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(env[i] + 6);
			shlvl++;
			value = ft_itoa(shlvl);
			new_value = ft_strjoin("SHLVL=", value);
			free(value);
			free(env[i]);
			env[i] = new_value;
			return ;
		}
		i++;
	}
	env[i] = ft_strdup("SHLVL=1");
	env[i + 1] = NULL;
}
