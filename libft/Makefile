# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshagwel <pshagwel@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/06 21:53:58 by pshagwel          #+#    #+#              #
#    Updated: 2020/05/06 22:17:32 by pshagwel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_DIR = obj/

SRC =	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strcmp.c \
		ft_atof.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
DEP = $(addprefix $(OBJ_DIR), $(SRC:.c=.d))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -ggdb3
CPPFLAGS = -MMD

.PHONY: all clean fclean re

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)

$(OBJ_DIR)%.o: %.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEP)

$(NAME): $(OBJ)
		ar rc $@ $^
		ranlib $(NAME)

clean:
		/bin/rm -rf $(OBJ_DIR)

fclean: clean
		/bin/rm -f $(NAME)

makeobjdir:
		$(shell mkdir -p $(OBJ_DIR))

re: fclean makeobjdir all