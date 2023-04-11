FILES	=	dda/dda_utils.c \
			dda/dda.c \
			dda/ray.c \
			hooks/hooks_utils.c \
			hooks/hooks.c \
			hooks/keyhooks_utils.c \
			hooks/keyhooks.c \
			sprites/sprites.c \
			parsing/parse_color.c \
			parsing/parse_file.c \
			parsing/parse_map.c \
			parsing/parse_textures.c \
			parsing/parsing.c \
			parsing/tools/parse_check.c \
			parsing/tools/parse_utils.c \
			common_tools/free.c \
			common_tools/handling_error.c \
			common_tools/singleton.c \
			common_tools/singleton2.c \
			common_tools/tools.c \
			common_tools/tools2.c \
			main.c \
			minimap.c \
			player.c \
			
DIR_OBJS = .objs

SRCS_DIR = srcs

SRCS	= $(addprefix $(SRCS_DIR)/,$(FILES))

OBJS	= $(addprefix $(DIR_OBJS)/,$(FILES:.c=.o))

INC		=	includes/cub3d.h

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -g3 -I includes/

MLX		=	mlx_Linux

RM		=	rm -f

NAME	=	cub3d

MLX_MACOS = mlx_macos

MACOS_FLAGS =  -Lmlx_macos -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(INC) 
		 @$(MAKE) -C libft
		 @echo "cub3d : libft compiled"
		 @$(CC) -g $(CFLAGS) -o $(NAME) $(OBJS) $(INC) libft/libft.a -Lmlx -lmlx -lXext -lX11 -lm -lz
		 @echo "cub3d : compiled"

$(MLX):
		@cd mlx && $(MAKE) -f Makefile.gen
		@echo "cub3d : minilibx compiled" 
		

macos:	$(OBJS) $(INC)
		@cd mlx_macos && make
		@echo "cub3d : minilibx_macos compiled"
		@$(MAKE) -C libft
		@echo "cub3d : libft compiled"
		@$(CC) $(OBJS) $(CFLAGS) $(MACOS_FLAGS) libft/libft.a -o $(NAME)
		@echo "cub3d : compiled"
		
$(MLX_MACOS):
		@cd mlx_macos && make
		@echo "cub3d : minilibx_macos compiled"

$(DIR_OBJS)/%.o	:	$(SRCS_DIR)/%.c $(INC)
					@mkdir -p $(@D)
					@echo "cub3d : compiling $(notdir $<)..."
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(MAKE) -C libft clean
		@$(RM) $(OBJS)
		cd mlx && $(MAKE) -f Makefile.gen clean
		cd mlx_macos && make clean
		@echo "cub3d : objects has been erased"

fclean:	clean
		@$(MAKE) -C libft fclean
		@$(RM) $(NAME)
		@echo "cub3d : objects and name has been erased"

re: fclean all

remacos: fclean macos

test_leaks:
	valgrind $(NAME)

.PHONY: bonus all clean fclean re test_leaks
