# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-hajj <yel-hajj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 15:51:06 by yel-hajj          #+#    #+#              #
#    Updated: 2023/02/03 16:44:30 by yel-hajj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
FRM = rm -rf

NAME = pipex
BONUS = pipex_bonus
HEADER = pipex.h

SRCMAN = pipex.c \
		split.c \
		fns.c \
		fns2.c \

SRCBON = pipex_bonus.c \
		split.c \
		fns.c \
		fns2.c \
		get_next_line_utils.c \
		get_next_line.c \

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(SRCMAN) $(HEADER)
	$(CC) $(CFLAGS) $(SRCMAN) -o $(NAME)

$(BONUS): $(SRCBON) $(HEADER)
	$(CC) $(CFLAGS) $(SRCBON) -o $(BONUS)

clean:
	$(FRM) $(NAME)

fclean: clean
	$(FRM) $(BONUS)

re: fclean all
