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

int	execute_cmd(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (1);
	if (cmds->next == NULL && execute_builtin(cmds, shell))
		return (shell->last_exit_status);
	handle_pipes(cmds, shell);
	return (shell->last_exit_status);
}
