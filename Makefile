# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:08:43 by cmenke            #+#    #+#              #
#    Updated: 2023/05/10 23:47:22 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# := sets the value only once

NAME := pipex

SRCDIR := mandatory

SRCS := $(addprefix ${SRCDIR}/,main.c \
								error_and_free.c \
								checks.c \
								get_cmd_args.c \
								childs.c \
								envp_paths.c \
								remove_quotes.c)

OBJS := ${SRCS:.c=.o}

HEADER := ${SRCDIR}/pipex.h

LIBFTDIR := libft

LIBFT := libft.a

INCLUDE := ${LIBFTDIR}/${LIBFT}

CFLAGS := -Wall -Wextra -g
# CFLAGS := -Wall -Werror -Wextra -g

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