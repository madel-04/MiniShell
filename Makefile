NAME = minishell
CC = cc
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = -I include/ -I libft/
LIBFT = libft/libft.a
SRC =   $(SRC_DIR)builtins.c \
				$(SRC_DIR)expand_variable_utils.c \
				$(SRC_DIR)expand_variable_utils_2.c \
				$(SRC_DIR)expand_variable.c \
				$(SRC_DIR)frees.c \
				$(SRC_DIR)main.c \
				$(SRC_DIR)parse_tokens.c \
				$(SRC_DIR)proces_x.c \
				$(SRC_DIR)signals.c \
				$(SRC_DIR)tokenize_input.c \
				$(SRC_DIR)tokens_utils.c \
				$(SRC_DIR)utils.c \
				$(SRC_DIR)validate_tokens.c \
				$(SRC_DIR)execute_cmd.c \
				$(SRC_DIR)execute_cmd_utils.c \
				$(SRC_DIR)redirect_io.c \
				$(SRC_DIR)env_utils.c \
				$(SRC_DIR)get_word.c \
				$(SRC_DIR)utils2.c \
				$(SRC_DIR)builtins2.c \
				$(SRC_DIR)add_redirections.c \
				$(SRC_DIR)handle_quotes.c \
				$(SRC_DIR)ft_qsort.c \



CFLAGS = -Wall -Wextra -Werror -pthread -g
LDFLAGS = -lreadline -Llibft -lft
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRC)))

SANITIZER = -fsanitize=address
VALGRIND = valgrind --leak-check=full --track-origins=yes

# SANITIZER = -fsanitize=thread // -fsanitize=address
# valgrind --tool=helgrind 
# valgrind --tool=drd 

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@echo "Compilando el ejecutable: $(NAME)"
		$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LDFLAGS)
		@echo "Compilación completada"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
		@echo "Compilando: $< -> $@"
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Compilando libft..."
	@make -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all