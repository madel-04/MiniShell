#include "minishell.h"



static char	*ft_get_word(char *input, int *i)
{
	int		start;
	int		len;
	char	*word;
	char	mark; // ? INIT

	start = 0;
	len = 0;
	if (input[*i] == '\'' || input[*i] == '"') // & OTRA FUNCIÓN
	{
		mark = input[*i];
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != mark)
		{
			(*i)++;
			len++;
		}
		if (input[*i] != mark)
		{
			fprintf(stderr, "ERROR: Comillas cerradas no encontradas\n");
			return NULL;
		}
		(*i)++; // * Saltarse la comilla que cierra
	} // & HASTA AQUÍ ??
	else
	{
		start = *i;
		while (input[*i] && !isspace(input[*i]) && input[*i] != '|' &&
               input[*i] != '<' && input[*i] != '>') // & FUNCION PARA VER SI SON | > o <
			   {
				(*i)++;
				len++;
			   }
	}
	word = ft_strndup(&input[start], len); // TODO LIBFT
	return (word);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;
	char	op[3];
	t_type	type; // ? Hace falta inicializarla??
	char	*word;

	tokens = NULL;
	i = 0;
	while(input[i])
	{
		while(input[i] && isspace(input[i])) // TODO LIBFT
			i++;
		if (!input[i])
			break;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>') // &NUEVA FUNCION
		{
			op[0] = input[i];
			op[1] = '\0';
			if ((input[i] == '<' || input[i] == '>') && input[i+1] == input[i])
			{
				op[1] = input[i+1];
				op[2] = '\0';
				i += 2;
			}
			else
				i++;
			if (ft_strcmp(op, "|") == 0)
				type = TOKEN_PIPE;
			if (ft_strcmp(op, "<") == 0)
				type = TOKEN_INPUT;
			if (ft_strcmp(op, ">") == 0)
				type = TOKEN_OUTPUT;
			if (ft_strcmp(op, "<<") == 0)
				type = TOKEN_HEREDOC;
			if (ft_strcmp(op, ">>") == 0)
				type = TOKEN_RED_OUTPUT_APPEND; // &NUEVA FUNCION
		}
		else
		{
			word = ft_get_word(input, &i); // TODO
			if (!word)
			{
				free_tokens(tokens); //TODO
				return NULL;
			}
			add_token(&tokens, new_token(TOKEN_WORD, word)); // TODO
			free(word);
		}
	}
	return (tokens);
}
