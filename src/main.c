/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madel-va <madel-va@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:55:15 by madel-va          #+#    #+#             */
/*   Updated: 2025/05/17 13:55:15 by madel-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *shell, int status)
{
	free_array(shell->env);
	exit(status);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**copy;

	i = 0;
	while (arr[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
		{
			free_array(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	process_command(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		ret;

	tokens = tokenize_input(input);
	if (!tokens)
		return (0);
	if (!validate_tokens(tokens, shell))
	{
		free_tokens(tokens);
		return (0);
	}
	cmds = parse_tokens(&tokens, shell);
	free_tokens(tokens);
	if (!cmds)
		return (0);
	ret = execute_cmd(cmds, shell);
	shell->last_exit_status = ret;
	free_cmds(cmds);
	return (0);
}

static int	shell_loop(t_shell *shell)
{
	char	*input;
	char	*trimmed;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		trimmed = ft_strtrim(input, " \t");
		if (trimmed && *trimmed)
		{
			add_history(input);
			process_command(shell, trimmed);
		}
		free(trimmed);
		free(input);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.last_exit_status = 0;
	if (!env || !env[0])
		shell.env = create_default_env();
	else
		shell.env = ft_arrdup(env);
	increment_shlvl(shell.env);
	init_signals();
	shell_loop(&shell);
	rl_clear_history();
	exit_shell(&shell, 0);
	return (0);
}

// 
/*
1. The readline() function reads a line from the terminal and returns it,
	using prompt as a prompt. If no prompt is given as parameter,
	no prompt will be shown in the terminal. The line returned is allocated
	! with malloc and we have to free it ourselves. 

2. add_history() is a function provided by the GNU Readline library in C.
	It is used to add a command or input line to the history list, which
	allows users to navigate through previously entered commands using the
	arrow keys.
	The history list is managed internally by the GNU Readline library.
	It is stored in a dynamically allocated memory structure managed by Readline.
	This history exists only during the program's runtime unless manually saved
	to a file.

	To access command history using arrow keys during a program, you need to
	properly 
	! configure and link the GNU Readline library compiling with (-lreadline)

3. The rl_clear_line() function clears the history list by deleting all of
	the entries.
	The rl_clear_line() function frees data that the readline library saves
	in the histroy list.


? 	When handling signals like SIGINT (Ctrl+C) or background messages,
?	rl_on_new_line()
??	ensures the input prompt behaves correctly.

? When to Use rl_replace_line()
??	 - Clearing user input after an interrupt (Ctrl+C).
??	 - Replacing user input dynamically (e.g., autocomplete, modifications).
??	 - Handling asynchronous input (e.g., background tasks modifying input).
*/
