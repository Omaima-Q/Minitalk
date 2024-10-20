# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/17 17:21:00 by oqaroot           #+#    #+#              #
#    Updated: 2024/10/17 17:21:02 by oqaroot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = client.c server.c utils.c
SRC_BNS = client_bonus.c server_bonus.c utils.c

CLIENT_NAME = client
SERVER_NAME = server

CLIENT_BNS = client_bonus
SERVER_BNS = server_bonus

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(CLIENT_NAME) $(SERVER_NAME)

bonus: $(CLIENT_BNS) $(SERVER_BNS)

$(CLIENT_NAME): client.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_NAME): server.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_BNS): client_bonus.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_BNS): server_bonus.o utils.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "\033[1;34mCompile C file\033[1;0m"

clean:
	$(RM) $(OBJ) $(OBJ_BNS)
	@echo "\033[1;33mClean object files... ✅\033[1;0m"

fclean: clean
	$(RM) $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BNS) $(SERVER_BNS)
	@echo "\033[1;33mClean executables... ✅\033[1;0m"

re: fclean all

