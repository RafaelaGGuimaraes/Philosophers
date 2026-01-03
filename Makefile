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
