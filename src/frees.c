/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:06:50 by marvin            #+#    #+#             */
/*   Updated: 2025/02/19 11:06:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;
	int		i;

	while (cmds)
	{
		temp_cmd = cmds;
		cmds = cmds->next;
		if (temp_cmd->argv)
		{
			i = 0;
			while (temp_cmd->argv[i])
				free(temp_cmd->argv[i++]);
			free(temp_cmd->argv);
		}
		while (temp_cmd->redir)
		{
			temp_redir = temp_cmd->redir;
			temp_cmd->redir = temp_cmd->redir->next;
			free(temp_redir->filename);
			free(temp_redir);
		}
		free(temp_cmd);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens;
		free(temp->value);
		free(temp);
		tokens = tokens->next;
	}
}
