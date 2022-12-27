NAME		=	philo

SRC			=	philo.c init.c utils.c actions.c thread.c

OBJ			=	$(SRC:.c=.o)

CC			=	gcc 

RM			=	rm -f
CFLAGS		=	-pthread -Wall -Werror -Wextra

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			${RM} $(OBJ)

fclean: 	clean
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re
