
CC = gcc
CFLAGS = -Wall -Wextra -Werror -DM

NAME = philo
SRC = main.c utils.c init.c print.c tasks.c

# Do not change these
OBJ = $(SRC:.c=.o)

all: $(NAME)

#-include $(OBJ_FILES:.o=.d)

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	@echo "\033[0;32mCompiling $<\033[0m"
#	@mkdir -p $(basename $@)
#	@$(CC) $(CFLAGS) -c $< -o $@

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
