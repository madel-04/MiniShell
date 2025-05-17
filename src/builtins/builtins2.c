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

static int	is_valid_identifier(const char *str, char *eq_sign)
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

void	ft_export(char **argv, t_shell *shell)
{
	int		i;
	char	*eq_sign;

	i = 1;
	if (!argv[1])
	{
		print_env_sorted(shell->env);
		return ;
	}
	while (argv[i])
	{
		eq_sign = ft_strchr(argv[i], '=');
		if (!is_valid_identifier(argv[i], eq_sign))
			handle_invalid_identifier(argv[i], shell);
		else if (eq_sign)
			handle_valid_identifier(argv[i], eq_sign, shell);
		else
		{
			if (!get_env_value(argv[i], shell->env))
				set_env_var(argv[i], NULL, shell);
		}
		i++;
	}
}

void	ft_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	if (argv[1] && !argv[2])
	{
		if (!ft_isdigit_str(argv[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		exit_code = ft_atoi(argv[1]);
		exit_code %= 256;
		exit(exit_code);
	}
	exit(shell->last_exit_status);
}
