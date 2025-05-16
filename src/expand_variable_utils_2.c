/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:36:47 by marvin            #+#    #+#             */
/*   Updated: 2025/04/07 13:36:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_escaped(t_exp *exp)
{
	return (exp->i > 0 && exp->token[exp->i - 1] == '\\');
}

static void	handle_special_case(t_exp *exp, t_shell *shell)
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
/*
void	handle_variable(t_exp *exp, t_shell *shell)
{
	char	var_name[256];

	exp->i++;
	if (is_escaped(exp))
	{
		append_char(exp, '$');
		return ;
	}
	if (!exp->token[exp->i] || !(ft_isalnum(exp->token[exp->i])
			|| exp->token[exp->i] == '_'))
	{
		append_char(exp, '$');
		return ;
	}
	if (exp->token[exp->i] == '?')
	{
		handle_special_case(exp, shell);
		return ;
	}
	read_variable_name(exp, var_name);
	append_variable_value(exp, shell, var_name);
}
*/
void	handle_variable(t_exp *exp, t_shell *shell)
{
    char	var_name[256];

    exp->i++;
    if (is_escaped(exp))
    {
        append_char(exp, '$');
        return ;
    }
    if (!exp->token[exp->i])
    {
        append_char(exp, '$');
        return ;
    }
    if (exp->token[exp->i] == '?')
    {
        handle_special_case(exp, shell);
        return ;
    }
    if (ft_isdigit(exp->token[exp->i]))
    {
        exp->i++;
        return ;
    }
    if (!(ft_isalpha(exp->token[exp->i]) || exp->token[exp->i] == '_'))
    {
        append_char(exp, '$');
        return ;
    }
    read_variable_name(exp, var_name);
    append_variable_value(exp, shell, var_name);
}
