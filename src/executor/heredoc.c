/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:59:09 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/19 23:59:09 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds_on_sigint(int sig)
{
	int	fd;

	(void)sig;
	fd = 3;
	while (fd < 1024)
		close(fd++);
	exit(130);
}

int	handle_heredoc(char *delimiter)
{
	int					fd[2];
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	old_sa_int;
	struct sigaction	old_sa_quit;

	sa_int.sa_handler = close_fds_on_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, &old_sa_int);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, &old_sa_quit);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	heredoc_loop(fd[1], delimiter);
	sigaction(SIGINT, &old_sa_int, NULL);
	sigaction(SIGQUIT, &old_sa_quit, NULL);
	close(fd[1]);
	return (fd[0]);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (shell->last_exit_status = ft_echo(cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (shell->last_exit_status = ft_cd(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (shell->last_exit_status = ft_pwd(shell));
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (shell->last_exit_status = ft_export(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (shell->last_exit_status = ft_unset(cmd->argv, shell));
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (shell->last_exit_status = ft_env(shell));
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd->argv, shell);
	return (0);
}
