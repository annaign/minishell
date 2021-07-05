# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 19:46:19 by pshagwel          #+#    #+#              #
#    Updated: 2020/11/20 19:46:20 by pshagwel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/
PRINTF = ft_printf/

H_DIR = includes/
SRC_DIR = src/
OBJ_DIR = obj/

SRC =	main.c \
		get_next_line.c \
		ft_read_fd.c \
		ft_err_exit.c \
		ft_init.c \
		ft_free_memory.c \
		ft_read_command.c \
		ft_parse_command.c \
		ft_parse_redicrect.c \
		ft_create_cmd.c \
		ft_cmd_pwd.c \
		ft_cmd_export.c \
		ft_cmd_env.c \
		ft_cmd_exit.c \
		ft_cmd_echo.c \
		ft_cmd_cd.c \
		ft_cmd_unset.c \
		ft_cmd_external.c \
		ft_parse_arg.c \
		ft_parse_tool.c \
		ft_parse_sign.c \
		ft_get_path.c \
		ft_builtin_function.c \
		ft_pipes.c \
		ft_signals.c \
		ft_redirect.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
# add list of dependency files
DEP = $(addprefix $(OBJ_DIR), $(SRC:.c=.d))

# Setting the compiler and the default linker program
CC = gcc
# main compilation options
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -ggdb3
# options for pre-processor (-I, -include, -D ... )
CPPFLAGS = -MMD $(INCLUDES)
# libs and path for linker
LDLIBS = $(LIBFT)libft.a $(PRINTF)libftprintf.a

INCLUDES = -I$(H_DIR) -I$(LIBFT) -I$(PRINTF)

OS := $(shell uname)
ifeq ($(OS), Linux)
	INCLUDES += -Iinc_linux
	CFLAGS += -std=gnu99
endif
ifeq ($(OS), Darwin)
	INCLUDES += -Iinc_mac
	CFLAGS += -std=c99
endif

.PHONY: all clean fclean makeobjdir re bonus leaks

$(shell mkdir -p $(OBJ_DIR))

all:$(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# include dependency files
-include $(DEP)

$(NAME): $(OBJ)
		@make -C $(LIBFT)
		@make -C $(PRINTF)
		$(CC) $(OBJ) $(LDLIBS) -o $(NAME)

clean:
		/bin/rm -rf $(OBJ_DIR)
		cd $(LIBFT) && $(MAKE) clean
		cd $(PRINTF) && $(MAKE) clean

fclean: clean
		/bin/rm -f $(NAME)
		cd $(LIBFT) && $(MAKE) fclean
		cd $(PRINTF) && $(MAKE) fclean

makeobjdir:
		$(shell mkdir -p $(OBJ_DIR))

bonus: all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	./minishell

re: fclean makeobjdir all
