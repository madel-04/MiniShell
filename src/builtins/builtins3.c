/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:49:38 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/19 17:49:38 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv, t_shell *shell)
{
	int	exit_code;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
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
