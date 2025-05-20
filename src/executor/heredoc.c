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
