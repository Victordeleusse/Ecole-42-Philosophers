NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS =	main.c threads.c utils.c initialisation.c handle_life.c handle_death.c eating_process.c msg.c

SRCS_PATH = srcs/
OBJS_PATH = objs
HEADER_PATH = ${SRCS_PATH}includes/

HEADER = philo.h

vpath %.c ${SRCS_PATH}
vpath %.h ${HEADER_PATH}



# CFLAGS += -fsanitize=address,undefined -g2
# CFLAGS += -valgrind
# CFLAGS += -g 

all: ${NAME}

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}

${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile ${HEADER}
		mkdir -p ${OBJS_PATH}
		${CC} ${CFLAGS} -g -c $< -o $@ -I ${HEADER_PATH}

${NAME}: ${OBJS}
		@ $(CC) $(CFLAGS) -o ${NAME} ${OBJS}

clean:	
		rm -f ${OBJS} ${DEPS}
		clear

fclean:	clean
		rm -f ${NAME}
		clear

-include $(DEPS) $(DEPS_BONUS) 

re:	fclean all

.PHONY: clean fclean re 
