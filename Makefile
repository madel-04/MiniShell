NAME = minishell
CC = cc
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = -I include/ -I libft/
LIBFT = libft/libft.a
SRC =   $(SRC_DIR)builtins/builtins.c \
				$(SRC_DIR)expand/expand_variable_utils.c \
				$(SRC_DIR)expand/expand_variable_utils_2.c \
				$(SRC_DIR)expand/expand_variable.c \
				$(SRC_DIR)utils/frees.c \
				$(SRC_DIR)main.c \
				$(SRC_DIR)parser/parse_tokens.c \
				$(SRC_DIR)utils/proces_x.c \
				$(SRC_DIR)signals/signals.c \
				$(SRC_DIR)parser/tokenize_input.c \
				$(SRC_DIR)utils/tokens_utils.c \
				$(SRC_DIR)utils/utils.c \
				$(SRC_DIR)parser/validate_tokens.c \
				$(SRC_DIR)executor/execute_cmd.c \
				$(SRC_DIR)executor/execute_cmd_utils.c \
				$(SRC_DIR)executor/redirect_io.c \
				$(SRC_DIR)executor/heredoc.c \
				$(SRC_DIR)utils/env_utils.c \
				$(SRC_DIR)utils/get_word.c \
				$(SRC_DIR)utils/utils2.c \
				$(SRC_DIR)builtins/builtins2.c \
				$(SRC_DIR)builtins/builtins3.c \
				$(SRC_DIR)executor/add_redirections.c \
				$(SRC_DIR)parser/handle_quotes.c \
				$(SRC_DIR)utils/ft_qsort.c \
				$(SRC_DIR)utils/shell_level.c \


CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -Llibft -lft

OBJ = $(SRC:$(SRC_DIR)%= $(OBJ_DIR)%)
OBJ := $(OBJ:.c=.o)

SANITIZER = -fsanitize=address
VALGRIND = valgrind --leak-check=full --track-origins=yes

# SANITIZER = -fsanitize=thread // -fsanitize=address
# valgrind --tool=helgrind 
# valgrind --tool=drd 

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@echo "Compilando el ejecutable: $(NAME)"
		@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LDFLAGS)
		@echo "Compilación completada"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Compilando libft..."
	@make -s -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -s fclean -C libft

fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C libft

re: fclean all
