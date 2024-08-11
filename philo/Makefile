CC=cc
CFLAGS= -Wall -Wextra -Werror -I.
NAME=philo
SRCDIR=src
BINDIR=bin
OBJ=$(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(wildcard $(SRCDIR)/*.c))

vpath %.c src

all : $(NAME)

$(NAME) : $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(BINDIR) :
	mkdir -p $@

$(BINDIR)/%.o : %.c | $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(BINDIR)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
.SECONDARY:
