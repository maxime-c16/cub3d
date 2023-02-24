SRCS	=	srcs/dda/dda_utils.c \
			srcs/dda/dda.c \
			srcs/dda/ray.c \
			srcs/hooks/hooks_utils.c \
			srcs/hooks/hooks.c \
			srcs/hooks/keyhooks_utils.c \
			srcs/hooks/keyhooks.c \
			srcs/sprites/sprites.c \
			srcs/free.c \
			srcs/get_map.c \
			srcs/handling_error.c \
			srcs/main.c \
			srcs/minimap.c \
			srcs/player.c \
			srcs/singleton.c \
			srcs/singleton2.c \
			srcs/tools.c \
			srcs/tools2.c \

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