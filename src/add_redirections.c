/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:22:33 by marvin            #+#    #+#             */
/*   Updated: 2025/04/07 16:22:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_redir_fields(t_redir *new_redir, t_parse *p)
{
	char	*expanded_filename;

	expanded_filename = expand_variable(p->token->next->value,
			p->shell->last_exit_status, p->shell);
	if (!expanded_filename)
	{
		free(new_redir);
		return (0);
	}
	new_redir->type = p->token->type;
	new_redir->filename = expanded_filename;
	new_redir->next = NULL;
	return (1);
}

static void	append_redirection(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*last;

	if (cmd->redir == NULL)
		cmd->redir = new_redir;
	else
	{
		last = cmd->redir;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

int	add_redirection(t_parse *p)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	if (!init_redir_fields(new_redir, p))
		return (0);
	append_redirection(p->current_cmd, new_redir);
	p->token = p->token->next->next;
	return (1);
}
