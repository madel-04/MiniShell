/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:56:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/13 12:56:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_tokens(t_token *tokens, t_shell *shell)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
		return (handle_unexpected_pipe(shell));
	return (validate_token_sequence(tokens, shell));
}

int	validate_token_sequence(t_token *tokens, t_shell *shell)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_PIPE)
		{
			if (!validate_pipe(cur, tokens, shell))
				return (0);
		}
		else if (cur->type >= TOKEN_INPUT && cur->type
			<= TOKEN_RED_OUTPUT_APPEND)
		{
			if (!validate_redirection(cur, shell))
			{
				shell->last_exit_status = 2;
				return (0);
			}
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (1);
}

int	handle_unexpected_pipe(t_shell *shell)
{
	printf(" syntax error near unexpected token `|'\n");
	shell->last_exit_status = 2;
	return (0);
}

int	validate_pipe(t_token *cur, t_token *tokens, t_shell *shell)
{
	(void)tokens;
	if (!cur->next)
	{
		printf("syntax error: pipe at end of command\n");
		shell->last_exit_status = 2;
		return (0);
	}
	if (cur->next->type == TOKEN_PIPE)
	{
		printf("syntax error: consecutive pipes\n");
		shell->last_exit_status = 2;
		return (0);
	}
	return (1);
}

int	validate_redirection(t_token *cur, t_shell *shell)
{
	(void)shell;
	if (!cur->next || cur->next->type != TOKEN_WORD)
	{
		if (cur->next)
			printf(" syntax error near unexpected token `%s'\n",
				cur->next->value);
		else
			printf(" syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}
