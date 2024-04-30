CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := philo_bonus
SRC_DIR := src
BIN_DIR := bin

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<
	
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean all

.PHONY : all clean fclean re
