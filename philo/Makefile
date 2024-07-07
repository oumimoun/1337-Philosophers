HEADER = philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = philo
SRC = philo.c\
	philo_utils.c\
	main.c\
	parce.c\
	threads.c\
	routine.c\
	monitor.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
