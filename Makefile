NAME = philo

SRCS =	main.c \
		parse.c\
		init_philo.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread
#CFLAGS += -fsanitize=address -g3

RM = rm -rf

all:	$(NAME)

$(NAME): ${OBJS}
	$(CC) -o $(NAME) ${OBJS} $(CFLAGS)
	
clean:
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re