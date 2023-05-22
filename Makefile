# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:08:43 by cmenke            #+#    #+#              #
#    Updated: 2023/05/22 19:17:54 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# := sets the value only once

NAME := pipex

SRCDIR := mandatory

PROCESS_CMD_LINE := $(addprefix process_cmd_line/, count_elements.c \
													ft_get_cmd_line_elements.c \
													remove_quotes.c)

SRCS := $(addprefix ${SRCDIR}/,main.c \
								error_and_free.c \
								childs.c \
								envp_paths.c \
								${PROCESS_CMD_LINE})

OBJS := ${SRCS:.c=.o}

HEADER := ${SRCDIR}/pipex.h

LIBFTDIR := libft

LIBFT := libft.a

INCLUDE := ${LIBFTDIR}/${LIBFT}

CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}

${NAME}: ${OBJS} ${LIBFTDIR}/${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}

${OBJS}: ${HEADER}

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFTDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}

re: fclean all

.PHONY: all clean fclean re library

.NOTPARALLEL: