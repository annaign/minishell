#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: rmanfred <rmanfred@21-school.ru>           +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2020/05/05 23:45:50 by rmanfred          #+#    #+#             *#
#*   Updated: 2020/05/19 17:15:02 by rmanfred         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = libftprintf.a

OBJ_DIR = obj/

H_DIR = ./

INCLUDES = -I$(H_DIR)

SRC = ft_printf.c ft_put_c.c ft_put_s.c ft_put_d_i.c \
	ft_put_x.c ft_put_u.c ft_put_ptr.c ft_strlen.c \
	ft_strchr.c ft_strjoin.c ft_strdup.c ft_putstr_number.c ft_putchar.c \
	ft_isdigit.c ft_itoa.c ft_itoa_x.c ft_itoa_u.c ft_substr2.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
# add list of dependency files
DEP = $(addprefix $(OBJ_DIR), $(SRC:.c=.d))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# options for pre-processor (-I, -include, -D ... )
CPPFLAGS = -MMD $(INCLUDES)

.PHONY: all clean fclean re

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# include dependency files
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
