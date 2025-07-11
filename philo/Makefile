NAME	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread -g

SRC		= main.c \
		  parsing.c \
		  philo_utils.c \
		  libft_utils.c \
		  routine.c

OBJ		= $(SRC:.c=.o)

HEADER	= philo.h

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

.PHONY: all clean fclean re
