# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgomes-g <rgomes-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 13:35:38 by rgomes-g          #+#    #+#              #
#    Updated: 2026/01/27 14:02:54 by rgomes-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
THREAD	= -pthread
INC		= -Iincludes

SRCS	= srcs/init.c \
		  srcs/pthread.c \
		  srcs/utils.c \
		  srcs/str_utils.c \
		  srcs/routine.c \
		  srcs/main.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(THREAD) -o $(NAME)

%.o: %.c includes/philosophers.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
