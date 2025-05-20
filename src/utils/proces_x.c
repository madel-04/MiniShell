/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:55:26 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/17 13:55:26 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	process_pipe(t_parse *p)
{
	if (p->current_cmd && p->argv)
		p->current_cmd->argv = p->argv;
	p->current_cmd = NULL;
	p->token = p->token->next;
}  */
void	process_pipe(t_parse *p)
{
	int argc = 0, i = 0;

	if (p->current_cmd)
	{
		if (p->argv)
		{
			while (p->argv[argc])
				argc++;
			p->current_cmd->argv = malloc(sizeof(char *) * (argc + 1));
			if (!p->current_cmd->argv)
				exit(1);
			for (i = 0; i < argc; i++)
				p->current_cmd->argv[i] = ft_strdup(p->argv[i]);
			p->current_cmd->argv[argc] = NULL;
			for (i = 0; i < argc; i++)
				free(p->argv[i]);
			free(p->argv);
			p->argv = NULL;
		}
		else
		{
			p->current_cmd->argv = malloc(sizeof(char *));
			if (!p->current_cmd->argv)
				exit(1);
			p->current_cmd->argv[0] = NULL;
		}
	}
	p->current_cmd = NULL;
	p->token = p->token->next;
}

int	process_redir(t_parse *p)
{
	if (!validate_redirection_token(p))
		return (0);
	return (add_redirection(p));
}

int	validate_redirection_token(t_parse *p)
{
	if (p->token->next == NULL)
	{
		ft_putstr_fd("syntax error: redirection without filename\n", 2);
		free_tokens(p->token);
		free_cmds(p->cmd_head);
		p->cmd_head = NULL;
		return (0);
	}
	if (p->token->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("syntax error: redirection without filename\n", 2);
		free_tokens(p->token);
		free_cmds(p->cmd_head);
		p->cmd_head = NULL;
		return (0);
	}
	return (1);
}

int	process_word(t_parse *p)
{
	char	*expanded;
	char	**temp_argv;

	expanded = expand_variable(p->token->value, p->shell->last_exit_status,
			p->shell);
	if (!expanded)
		return (free(p->argv), free_tokens(p->token), free_cmds(p->cmd_head),
			0);
	temp_argv = ft_realloc(p->argv,
			sizeof(char *) * (p->argc + 1), sizeof(char *) * (p->argc + 2));
	if (!temp_argv)
	{
		free(expanded);
		return (free(p->argv), free_tokens(p->token), free_cmds(p->cmd_head),
			0);
	}
	p->argv = temp_argv;
	p->argv[p->argc] = expanded;
	p->argc++;
	p->argv[p->argc] = NULL;
	return (1);
}

/* void	close_unused_pipes(int *prev_pipe_in, int fd[2], t_cmd *current)
{
	if (*prev_pipe_in != -1)
		close(*prev_pipe_in);
	if (current->next)
	{
		close(fd[1]);
		*prev_pipe_in = fd[0];
	}
} */
//// filepath: src/utils/proces_x.c
// ...existing code...
void	close_unused_pipes(int *prev_pipe_in, int fd[2], t_cmd *current)
{
    if (*prev_pipe_in != -1)
    {
        close(*prev_pipe_in);
        *prev_pipe_in = -1;
    }
    if (current->next)
    {
        close(fd[1]);
        *prev_pipe_in = fd[0];
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
    }
}
// ...existing code...