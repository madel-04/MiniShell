/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:21:00 by madel-va          #+#    #+#             */
/*   Updated: 2025/04/07 17:21:00 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struct_(t_exp *exp, char *token, int last_exit_status)
{
	exp->token = token;
	exp->i = 0;
	exp->result = malloc(1024);
	if (!exp->result)
		return ;
	exp->res_index = 0;
	exp->buff_size = 1024;
	exp->in_single = 0;
	exp->in_double = 0;
	exp->last_exit_status = last_exit_status;
}

static int	handle_backslash(t_exp *exp)
{
	exp->i++;
	if (exp->token[exp->i] == '\0')
	{
		append_char(exp, '\\');
		return (1);
	}
	if (exp->in_single)
	{
		append_char(exp, '\\');
		append_char(exp, exp->token[exp->i]);
		exp->i++;
	}
	else if (exp->in_double && exp->token[exp->i] == '\'')
	{
		append_char(exp, '\\');
		append_char(exp, exp->token[exp->i]);
		exp->i++;
	}
	else
	{
		append_char(exp, exp->token[exp->i]);
		exp->i++;
	}
	return (0);
}

static void	in_double_or_single(int x, t_exp *exp)
{
	if (x == 1)
	{
		exp->in_double = !exp->in_double;
		exp->i++;
	}
	else if (x == 2)
	{
		exp->in_single = !exp->in_single;
		exp->i++;
	}
}

static void	is_a_dollar(t_exp *exp, t_shell *shell)
{
	if (exp->token[exp->i] == '$' && !exp->in_single)
	{
		if ((exp->i > 0 && exp->token[exp->i - 1] == '\\')
			|| exp->token[exp->i + 1] == '\\')
		{
			append_char(exp, '$');
			exp->i++;
		}
		else if (exp->token[exp->i + 1] == '?')
			handle_exit_status(exp);
		else
			handle_variable(exp, shell);
	}
}

char	*expand_variable(char *token, int last_exit_status, t_shell *shell)
{
	t_exp	exp;

	init_struct_(&exp, token, last_exit_status);
	while (exp.token[exp.i])
	{
		if (exp.token[exp.i] == '\\')
		{
			if (handle_backslash(&exp))
				break ;
		}
		else if (exp.token[exp.i] == '\'' && !exp.in_double)
			in_double_or_single(2, &exp);
		else if (exp.token[exp.i] == '\"' && !exp.in_single)
			in_double_or_single(1, &exp);
		else if (exp.token[exp.i] == '$' && !exp.in_single)
			is_a_dollar(&exp, shell);
		else
		{
			append_char(&exp, exp.token[exp.i]);
			exp.i++;
		}
	}
	exp.result[exp.res_index] = '\0';
	return (exp.result);
}
