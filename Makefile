SRCS = client.c server.c

SRCS_BONUS = server_bonus.c client_bonus.c

HEAD = minitalk.h 

NAME = minitalk

NAME_BONUS = minitalk_bonus

CC = cc

RM = rm -f

OBJS = ${SRCS:%.c=%.o}

OBJS_BONUS = ${SRCS_BONUS:%.c=%.o}

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -Ilibft -Ift_printf -c $? -o $@

${NAME}:	server client

${NAME_BONUS}:	server_bonus client_bonus

server:	server.o
		${MAKE} -C libft
		${MAKE} -C ft_printf
		${CC} ${CFLAGS} server.c utils.c ./libft/libft.a ./ft_printf/libftprintf.a -o server

client: client.o
		${MAKE} -C libft
		${MAKE} -C ft_printf
		${CC} ${CFLAGS} client.c utils.c ./libft/libft.a ./ft_printf/libftprintf.a -o client

server_bonus: server_bonus.o
			  ${MAKE} -C libft
			  ${MAKE} -C ft_printf
			  ${CC} ${CFLAGS} server_bonus.c utils.c ./libft/libft.a ./ft_printf/libftprintf.a -o server_bonus

client_bonus: client_bonus.o
			  ${MAKE} -C libft
			  ${MAKE} -C ft_printf
			  ${CC} ${CFLAGS} client_bonus.c utils.c ./libft/libft.a ./ft_printf/libftprintf.a -o client_bonus

libft:
		make -C libft

printf:
		make -C ft_printf

clean:
		make clean -C libft
		make clean -C ft_printf
		${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
		${RM} server client server_bonus client_bonus

re:		fclean all

bonus:	${NAME_BONUS}

.PHONY:	libft ft_printf bonus all clean fclean re