# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madel-va <madel-va@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:19:57 by madel-va          #+#    #+#              #
#    Updated: 2024/09/23 16:19:57 by madel-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB			= ar rcs
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= libft.a

SRC			= other/ft_tolower.c \
			  put_x/ft_putstr_fd.c \
			  put_x/ft_putendl_fd.c \
			  is_x/ft_isalnum.c \
			  is_x/ft_isalpha.c \
			  is_x/ft_isdigit.c \
			  is_x/ft_isascii.c \
			  is_x/ft_isprint.c \
			  str/ft_strlen.c \
			  mem/ft_memset.c \
			  other/ft_bzero.c \
			  mem/ft_memcpy.c \
			  mem/ft_memmove.c \
			  str/ft_strlcpy.c \
			  str/ft_strlcat.c \
			  other/ft_toupper.c \
			  str/ft_strcmp.c \
			  str/ft_strnstr.c \
			  put_x/ft_putchar_fd.c \
			  put_x/ft_putnbr_fd.c \
			  str/ft_strjoin.c \
			  other/ft_calloc.c \
			  str/ft_strdup.c \
			  mem/ft_memchr.c \
			  mem/ft_memcmp.c \
			  str/ft_substr.c \
			  other/ft_itoa.c \
			  other/ft_split.c \
			  str/ft_strrchr.c \
			  str/ft_strmapi.c \
			  str/ft_striteri.c \
			  other/ft_atoi.c \
			  str/ft_strchr.c \
			  str/ft_strtrim.c

OBJ			= $(SRC:%.c=%.o)
#Para generar los archivos objetos de una lista fuente SRCS


INCLUDE		= libft.h

SRCBONUS	= lst/ft_lstnew_bonus.c \
			  lst/ft_lstadd_front_bonus.c \
			  lst/ft_lstsize_bonus.c \
			  lst/ft_lstlast_bonus.c \
			  lst/ft_lstadd_back_bonus.c \
			  lst/ft_lstdelone_bonus.c \
			  lst/ft_lstclear_bonus.c

OBJBONUS	= $(SRCBONUS:%.c=%.o)

all: $(NAME)
#Define el target/objetivo y especifica que depende de NAME
#Si el archivo no existe o no está actualizado se ejecutan las reglas para obtenerlo

$(NAME): $(OBJ) $(INCLUDE)
		$(LIB) $(NAME) $(OBJ)

# gcc $(FLAGS) -c $(SRCS) -I ./ 
#Para compilar con las flags en el directorio actual, la I (Include directory) busca archivos de cabecera
#en el directorio indicado. Los archivos fuentes .c con la cabecera propia (libft.h), si el .h está en el
#directorio actual, se necesita el flag para que el compilador realice su función
#Fuerza a buscar en mi directorio sobre los del sistema si hubiera coincidencias

bonus: $(OBJ) $(OBJBONUS) $(INCLUDE)
	$(LIB) $(NAME) $(OBJBONUS) $(OBJ)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@
#El archivo .o depende del respectivo .c y la cabecera includeç
#la -c $< se refiere a la primera dependencia de la regla, siendo .c en este caso
# -o $@ indica el nombre del archivo de salida y el $@ se refiere al nombre del objetivo de la regla (.o)

.PHONY: clean fclean re rebonus
#Objetivos declarados ficticios para que se ejecuten siempre que se invoquen sin importar
#que haya archivos con los mismos nombres.

clean:
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)
#Ejecuta primero el clean para eliminar los archivos objetos y luego la libreria .a y
# y vuelve a compilar los archivos generales 

re: fclean all
#re for rebuilt
#Aegurarse de que se construya desde un estado limpio
#eliminando cualquier problema o residuo de compilaciones anteriores

rebonus: fclean bonus
