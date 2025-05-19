/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:25:08 by mmendiol          #+#    #+#             */
/*   Updated: 2025/05/16 21:25:08 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	handle_heredoc(char *delimiter)
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
} */

int	open_file(t_redir *redir)
{
	int	fd;

	if (!redir->filename)
	{
		ft_putstr_fd("minishell: redirection error: missing filename\n", 2);
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
		print_file_error("Failed to open file: ", redir->filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_file_descriptors(t_redir *redir, int *in_fd, int *out_fd)
{
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == TOKEN_INPUT || curr->type == TOKEN_HEREDOC)
		{
			if (*in_fd != -1)
				close(*in_fd);
			*in_fd = open_file(curr);
		}
		else if (curr->type == TOKEN_OUTPUT
			|| curr->type == TOKEN_RED_OUTPUT_APPEND)
		{
			if (*out_fd != -1)
				close(*out_fd);
			*out_fd = open_file(curr);
		}
		curr = curr->next;
	}
}

void	apply_redirects(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(in_fd);
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
	if (out_fd != -1)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(out_fd);
			exit(EXIT_FAILURE);
		}
		close(out_fd);
	}
}

void	redirect_io(t_redir *redir)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	handle_file_descriptors(redir, &in_fd, &out_fd);
	apply_redirects(in_fd, out_fd);
}
