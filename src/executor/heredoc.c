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
	struct sigaction	sa;
	struct sigaction	old_sa;

	sa.sa_handler = close_fds_on_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &old_sa);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	heredoc_loop(fd[1], delimiter);
	sigaction(SIGINT, &old_sa, NULL);
	close(fd[1]);
	return (fd[0]);
}
