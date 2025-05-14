/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:50:46 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 11:50:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	nl_flag;
	int	i;

	nl_flag = 0;
	i = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		nl_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!nl_flag)
		ft_putstr_fd("\n", 1);
}

void	ft_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return ;
	}
	if (!argv[1])
		path = get_env_value("HOME", shell->env);
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		shell->last_exit_status = 1;
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	set_env_var("OLDPWD", get_env_value("PWD", shell->env), shell);
	set_env_var("PWD", cwd, shell);
	shell->last_exit_status = 0;
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
}

void	ft_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_env_var(argv[i], shell);
		i++;
	}
}

void	ft_env(t_shell *shell)
{
	print_env(shell->env);
}
