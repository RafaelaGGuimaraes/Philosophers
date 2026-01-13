# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/13 18:29:17 by rgomes-g          #+#    #+#              #
#    Updated: 2026/01/13 18:31:27 by rgomes-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
THREAD	= -pthread
INC		= -Iincludes

SRCS	= srcs/main.c \
		  srcs/init.c \
		  srcs/simulation.c \
		  srcs/utils.c \
		  srcs/str_utils.c \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(THREAD) -o $(NAME)

%.o: %.c includes/philo.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
