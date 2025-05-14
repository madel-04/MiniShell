/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:23:28 by marvin            #+#    #+#             */
/*   Updated: 2025/03/24 13:23:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Agrega un solo carácter al buffer.
void	append_char(t_exp *exp, char c)
{
	if (exp->res_index + 1 >= exp->buff_size)
	{
		exp->buff_size *= 2;
		exp->result = ft_realloc(exp->result, exp->buff_size);
	}
	exp->result[exp->res_index] = c;
	exp->res_index++;
	exp->result[exp->res_index] = '\0';
}

// Agrega una cadena al buffer.
void	append_str(t_exp *exp, const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (exp->res_index + len + 1 > exp->buff_size)
	{
		exp->buff_size *= 2;
		exp->result = ft_realloc(exp->result, exp->buff_size);
	}
	ft_strcpy(exp->result + exp->res_index, str);
	exp->res_index += len;
}

void	handle_exit_status(t_exp *exp)
{
	char	*status_str;

	status_str = ft_itoa(exp->last_exit_status);
	append_str(exp, status_str);
	free(status_str);
	exp->i += 2;
}
/*
void	print_shell_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
	{
		printf("shell->env is not initialized.\n");
		return ;
	}
	if (!shell->env)
	{
		printf("shell->env is NULL.\n");
		return ;
	}
	printf("Environment variables:\n");
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
}
*/
