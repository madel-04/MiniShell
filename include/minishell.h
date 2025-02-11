#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <ctype.h>
# include <string.h>

typedef enum e_type
{
	TOKEN_WORD, // 0
	TOKEN_PIPE, // 1
	TOKEN_a, // 2
	TOKEN_b, // 3
	TOKEN_c, // 4
}		t_type;

typedef struct s_token
{
	t_type				type;
	char			*value;
	struct s_token	*next;
}	t_token;

#endif

// ~ https://42-cursus.gitbook.io/guide/rank-03/minishell/functions | EXPLICACIONES DE VARIAS FUNCIONES

/*
! Red (!)
? Blue (?)
* Green (*)
^ Yellow (^)
& Pink (&)
~ Purple (~)
TODO Mustard (todo)
// Grey (//)
*/