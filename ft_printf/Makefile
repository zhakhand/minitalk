SRCS = ft_printf.c ft_putnbr.c ft_putchar.c ft_putstr.c ft_putnbr_hex.c ft_putunsigned.c ft_strchr.c

HEAD = ft_printf.h

NAME = libftprintf.a

AR = ar rcs

RM = rm -f

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

CC = cc

all: ${NAME}

.c.o: $(HEAD)
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
