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

static int	cd_too_many_args(char **argv, t_shell *shell)
{
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	return (0);
}

static char	*cd_get_path(char **argv, t_shell *shell)
{
	char	*path;

	if (!argv[1] || argv[1][0] == '\0')
		return (get_env_value("HOME", shell->env));
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		path = get_env_value("OLDPWD", shell->env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			shell->last_exit_status = 1;
			return (NULL);
		}
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
		return (path);
	}
	else
		return (argv[1]);
}

/*static void	cd_update_pwd_on_error(char **argv, char *old_pwd, 
	t_shell *shell)
{
	char	*new_pwd;
	char	*pwd_env;
	size_t	len;
	int		need_slash;

	ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access \
		 parent directories: No such file or directory\n", 2);
	pwd_env = NULL;
	if (old_pwd)
		pwd_env = old_pwd;
	else
		pwd_env = get_env_value("PWD", shell->env);
	if (!pwd_env)
		pwd_env = "";
	if (argv[1] && argv[1][0] == '/')
		new_pwd = ft_strdup(argv[1]);
	else if (argv[1])
	{
		len = ft_strlen(pwd_env);
		need_slash = (len > 0 && pwd_env[len - 1] != '/' && argv[1][0] != '/');
		if (need_slash)
			new_pwd = ft_strjoin3(pwd_env, "/", argv[1]);
		else
			new_pwd = ft_strjoin(pwd_env, argv[1]);
	}
	else
		new_pwd = ft_strdup(pwd_env);
	set_env_var("PWD", new_pwd, shell);
	free(new_pwd);
}*/

static char	*cd_build_new_pwd(char **argv, char *pwd_env)
{
	char	*new_pwd;
	size_t	len;
	int		need_slash;

	if (argv[1] && argv[1][0] == '/')
		new_pwd = ft_strdup(argv[1]);
	else if (argv[1])
	{
		len = ft_strlen(pwd_env);
		need_slash = (len > 0 && pwd_env[len - 1] != '/' && argv[1][0] != '/');
		if (need_slash)
			new_pwd = ft_strjoin3(pwd_env, "/", argv[1]);
		else
			new_pwd = ft_strjoin(pwd_env, argv[1]);
	}
	else
		new_pwd = ft_strdup(pwd_env);
	return (new_pwd);
}

static void	cd_update_pwd_on_error(char **argv, char *old_pwd, t_shell *shell)
{
	char	*new_pwd;
	char	*pwd_env;

	ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent \
		 directories: No such file or directory\n", 2);
	pwd_env = NULL;
	if (old_pwd)
		pwd_env = old_pwd;
	else
		pwd_env = get_env_value("PWD", shell->env);
	if (!pwd_env)
		pwd_env = "";
	new_pwd = cd_build_new_pwd(argv, pwd_env);
	set_env_var("PWD", new_pwd, shell);
	free(new_pwd);
}

int	ft_cd(char **argv, t_shell *shell)
{
	char	*old_pwd;
	char	*path;
	char	cwd[PATH_MAX];

	old_pwd = get_env_value("PWD", shell->env);
	if (cd_too_many_args(argv, shell))
		return (1);
	path = cd_get_path(argv, shell);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		shell->last_exit_status = 1;
		return (1);
	}
	set_env_var("OLDPWD", old_pwd, shell);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var("PWD", cwd, shell);
	else
		cd_update_pwd_on_error(argv, old_pwd, shell);
	shell->last_exit_status = 0;
	return (0);
}
