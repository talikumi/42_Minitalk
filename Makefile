# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsociety <fsociety@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 16:44:11 by fsociety          #+#    #+#              #
#    Updated: 2023/01/23 18:22:52 by fsociety         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft/ -Llibft -lft
LIBFT = ./libft/libft.a
FILE_1 = server
FILE_2 = client

all: $(LIBFT) client server

$(LIBFT):
	@$(MAKE) -C libft/

server: $(LIBFT) src/server.c
	@$(CC) $(CFLAGS) -o server src/server.c
client: $(LIBFT) src/client.c
	@$(CC) $(CFLAGS) -o client src/client.c

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(FILE_1)
	@rm -f $(FILE_2)
	@$(MAKE) fclean -C libft/

re: fclean all