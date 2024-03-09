HEADER = ./philo_mandatory/philo.h
CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
SRC = ./philo_mandatory/philo.c 

OBJ = $(SRC:.c=.o)

# NAME_BONUS = pipex_bonus

# SRC_BONUS = ./pipex_bonus_folder/pipex_bonus.c

# OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# bonus: $(NAME_BONUS)

# $(NAME_BONUS): $(OBJ_BONUS)
# 	$(CC) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
