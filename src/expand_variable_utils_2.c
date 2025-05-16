/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:24:42 by mmendiol          #+#    #+#             */
/*   Updated: 2025/05/16 21:24:42 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_escaped(t_exp *exp)
{
	return (exp->i > 0 && exp->token[exp->i - 1] == '\\');
}

static void	read_variable_name(t_exp *exp, char *var_name)
{
	int	i;

	i = 0;
	while (exp->token[exp->i] && (ft_isalnum(exp->token[exp->i])
			|| exp->token[exp->i] == '_'))
	{
		var_name[i++] = exp->token[exp->i];
		exp->i++;
	}
	var_name[i] = '\0';
}

static void	append_variable_value(t_exp *exp, t_shell *shell,
		const char *var_name)
{
	char	*var_value;

	var_value = get_env_value(var_name, shell->env);
	if (var_value)
		append_str(exp, var_value);
}

int	handle_edge_cases(t_exp *exp, t_shell *shell)
{
	if (is_escaped(exp) || !exp->token[exp->i])
	{
		append_char(exp, '$');
		return (1);
	}
	if (exp->token[exp->i] == '?')
	{
		handle_special_case(exp, shell);
		return (1);
	}
	if (ft_isdigit(exp->token[exp->i]))
	{
		exp->i++;
		return (1);
	}
	if (!(ft_isalpha(exp->token[exp->i]) || exp->token[exp->i] == '_'))
	{
		append_char(exp, '$');
		return (1);
	}
	return (0);
}

void	handle_variable(t_exp *exp, t_shell *shell)
{
	char	var_name[256];

	exp->i++;
	if (handle_edge_cases(exp, shell))
		return ;
	read_variable_name(exp, var_name);
	append_variable_value(exp, shell, var_name);
}
