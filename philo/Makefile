
CC = gcc
CFLAGS = -Wall -Wextra -Werror -DM -fsanitize=address 

NAME = philo
SRC = main.c utils.c init.c tasks.c observer.c

# Do not change these
OBJ = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	@echo "\033[0;34mLinking $@\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo "\033[0;33mFinished building $@\033[0m"

clean:
	@echo "\033[0;31mDeleting $(OBJ)\033[0m"
	@rm -rf $(OBJ)

fclean: clean
	@echo "\033[0;31mDeleting $(NAME)\033[0m"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
