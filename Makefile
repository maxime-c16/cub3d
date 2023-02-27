# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 16:05:45 by mcauchy           #+#    #+#              #
#    Updated: 2023/02/26 14:10:11 by mcauchy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES			=	singleton.c main.c get_map.c tools.c free.c hooks/hooks.c \
					hooks/hooks_utils.c dda/dda.c player.c dda/dda_utils.c\
					dda/ray.c\
					hooks/keyhooks.c hooks/keyhooks_utils.c tools2.c sprites/sprites.c\
					singleton2.c minimap.c tools3.c\

SRC_DIR			=	srcs

DIR_OBJ			=	.objs

LIBFT_DIR		=	libft

SRCS			=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS			=	$(addprefix $(DIR_OBJ)/,$(FILES:.c=.o))

CC				=	clang

CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g3

NAME			=	cub3d

HEADER			=	includes/cub3d.h

MLX				=	mlx

MLX_MAC			=	-Lmlx -framework OpenGL -framework AppKit

MLX_LINUX		=	-Lmlx -lmlx_Linux -lXext -lX11 -lm -lz

TOTAL_FILES		=	$(words $(FILES))

CURRENT_FILE	=	0

all				:	MK_LIBFT $(NAME)
					$(eval CURRENT_FILE=0)

$(NAME)			:	$(OBJS)
					@clear
					@$(CC) $(OBJS) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(LIBFT_DIR)/libft.a  -o $(NAME)
					@echo "cub3d : 100.00% compiled"

$(DIR_OBJ)/%.o	:	$(SRC_DIR)/%.c $(HEADER)
					@mkdir -p $(@D)
					@clear
					@echo "cub3d : compiling $(notdir $<)..."
					@echo "cub3d : $(shell echo "scale=2; $(CURRENT_FILE) / $(TOTAL_FILES) * 100" | bc)% complete"
					@$(eval CURRENT_FILE=$(shell echo "$(CURRENT_FILE) + 1" | bc))
					@$(CC) $(CFLAGS) -Imlx -c $< -o $@

MK_LIBFT	:
				@make -j -C $(LIBFT_DIR)
				@make -j -C $(LIBFT_DIR) bonus
				@echo "cub3d : libft compiled"

clean	:
			@rm -rf $(DIR_OBJ)
			@make clean -C $(LIBFT_DIR)
			@echo "cub3d : clean"

fclean	:	clean
			@rm -f $(NAME)
			@make fclean -C $(LIBFT_DIR)
			@echo "cub3d : fclean"

re	:	fclean all

.PHONY	:	all clean fclean re
