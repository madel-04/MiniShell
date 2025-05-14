/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:50:05 by marvin            #+#    #+#             */
/*   Updated: 2025/03/25 10:50:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		parse_input_token(input, &i, &tokens);
		if (!tokens)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}

void	parse_input_token(char *input, int *i, t_token **tokens)
{
	char	*word;
	char	op[3];
	t_token	*new_tok;

	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		ft_isline_or_triangle(i, input, op, tokens);
	}
	else
	{
		word = ft_get_word(input, i);
		if (!word)
		{
			free_tokens(*tokens);
			*tokens = NULL;
			return ;
		}
		new_tok = new_token(TOKEN_WORD, word);
		add_token(tokens, new_tok);
		free(word);
	}
}

void	ft_isline_or_triangle(int *i, char *input, char *op, t_token **tokens)
{
	int	type;

	type = TOKEN_WORD;
	op[0] = input[*i];
	op[1] = '\0';
	if ((input[*i] == '<' || input[*i] == '>') && input[(*i) + 1] == input[*i])
	{
		op[1] = input[*i];
		op[2] = '\0';
		(*i)++;
	}
	(*i)++;
	if (ft_strcmp(op, "|") == 0)
		type = TOKEN_PIPE;
	else if (ft_strcmp(op, "<") == 0)
		type = TOKEN_INPUT;
	else if (ft_strcmp(op, ">") == 0)
		type = TOKEN_OUTPUT;
	else if (ft_strcmp(op, "<<") == 0)
		type = TOKEN_HEREDOC;
	else if (ft_strcmp(op, ">>") == 0)
		type = TOKEN_RED_OUTPUT_APPEND;
	add_token(tokens, new_token(type, op));
}
