NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS =	eating_process.c handle_death.c handle_life.c initialisation.c main.c threads.c utils.c 
		
SRCS_PATH = srcs/
OBJS_PATH = objs

HEADER_PATH += ${SRCS_PATH}includes/
HEADER = philo.h

vpath %.c ${SRCS_PATH}
vpath %.h ${HEADER_PATH} 
# *.h -> ./srcs/includes/philo.h

all: ${NAME}

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}

${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile ${HEADER}
		mkdir -p ${OBJS_PATH}
		${CC} ${CFLAGS} -g -c $< -o $@ -I ${HEADER_PATH}

${NAME}: ${OBJS} 
		$(CC) -o ${NAME} $(CFLAGS) ${OBJS}  

clean:	
		rm -rf $(OBJS_PATH)
		clear

fclean:	clean
		rm -f ${NAME}
		clear

re:	fclean all

.PHONY: clean fclean re 