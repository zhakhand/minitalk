SRCS = client.c server.c

HEAD = minitalk.h 

NAME = minitalk

CC = cc

RM = rm -f

OBJS = ${SRCS:%.c=%.o}

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -Ilibft -Ift_printf -c $? -o $@

${NAME}:	server client

server:	server.o
		${MAKE} -C libft
		${MAKE} -C ft_printf
		${CC} ${CFLAGS} $? ./libft/libft.a ./ft_printf/libftprintf.a -o server

client: client.o
		${MAKE} -C libft
		${MAKE} -C ft_printf
		${CC} ${CFLAGS} $? ./libft/libft.a ./ft_printf/libftprintf.a -o client

libft:
		make -C libft

printf:
		make -C ft_printf

clean:
		make clean -C libft
		make clean -C ft_printf
		${RM} ${OBJS}

fclean: clean
		${RM} server client

re:		fclean all

.PHONY:	libft ft_printf