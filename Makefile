NAME = philo

SRCS =	main.c \
		parse.c\
		init_philo.c \
		philo_utils.c \
		philo_utils2.c \
		philo_utils3.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread -g
#CFLAGS += -fsanitize=thread -g3 

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
