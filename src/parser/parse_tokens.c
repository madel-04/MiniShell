/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:55:21 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/17 13:55:21 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd(t_parse *p)
{
	t_cmd	*temp;

	temp = NULL;
	p->current_cmd = malloc(sizeof(t_cmd));
	if (!p->current_cmd)
		return (free_tokens(p->token), free_cmds(p->cmd_head), 0);
	p->current_cmd->redir = NULL;
	p->current_cmd->argv = NULL;
	p->current_cmd->next = NULL;
	if (!p->cmd_head)
		p->cmd_head = p->current_cmd;
	else
	{
		temp = p->cmd_head;
		while (temp->next)
			temp = temp->next;
		temp->next = p->current_cmd;
	}
	p->argv = malloc(sizeof(char *));
	if (!p->argv)
		return (free_tokens(p->token), free_cmds(p->cmd_head), 0);
	p->argc = 0;
	return (1);
}

static void	loop_parse_tokens(t_parse *p)
{
	while (p->token)
	{
		if (p->token->type == TOKEN_PIPE)
		{
			process_pipe(p);
			continue ;
		}
		else if (p->token->type >= TOKEN_INPUT && p->token->type
			<= TOKEN_RED_OUTPUT_APPEND)
		{
			if (!process_redir(p))
				return ;
		}
		else
		{
			if (p->current_cmd == NULL)
			{
				if (!init_cmd(p))
					return ;
			}
			if (p->token->type == TOKEN_WORD)
				process_word(p);
			p->token = p->token->next;
		}
	}
}

t_cmd	*parse_tokens(t_token **tokens, t_shell *shell)
{
	t_parse	p;

	p.cmd_head = NULL;
	p.current_cmd = NULL;
	p.token = *tokens;
	p.argv = NULL;
	p.argc = 0;
	p.shell = shell;
	if (!validate_tokens(p.token, shell))
	{
		*tokens = NULL;
		return (NULL);
	}
	loop_parse_tokens(&p);
	if (p.current_cmd && p.argv)
		p.current_cmd->argv = p.argv;
	return (p.cmd_head);
}

void	ft_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_env_var(argv[i], shell);
		i++;
	}
}

char	**env_to_array(char **env)
{
	return (env);
}
