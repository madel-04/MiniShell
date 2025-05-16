/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:50:17 by marvin            #+#    #+#             */
/*   Updated: 2025/03/27 11:50:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(int fd_write, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

static int	handle_heredoc(char *delimiter)
{
	int					fd[2];
	struct sigaction	sa;
	struct sigaction	old_sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	ft_sigemptyset(&sa.sa_mask);
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

static int	open_file(t_redir *redir)
{
	int	fd;

	if (!redir->filename)
	{
		fprintf(stderr, "minishell: redirection error: missing filename\n");
		exit(EXIT_FAILURE);
	}
	if (redir->type == TOKEN_INPUT)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == TOKEN_OUTPUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_RED_OUTPUT_APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TOKEN_HEREDOC)
		fd = handle_heredoc(redir->filename);
	else
		fd = -1;
	if (fd == -1)
	{
		perror("minishell");
		fprintf(stderr, "Failed to open file: %s\n", redir->filename);//!
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	dup_io(int fd, t_redir *redir)
{
	if (redir->type == TOKEN_INPUT || redir->type == TOKEN_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			exit(EXIT_FAILURE);
		}
	}
}

void	redirect_io(t_redir *redir)
{
	int	fd;

	printf("%d\n", redir->type);
	printf("%s\n", redir->filename);

	while (redir)
	{
		fd = open_file(redir);
		dup_io(fd, redir);
		close(fd);
		redir = redir->next;
	}
}
