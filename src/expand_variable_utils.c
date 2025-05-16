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

void	heredoc_loop(int fd_write, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

void	handle_special_case(t_exp *exp, t_shell *shell)
{
	char	*var_value;

	if (exp->token[exp->i] == '?')
	{
		var_value = ft_itoa(shell->last_exit_status);
		append_str(exp, var_value);
		free(var_value);
		exp->i++;
	}
}
