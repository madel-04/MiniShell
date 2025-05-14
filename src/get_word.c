/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:55:28 by marvin            #+#    #+#             */
/*   Updated: 2025/04/07 13:55:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quotes(char *input, int *i, char **word)
{
	int	success;

	success = handle_quotes(input, i, word);
	if (!success)
	{
		free(*word);
		return (0);
	}
	return (1);
}

static int	handle_backslash(char *input, int *i, char **word)
{
	char	*temp;

	(*i)++;
	if (input[*i] == '\0')
	{
		temp = ft_strndup("\\", 1);
		*word = ft_strjoin_free(*word, temp);
		free(temp);
		return (0);
	}
	temp = ft_strndup(&input[*i - 1], 2);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i)++;
	return (1);
}

static void	append_normal_char(char *input, int *i, char **word)
{
	char	*temp;

	temp = ft_strndup(&input[*i], 1);
	*word = ft_strjoin_free(*word, temp);
	free(temp);
	(*i)++;
}

char	*ft_get_word(char *input, int *i)
{
	char	*word;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\\')
		{
			if (!handle_backslash(input, i, &word))
				break ;
		}
		else if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!process_quotes(input, i, &word))
				return (NULL);
		}
		else
			append_normal_char(input, i, &word);
	}
	return (word);
}
