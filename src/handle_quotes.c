/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:18:21 by marvin            #+#    #+#             */
/*   Updated: 2025/04/07 16:18:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_char2(char *input, int *i, char **word)
{
	char	*temp;

	temp = ft_strndup(&input[*i], 1);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i)++;
}

static void	process_escaped_double_quote(char *input, int *i, char **word)
{
	char	*temp;

	temp = ft_strndup(&input[*i], 2);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i) += 2;
}

static int	close_quote(char *input, int *i, char **word)
{
	char	*temp;

	temp = ft_strndup(&input[*i], 1);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i)++;
	return (1);
}

int	handle_quotes(char *input, int *i, char **word)
{
	char	quote;
	char	*temp;

	quote = input[*i];
	temp = ft_strndup(&input[*i], 1);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i)++;
	while (input[*i])
	{
		if (quote == '\'' && input[*i] != quote)
			append_char2(input, i, word);
		else if (quote == '"' && input[*i] == '\\'
			&& (input[*i + 1] == '"' || input[*i + 1] == '$'
				|| input[*i + 1] == '`' || input[*i + 1] == '\\'))
			process_escaped_double_quote(input, i, word);
		else if (quote == '"' && input[*i] == '\\')
			append_char2(input, i, word);
		else if (input[*i] == quote)
			return (close_quote(input, i, word));
		else
			append_char2(input, i, word);
	}
	fprintf(stderr, "syntax error: unclosed quote\n");
	return (0);
}
