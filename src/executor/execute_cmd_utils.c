/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:24:17 by mmendiol          #+#    #+#             */
/*   Updated: 2025/05/16 21:24:17 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->argv), 1);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd->argv, shell), 1);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd->argv, shell), 1);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd->argv, shell), 1);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(shell), 1);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_exit(cmd->argv, shell);
	return (0);
}*/

static void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**env_arr;

	path = get_cmd_path(cmd->argv[0], shell->env);
	env_arr = env_to_array(shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		free_array(env_arr);
		exit(127);
	}
	execve(path, cmd->argv, env_arr);
	perror("execve");
	free(path);
	free_array(env_arr);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}
/*
static void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	redirect_io(cmd->redir);
	if (execute_builtin(cmd, shell))
		exit(shell->last_exit_status);
	else
		execute_external(cmd, shell);
}
*/

static void	execute_single_cmd(t_cmd *cmd, t_shell *shell)
{
	redirect_io(cmd->redir);
	if (!cmd->argv || !cmd->argv[0])
	{
		exit(0);
	}
	if (is_builtin_cmd(cmd))
		exit(execute_builtin(cmd, shell));
	else
		execute_external(cmd, shell);
}

/* static void	setup_child_process(int prev_pipe_in, int fd[2],
				t_cmd *current, t_shell *shell)
{
	if (prev_pipe_in != -1)
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
	if (current->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	execute_single_cmd(current, shell);
	exit(shell->last_exit_status);
} */

/* static void	setup_child_process(int prev_pipe_in, int fd[2], t_cmd *current,
		t_shell *shell)
{
	int		has_output_redir;
	t_redir	*redir;

	if (prev_pipe_in != -1)
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
	has_output_redir = 0;
	redir = current->redir;
	while (redir)
	{
		if (redir->type == TOKEN_OUTPUT
			|| redir->type == TOKEN_RED_OUTPUT_APPEND)
		{
			has_output_redir = 1;
			break ;
		}
		redir = redir->next;
	}
	if (current->next && !has_output_redir)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	execute_single_cmd(current, shell);
	exit(shell->last_exit_status);
} */

static int	has_output_redirection(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_OUTPUT
			|| redir->type == TOKEN_RED_OUTPUT_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static void	setup_child_process(int prev_pipe_in, int fd[2],
		t_cmd *current, t_shell *shell)
{
	if (prev_pipe_in != -1)
	{
		dup2(prev_pipe_in, STDIN_FILENO);
		close(prev_pipe_in);
	}
	if (current->next && !has_output_redirection(current->redir))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	execute_single_cmd(current, shell);
	exit(shell->last_exit_status);
}

pid_t	create_child_process(int prev_pipe_in, int fd[2],
				t_cmd *current, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_child_process(prev_pipe_in, fd, current, shell);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (pid);
}
