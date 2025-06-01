# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 09:23:03 by nbuchhol          #+#    #+#              #
#    Updated: 2025/06/01 12:16:22 by nbuchhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalnum.c \
	  ft_isascii.c \
	  ft_isspace.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_strlen.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  ft_strlcpy.c \
	  ft_memset.c \
	  ft_memcpy.c \
	  ft_strlcat.c \
	  ft_bzero.c \
	  ft_memmove.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_strncmp.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_strnstr.c \
	  ft_atoi.c \
	  ft_calloc.c \
	  ft_strdup.c \
	  ft_substr.c \
	  ft_strjoin.c \
	  ft_strtrim.c \
	  ft_split.c \
	  ft_itoa.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putendl_fd_1.c \
	  ft_putendl_fd_0.c \
	  ft_putendl_fd_n.c \
	  ft_putnbr_fd.c \
	  ft_lstadd_back.c \
	  ft_lstadd_front.c \
	  ft_lstclear.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstlast.c \
	  ft_lstmap.c \
	  ft_lstnew.c \
	  ft_lstsize.c
PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
OBJ = ${SRC:.c=.o}
RM = rm -f

all: ${PRINTF} ${NAME}

${NAME}: ${OBJ} ${PRINTF}
	@ar rcs ${NAME} ${OBJ} ${PRINTF}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${PRINTF}:
	@make -C ${PRINTF_DIR}

clean:
	@${RM} ${OBJ}
	@make -C ${PRINTF_DIR} clean

fclean: clean
	@${RM} ${NAME}
	@make -C ${PRINTF_DIR} fclean

re: fclean all

.PHONY = all clean fclean re
