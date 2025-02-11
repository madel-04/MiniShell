#include "minishell.h"

int	main(void)
{
	char		*input;
	t_token		*tokens;

	while (1)
	{
		input = readline("minishell> "); // ^ READLINE [1]
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (input)
			add_history(input); // ^ ADD_HISTORY [2]
		tokens = tokenize_input(input); // TODO
		free(input);
		if (!tokens)
			continue;
		// TODO Implementación del programa??
	}
	rl_clear_history(); // ^ Clear History [3]
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
	allows users to navigate through previously entered commands using the arrow keys.
	The history list is managed internally by the GNU Readline library.
	It is stored in a dynamically allocated memory structure managed by Readline.
	This history exists only during the program's runtime unless manually saved to a file.

	To access command history using arrow keys during a program, you need to properly 
	! configure and link the GNU Readline library compiling with (-lreadline)

3. The rl_clear_line() function clears the history list by deleting all of the entries.
	The rl_clear_line() function frees data that the readline library saves in the histroy list.


? 	When handling signals like SIGINT (Ctrl+C) or background messages, rl_on_new_line()
??	ensures the input prompt behaves correctly.

? When to Use rl_replace_line()
??	 - Clearing user input after an interrupt (Ctrl+C).
??	 - Replacing user input dynamically (e.g., autocomplete, modifications).
??	 - Handling asynchronous input (e.g., background tasks modifying input).
*/