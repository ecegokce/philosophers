NAME = philo

SRCS = main.c init_data.c init_philo.c utils.c philo_utils.c philo_act.c philo_lifecycle.c create_thread.c checker.c time.c clean.c
 
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re