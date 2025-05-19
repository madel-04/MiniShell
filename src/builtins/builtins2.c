/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:34 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/17 13:54:34 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str, char *eq_sign)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && (eq_sign == NULL || &str[i] < eq_sign))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_invalid_identifier(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->last_exit_status = 1;
}

static void	handle_valid_identifier(char *arg, char *eq_sign, t_shell *shell)
{
	*eq_sign = '\0';
	set_env_var(arg, eq_sign + 1, shell);
	*eq_sign = '=';
}

static int	process_export_arg(char *arg, t_shell *shell)
{
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	if (!is_valid_identifier(arg, eq_sign))
	{
		handle_invalid_identifier(arg, shell);
		return (1);
	}
	else if (eq_sign)
		handle_valid_identifier(arg, eq_sign, shell);
	else
	{
		if (!get_env_value(arg, shell->env))
			set_env_var(arg, NULL, shell);
	}
	return (0);
}

int	ft_export(char **argv, t_shell *shell)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!argv[1])
	{
		print_env_sorted(shell->env);
		return (0);
	}
	while (argv[i])
	{
		if (process_export_arg(argv[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
