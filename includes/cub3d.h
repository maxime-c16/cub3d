/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:37:07 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 16:56:055 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "../mlx/mlx.h"
# include "../mlx_macos/mlx.h"

# ifndef M_PI
#  define M_PI 3.141592653
# endif

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_E 101
#  define KEY_R 114
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363

# elif __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_E 14
#  define KEY_R 15
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124

# endif

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MIN_DIST 0.1
# define MMAP_L WIN_WIDTH / 108
# define MINI_FOV 15

# define WALL '1'
# define VOID ' '

# define NORTH_SOUTH 0
# define WEST_EAST 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

# define ENEMY_IDLE 0
# define ENEMY_WALK 1
# define ENEMY_ATTACK 2
# define NUM_IDLE_FRAMES 4
# define NUM_WALK_FRAMES 2
# define ENEMY_SPEED 0.05

typedef enum	e_enemy_direction
{
	ENEMY_NORTH,
	ENEMY_SOUTH,
	ENEMY_WEST,
	ENEMY_EAST
}				t_enemy_direction;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	int		filled;
}				t_color;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		flag;
	t_color	c_floor;
	t_color	c_ceiling;
}				t_mlx;

typedef struct s_fov
{
	int		prev_dir_x;
	int		prev_dir_y;
	int		new_x;
	int		new_y;
	float	rotation;
} t_fov;

typedef struct s_map
{
	int		fd;
	int		width;
	int		height;
	int		border_size;
	int		border_color;
	int		hit_wall_x;
	int		hit_wall_y;
	int		minimap_bpp;
	int		minimap_endian;
	int		minimap_line_len;
	int		*minimap_addr;
	double	minimap_scale;
	char	*line;
	char	*path;
	char	**map;
	void	*minimap_img;
	t_fov	fov;
} t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	angle;
	double	fov;
	double	speed;
	double	rot_speed;
} t_player;

typedef struct	s_wall
{
	int		height;
	int		start;
	int		end;
}				t_wall;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wallDist;
	double	wallX;
	t_wall	wall;

} t_ray;

typedef struct s_dda
{
	double	mapX;
	double	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	stepX;
	double	stepY;
	double	hit;
	double	side;
	double	sideHit;
} t_dda;

typedef struct	s_sprite
{
	char	*path;
	int		*addr;
	void	*img;
	int		bpp;
	int		width;
	int		height;
	int		line_len;
	int		endian;
}				t_sprite;

typedef struct	s_tex
{
	t_sprite	sprite[4];
	int			x;
	int			y;
	int			sideHit;
	int			color;
	double		step;
	double		tex_pos;
}				t_tex;

typedef struct	s_enemy
{
	double				x;
	double				y;
	double				animation_speed;
	double				animation_timer;
	int					animation_state;
	int					animation_frame;
	t_enemy_direction	direction;
	t_sprite			walking[4][9];
}				t_enemy;

//singleton

t_mlx		*_mlx(void);
t_map		*_map(void);
t_player	*_player(void);
t_dda		*_dda(void);
t_ray		*_ray(void);
t_tex		*_tex(void);
t_enemy		*_enemy(void);

//tools

void	ft_print_map(void);
int		get_height(int fd);
void	wall_height(void);
void	draw_wall(int x, int start, int end);
void	refresh_image(void);
int		calculate_color(t_color color);
int		calculate_rgb(unsigned char r, unsigned char g, unsigned char b);
void	calculate_y_tex(void);
int		match_color_tex(void);
void	draw_square(int x, int y, int color);

//parsing

int		skip_space(char *line);
int 	is_empty_line(char *line);
int		is_game_param(char *line);
int 	check_param_filled(void);
void	check_invalid_char(char *line);
void	check_map_closed(void);
void	check_nb_player(void);
void	open_file(char **av);
void 	skip_to_map(int fd);
void	parsing(char **av);
void	parse_map(char **av);
void	parse_file(char **av);
void	parse_tex_north(char *line);
void	parse_tex_south(char *line);
void	parse_tex_west(char *line);
void	parse_tex_east(char *line);
void	parse_color(char *line, t_color *color);

//free

void	free_array(char **array);
void	hasta_la_vista(int status);
void	handling_error(char *error_msg, char *arg);

//render

void	render_map(t_mlx *ptr);

//raycasting

void	get_player_data(void);

//dda

void	init_dda(int w);
void	dda_loop(t_dda *dda);
void	set_dda_side(void);
void	init_ray(t_ray *ray, int x);
int		render_rays(void);

//hooks

void	hook(void);
void	rotate_left(void);
void	rotate_right(void);
void	move_forward(void);
void	move_backward(void);
void	move_left(void);
void	move_right(void);
void 	create_wall(void);
void	delete_wall(void);
int		check_wall(double x, double y);
int		close_window(void);

//sprites

void	load_sprites(void);
void	calculate_sprite(void);
void	get_color(double y, int x, int y_tex);
void	sprite_put_pixel(int x, int y, int color);

//minimap

void	draw_minimap(void);
void	highlight_block_border(void);

//enemy

void	update_enemy_direction(void);
void	update_enemy_animation(void);
void	move_enemy_towards_player(void);
void	spawn_enemy_opposite_player(void);
void	draw_enemy_sprite(void);
void	load_walk(void);
void	draw_enemy_sprite(void);

#endif
