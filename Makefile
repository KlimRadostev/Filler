#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kradoste <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/05 17:52:37 by kradoste          #+#    #+#              #
#    Updated: 2019/06/30 17:29:35 by kradoste         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = klim.filler
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = *.c
OBJ = $(SRC:.c=.o)
LIB_LINK = -L ./libft -lft

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(LIB_LINK) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f *~

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all