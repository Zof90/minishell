# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/02 16:45:53 by codespace         #+#    #+#              #
#    Updated: 2026/04/03 18:04:37 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Werror -Wextra 
NAME = minishell
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
HEADER = include/minishell.h
all: $(NAME)
$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -lhistory -o $(NAME)
src/%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) -Iinclude -I$(LIBFT_PATH) -c $< -o $@
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
re: fclean all
.PHONY: all clean fclean re	