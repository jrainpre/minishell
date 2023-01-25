# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoller <mkoller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 15:05:43 by mkoller           #+#    #+#              #
#    Updated: 2023/01/25 10:52:44 by mkoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC        := cc
FLAGS    :=  -g
READ_INCLUDE := -lreadline -L/usr/local/lib -I/usr/local/include 

SRCS        :=      libft/ft_printf.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_printf_utils_hex.c \
                          libft/ft_bzero.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_memchr.c \
                          libft/ft_itoa.c \
                          libft/ft_isalpha.c \
                          libft/ft_isdigit.c \
                          libft/ft_memcmp.c \
                          libft/ft_tolower.c \
                          libft/ft_toupper.c \
                          libft/ft_strrchr.c \
                          libft/ft_printf_utils_print.c \
                          libft/ft_isprint.c \
                          libft/ft_strtrim.c \
                          libft/ft_strjoin.c \
                          libft/ft_strchr.c \
                          libft/ft_isascii.c \
                          libft/ft_strmapi.c \
                          libft/ft_striteri.c \
                          libft/ft_lstsize.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_calloc.c \
                          libft/ft_strnstr.c \
                          libft/ft_strlcat.c \
                          libft/ft_isalnum.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_memcpy.c \
                          libft/ft_printf_unsigned.c \
                          libft/ft_lstlast.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_strncmp.c \
                          libft/ft_lstnew.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_split.c \
                          libft/ft_strdup.c \
                          libft/ft_substr.c \
                          libft/ft_memset.c \
                          libft/ft_strlcpy.c \
                          libft/ft_atoi.c \
                          libft/ft_strlen.c \
                          libft/ft_memmove.c \
                          libft/ft_strcpy.c \
                          libft/ft_strncpy.c \
                          libft/ft_strcmp.c \
                          libft/ft_insert_substr.c  \
                          libft/ft_strcat.c \
                          libft/ft_delete_char.c \
                          libft/ft_get_str_index_of_pos.c \
                          parse_input.c \
                          env_replace.c \
                          safe_env_in_lst.c \
                          minishell.c \
                          echo.c \
                          exit.c \
                          fd_redirect_out.c \
                          fd_redirect_in.c \
                          builtin.c \
                          pwd_cd.c \
                          do_env_stuff.c \
                          PrepareInputString.c \
                          expand_tilde.c \
                          delete_closed_quotes.c \
                          in_quotes.c \
                          error.c \
                          executer.c \
                          signals.c \
                          

                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} ${READ_INCLUDE}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


