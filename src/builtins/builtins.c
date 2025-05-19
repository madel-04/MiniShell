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

int	ft_echo(char **argv)
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
	return (0);
}

/*int	ft_cd(char **argv, t_shell *shell)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	if (!argv[1])
		path = get_env_value("HOME", shell->env);
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		perror("cd");
		shell->last_exit_status = 1;
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	set_env_var("OLDPWD", get_env_value("PWD", shell->env), shell);
	set_env_var("PWD", cwd, shell);
	shell->last_exit_status = 0;
	return (0);
}*/

int ft_cd(char **argv, t_shell *shell)
{
	char *old_pwd;
	char *path;
	char *new_pwd;
	char cwd[PATH_MAX];

	old_pwd = get_env_value("PWD", shell->env);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	if (!argv[1] || argv[1][0] == '\0')
		path = get_env_value("HOME", shell->env);
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		shell->last_exit_status = 1;
		return (1);
	}
	set_env_var("OLDPWD", old_pwd, shell);
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_var("PWD", cwd, shell);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		char *pwd_env = old_pwd ? old_pwd : get_env_value("PWD", shell->env);
		if (!pwd_env)
			pwd_env = "";
		if (argv[1] && argv[1][0] == '/')
			new_pwd = ft_strdup(argv[1]);
		else if (argv[1])
		{
			size_t len = ft_strlen(pwd_env);
			int need_slash = (len > 0 && pwd_env[len - 1] != '/' && argv[1][0] != '/');
			if (need_slash)
				new_pwd = ft_strjoin3(pwd_env, "/", argv[1]);
			else
				new_pwd = ft_strjoin(pwd_env, argv[1]);
		}
		else
			new_pwd = ft_strdup(pwd_env);
		set_env_var("PWD", new_pwd, shell);
		free(new_pwd);
	}

	shell->last_exit_status = 0;
	return (0);
}

int ft_pwd(t_shell *shell)
{
	char *pwd = get_env_value("PWD", shell->env);

	if (pwd && *pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	{
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)))
		{
			ft_putstr_fd(cwd, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
		perror("pwd");
		return (1);
	}
}

int	ft_env(t_shell *shell)
{
	print_env(shell->env);
	return (0);
}
