NAME = minishell
CC = cc
OBJ_DIR = obj/
SRC_DIR = src/
INCLUDES = -I include/
SRC =   $(SRC_DIR)parser.c \
                $(SRC_DIR)main.c \
                $(SRC_DIR)init.c \
                $(SRC_DIR).c \
                $(SRC_DIR).c \
                $(SRC_DIR).c \
                $(SRC_DIR).c \
                $(SRC_DIR).c \

CFLAGS = -Wall -Wextra -Werror -pthread -g
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(notdir $(SRC)))

# SANITIZER = -fsanitize=thread // -fsanitize=address
# valgrind --tool=helgrind 
# valgrind --tool=drd 

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
        @echo "Compilando el ejecutable: $(NAME)"
        $(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)
        @echo "Compilación completada"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
        @mkdir -p $(OBJ_DIR)
        @echo "Compilando: $< -> $@"
        $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
        @rm -rf $(OBJ_DIR)

fclean: clean
        @rm -f $(NAME)

re: fclean all%