NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I.

SRC = main.c utils.c init.c routine.c monitor.c print_status.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all