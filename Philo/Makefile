NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS =	main.c threads.c utils.c initialisation.c error.c check.c

OBJS = ${SRCS:.c=.o}
DEPS = ${SRCS:.c=.d}

# CFLAGS += -fsanitize=address,undefined -g2
# CFLAGS += -valgrind
# CFLAGS += -g 

all: ${NAME}
	clear

${NAME}: ${OBJS}
		@ $(CC) -o ${NAME} $(CFLAGS) ${OBJS}

%.o: %.c 
			${CC} -MMD -o $@ -c $<

clean:	
		rm -f ${OBJS} ${DEPS}
		clear

fclean:	clean
		rm -f ${NAME}
		clear

-include $(DEPS) $(DEPS_BONUS) 

re:	fclean all

.PHONY: clean fclean re bonus