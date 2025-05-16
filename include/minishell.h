/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:34 by marvin            #+#    #+#             */
/*   Updated: 2025/03/26 16:04:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <ctype.h>
# include <string.h>
# include <errno.h>
# include "../libft/libft.h"

# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal_received;

typedef enum e_type
{
	TOKEN_WORD, //0
	TOKEN_PIPE, // 1
	TOKEN_INPUT, // 2
	TOKEN_OUTPUT, // 3
	TOKEN_HEREDOC, // 4
	TOKEN_RED_OUTPUT_APPEND, // 5
}		t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	char			**envp;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	int				last_exit_status;
	char			**env;
}	t_shell;

typedef struct s_exp
{
	const char		*token;
	size_t			i;
	char			*result;
	size_t			res_index;
	size_t			buff_size;
	int				in_single;
	int				in_double;
	int				last_exit_status;
}	t_exp;

typedef struct s_parse
{
	t_cmd		*cmd_head;
	t_cmd		*current_cmd;
	char		**argv;
	int			argc;
	t_token		*token;
	t_shell		*shell;
}				t_parse;

typedef struct s_partition_args
{
	void	*base;
	size_t	n;
	size_t	size;
	int		(*ft_compar)(const void *, const void *);
}	t_partition_args;

// *** ADD REDIRECTIONS ***
int		add_redirection(t_parse *p);

// *** BUILTINS ***
void	ft_echo(char **argv);
void	ft_cd(char **argv, t_shell *shell);
void	ft_pwd(void);
void	ft_unset(char **argv, t_shell *shell);
void	ft_env(t_shell *shell);

// *** BUILTINS 2 ***
void	ft_export(char **argv, t_shell *shell);
void	ft_exit(char **argv, t_shell *shell);

// *** ENV UTILS ***
char	*get_env_value(const char *name, char **env);
void	set_env_var(const char *name, const char *value, t_shell *shell);
void	unset_env_var(const char *name, t_shell *shell);
void	print_env(char **env);

// *** EXECUTE CMD UTILS ***
int		execute_builtin(t_cmd *cmd, t_shell *shell);
pid_t	create_child_process(int prev_pipe_in, int fd[2], t_cmd *current,
			t_shell *shell);

// *** EXECUTE CMD ***
int		execute_cmd(t_cmd *cmds, t_shell *shell);

// *** EXPAND VARIABLE UTILS 2 ***
void	handle_variable(t_exp *exp, t_shell *shell);

// *** EXPAND VARIABLE UTILS ***
void	append_char(t_exp *exp, char c);
void	append_str(t_exp *exp, const char *str);
void	handle_exit_status(t_exp *exp);

// *** EXPAND VARIABLE ***
char	*expand_variable(char *token, int last_exit_status, t_shell *shell);

// *** FREE ***
char	*ft_strjoin_free(char *s1, char *s2);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);

// *** FT_QSORT ***
void	ft_qsort(void *base, size_t n, size_t size,
			int (*ft_compar)(const void*, const void*));

// *** GET WORD ***
char	*ft_get_word(char *input, int *i);

// *** HANDLE QUOTES ***
int		handle_quotes(char *input, int *i, char **word);

// *** PARSE TOKENS ***
t_cmd	*parse_tokens(t_token **tokens, t_shell *shell);

// *** PROCESS X ***
void	process_pipe(t_parse *p);
int		process_redir(t_parse *p);
int		validate_redirection_token(t_parse *p);
int		process_word(t_parse *p);

// *** REDIRECT IO ***
void	redirect_io(t_redir *redir);

// *** SIGNALS ***
int		ft_sigemptyset(sigset_t *set);
void	init_signals(void);
void	handle_sigint(int sig);

// *** TOKENIZE INPUT ***
t_token	*tokenize_input(char *input);
void	parse_input_token(char *input, int *i, t_token **tokens);
void	ft_isline_or_triangle(int *i, char *input, char *op, t_token **tokens);

// *** TOKENS UTILS ***
void	add_token(t_token **head, t_token *new_token);
t_token	*new_token(int type, char *value);

// *** UTILS ***
int		ft_isspace(int c);
void	*ft_realloc(void *ptr, size_t new_size);
//void	print_tokens(t_token *tokens);
//void	print_cmd(t_cmd *cmd);
void	free_array(char **arr);
int		ft_isdigit_str(const char *str);

// *** UTILS 2 ***
char	*get_cmd_path(char *cmd, char **env);
char	**env_to_array(char **env);
void	print_env_sorted(char **env);

// *** VALIDATE TOKENS ***
int		validate_tokens(t_token *tokens, t_shell *shell);
int		validate_token_sequence(t_token *tokens, t_shell *shell);
int		handle_unexpected_pipe(t_shell *shell);
int		validate_pipe(t_token *cur, t_token *tokens, t_shell *shell);
int		validate_redirection(t_token *cur, t_shell *shell);

#endif
//& https://miro.com/app/board/uXjVIAeHVPM=/?share_link_id=518566271365
