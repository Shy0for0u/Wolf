# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgorold- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 10:09:18 by dgorold-          #+#    #+#              #
#    Updated: 2019/10/17 18:52:32 by dgorold-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = Wolf
INCLUDES = 	-I ./libft/include \
			-I ./sdl2/SDL2.framework/Headers/ \
			-I ./include

SRC_PATH =	src
SRC_LIST =	main.c \
            hooks.c \
            init_ray.c \
            initialization.c \
            read_map.c \
            read_map_helper.c \
            raycasting.c \
            drawing_window.c \
            ft_for_walls.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_LIST))

OBJ_LIST = $(SRC_LIST:.c=.o)
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_LIST))

LIBFT_PATH = libft
LIBFT = -L $(LIBFT_PATH) -lft

LIBS = 	-lm \
		-lpthread \
		-F ./sdl2/ -framework SDL2

YELLOW = \033[1;33m
PURPLE = \033[0;35m
NC = \033[0m

.PHONY: all

all: make_libft intro make_obj $(NAME)
	@echo "$(PURPLE)MAKE $(NAME) Done!$(NC)"

intro:
	@echo "\n$(PURPLE)MAKE $(NAME) Start!$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "$(YELLOW)$(NAME): $(notdir $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

make_obj :
	@mkdir -p obj

make_libft :
	@make -C ./libft/

clean :
	@echo "$(YELLOW)Objects Deleted.$(NC)"
	@/bin/rm -rf $(OBJ_PATH)

fclean :	clean
	@echo "$(YELLOW)$(NAME) Deleted.$(NC)"
	@/bin/rm -f $(NAME)

re :	fclean all

rc :
	make -C $(LIBFT_PATH) fclean && make fclean && make