/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proces_x.c     		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:19:50 by marvin            #+#    #+#             */
/*   Updated: 2025/03/25 11:19:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipe(t_parse *p)
{
	if (p->current_cmd && p->argv)
		p->current_cmd->argv = p->argv;
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
		fprintf(stderr, "syntax error: redirection without filename\n");
		free_tokens(p->token);
		free_cmds(p->cmd_head);
		p->cmd_head = NULL;
		return (0);
	}
	if (p->token->next->type != TOKEN_WORD)
	{
		fprintf(stderr, "syntax error: redirection without filename\n");
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
	temp_argv = ft_realloc(p->argv, sizeof(char *) * (p->argc + 2));
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
