/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:49:36 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 11:49:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_unused_pipes(int *prev_pipe_in, int fd[2], t_cmd *current)
{
	if (*prev_pipe_in != -1)
		close(*prev_pipe_in);
	if (current->next)
	{
		close(fd[1]);
		*prev_pipe_in = fd[0];
	}
}

static void	wait_for_children(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
	}
}

static void	setup_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

static void	handle_pipes(t_cmd *cmds, t_shell *shell)
{
	int		fd[2];
	int		prev_pipe_in;
	t_cmd	*current;

	prev_pipe_in = -1;
	current = cmds;
	while (current)
	{
		if (current->next)
			setup_pipe(fd);
		create_child_process(prev_pipe_in, fd, current, shell);
		close_unused_pipes(&prev_pipe_in, fd, current);
		current = current->next;
	}
	wait_for_children(shell);
}
/*
int	execute_cmd(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (1);
	if (cmds->next == NULL && execute_builtin(cmds, shell))
	{
		if (cmds->redir)
			redirect_io(cmds->redir);
		return (shell->last_exit_status);
	}
	handle_pipes(cmds, shell);
	return (shell->last_exit_status);
}
*/
/*
int	execute_cmd(t_cmd *cmds, t_shell *shell)
{
    int saved_stdin;
	int saved_stdout;

    if (!cmds)
        return (1);
    if (cmds->next == NULL && execute_builtin(cmds, shell))
    {
        if (cmds->redir)
        {
            saved_stdin = dup(STDIN_FILENO);
            saved_stdout = dup(STDOUT_FILENO);
            redirect_io(cmds->redir);
            execute_builtin(cmds, shell); // Solo una vez aquí
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
        }
        else
            execute_builtin(cmds, shell);
        return (shell->last_exit_status);
    }
    handle_pipes(cmds, shell);
    return (shell->last_exit_status);
}
	! ejecuta el builtin dos veces si hay redirección
*/
int	is_builtin_cmd(t_cmd *cmd)
{
    if (!cmd->argv || !cmd->argv[0])
        return (0);
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (1);
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (1);
    return (0);
}

int	execute_cmd(t_cmd *cmds, t_shell *shell)
{
    int saved_stdin, saved_stdout;
    int is_builtin;

    if (!cmds)
        return (1);

    is_builtin = is_builtin_cmd(cmds);
    if (cmds->next == NULL && is_builtin)
    {
        if (cmds->redir)
        {
            saved_stdin = dup(STDIN_FILENO);
            saved_stdout = dup(STDOUT_FILENO);
            redirect_io(cmds->redir);
            execute_builtin(cmds, shell);
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
        }
        else
            execute_builtin(cmds, shell);
        return (shell->last_exit_status);
    }
    handle_pipes(cmds, shell);
    return (shell->last_exit_status);
}
