# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 08:28:14 by jrainpre          #+#    #+#              #
#    Updated: 2023/01/27 13:24:59 by mkoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		  ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		  ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		  ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		  ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_insert_substr.c \
BONUS   = ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c \
		  ft_lstnew.c ft_lstsize.c 

BONUS_OBJS      = ${BONUS:.c=.o}		  
OBJS			= ${SRCS:.c=.o}
INCS			= includes
NAME			= libft.a
LIBC			= ar rc
LIBR			= ranlib
CC				= cc
RM				= rm -f
CFLAGS  		= -Wall -Wextra -Werror
MAIN    		= libft_main.c
AOUT			= a.out

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} ${AOUT} ${BONUS_OBJS}

re: fclean all

bonus: ${NAME} ${0BJS} ${BONUS_OBJS}
		${LIBC} ${NAME} ${OBJS} ${BONUS_OBJS}

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)

test: ${NAME}
	${CC} ${CFLAGS} ${MAIN} ${NAME} -lbsd
	./a.out