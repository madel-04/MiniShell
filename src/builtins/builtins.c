/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:23:51 by mmendiol          #+#    #+#             */
/*   Updated: 2025/05/16 21:23:51 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_n_flag(char **argv, int *i)
{
	int	j;
	int	nl_flag;

	nl_flag = 0;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 2;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] == '\0')
		{
			nl_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	return (nl_flag);
}

void	ft_echo(char **argv)
{
	int	nl_flag;
	int	i;

	i = 1;
	nl_flag = parse_n_flag(argv, &i);
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

void	ft_env(t_shell *shell)
{
	print_env(shell->env);
}
