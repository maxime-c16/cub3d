SRCS	=	srcs/dda/dda_utils.c \
			srcs/dda/dda.c \
			srcs/dda/ray.c \
			srcs/hooks/hooks_utils.c \
			srcs/hooks/hooks.c \
			srcs/hooks/keyhooks_utils.c \
			srcs/hooks/keyhooks.c \
			srcs/sprites/sprites.c \
			srcs/parsing/parse_color.c \
			srcs/parsing/parse_file.c \
			srcs/parsing/parse_map.c \
			srcs/parsing/parse_textures.c \
			srcs/parsing/parsing.c \
			srcs/parsing/tools/parse_check.c \
			srcs/parsing/tools/parse_utils.c \
			srcs/common_tools/free.c \
			srcs/common_tools/handling_error.c \
			srcs/common_tools/singleton.c \
			srcs/common_tools/singleton2.c \
			srcs/common_tools/tools.c \
			srcs/common_tools/tools2.c \
			srcs/main.c \
			srcs/minimap.c \
			srcs/player.c \

INC		=	includes/cub3d.h

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g3 -I includes/

MLX		=	mlx_Linux

OBJS	=	$(SRCS:.c=.o)

RM		=	rm -f

NAME	=	cub3d

MLX_MACOS =  -Lmlx -framework OpenGL -framework AppKit

# .c.o:
# 	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(INC) 
		 @$(MAKE) -C libft
		 @echo "cub3d : libft compiled"
		 $(CC) -g $(CFLAGS) -o $(NAME) $(OBJS) $(INC) libft/libft.a -Lmlx -lmlx -lXext -lX11 -lm -lz
		 @echo "cub3d : compiled"

$(MLX):
		cd mlx && ./configure
		@echo "cub3d : minilibx compiled" 

macos:  $(OBJS)
		$(MAKE) -C libft
		@echo "cub3d : libft compiled"
		@$(CC) $(MLX_MACOS) $(CFLAGS) $^ mlx_macos/libmlx.a libft/libft.a -o $(NAME)
		@echo "cub3d : compiled"
	
libft: 
		

clean:
		@$(MAKE) -C libft clean
		@$(RM) $(OBJS)
		cd mlx && ./configure clean
		@echo "cub3d : objects has been erased"

fclean:	clean
		@$(MAKE) -C libft fclean
		@$(RM) $(NAME)
		@echo "cub3d : objects and name has been erased"

re: fclean all

test_leaks:
	valgrind $(NAME)

.PHONY: bonus all clean fclean re test_leaks