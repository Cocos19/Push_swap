# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 14:31:04 by mprofett          #+#    #+#              #
#    Updated: 2023/01/30 14:42:28 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SORTER_NAME		= push_swap

SORTER_SRC		= push_swap.c push_swap_get_list.c push_swap_operations.c \
				push_swap_get_sorted_values.c push_swap_operation2.c \
				push_swap_utils.c push_swap_algo_push_b_utils.c \
				push_swap_algo_push_a_utils.c

SORTER_OBJ		= ${SORTER_SRC:.c=.o}

CHECKER_NAME	= checker

CHECKER_SRC		= checker_bonus.c push_swap_get_list.c push_swap_operations.c \
				push_swap_operation2.c push_swap_get_sorted_values.c \
				push_swap_utils.c

CHECKER_OBJ		= ${CHECKER_SRC:.c=.o}

LIB_NAME	= libft.a

LIB_PATH	= ./libft

CC			= gcc

RM			= rm -f

CFLAGS	= -Wall -Wextra -Werror

all: ${LIB_NAME} ${SORTER_NAME}

${LIB_NAME}:
	${MAKE} bonus -C ${LIB_PATH}
	mv ${LIB_PATH}/${LIB_NAME} .

${SORTER_NAME}: ${SORTER_OBJ}
	${CC} ${CFLAGS} ${LIB_NAME} ${SORTER_OBJ} -o ${SORTER_NAME}

${CHECKER_NAME}: ${CHECKER_OBJ}
	${CC} ${CFLAGS} ${LIB_NAME} ${CHECKER_OBJ} -o ${CHECKER_NAME}

bonus: ${LIB_NAME} ${SORTER_NAME} ${CHECKER_NAME}

clean:
	${MAKE} clean -C ${LIB_PATH}
	${RM} ${SORTER_OBJ} ${CHECKER_OBJ}

fclean: clean
	${RM} ${SORTER_NAME} ${CHECKER_NAME} ${LIB_NAME}

re:	fclean all

.PHONY:	all bonus clean fclean re
