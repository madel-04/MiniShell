#include "minishell.h"

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;
	char	op[3];

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && isspace(input[i]))
			i++;
		if (!input[i])
			break;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			op[0] = input[i];
			op[1] = '\0';
			if 
		}
	}
}