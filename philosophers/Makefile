NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c clean_up.c inits.c is_valide.c philosophers.c utils.c routine_helpers.c monitor_helpers.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
