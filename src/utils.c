/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:17:15 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 10:17:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r'
		|| c == '\f' || c == '\v' )
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
/*
void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token Type: %d, Token Value: %s, Quote type: %d\n",
			current->type, current->value, current->quote_type);
		current = current->next;
	}
}

// Función para imprimir la estructura t_cmd
void	print_cmd(t_cmd *cmd)
{
	int			i;
	t_redir		*redir;
	
	while (cmd)
	{
		printf("Command:\n");
		if (cmd->argv)
		{
			printf("Arguments:\n");
			for (i = 0; cmd->argv[i]; i++)
				printf("  argv[%d]: %s\n", i, cmd->argv[i]);
			}
			if (cmd->redir)
			{
			printf("Redirections:\n");
			redir = cmd->redir;
			while (redir)
			{
				printf("  Redir type: %d, filename: %s\n",
				redir->type, redir->filename);
				redir = redir->next;
			}
		}
		cmd = cmd->next;
		printf("\n");
	}
}
*/

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_isdigit_str(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
