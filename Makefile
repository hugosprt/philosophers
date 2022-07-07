NAME = philo

SRCS =	main.c \
		parse.c\
		init_philo.c \
		philo_utils.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -g3
CFLAGS += -fsanitize=thread -g3

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