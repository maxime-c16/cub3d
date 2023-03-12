/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:37:07 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/06 18:08:00 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//mon papa  a vu ce programme qui sappelle cub3d et il ma dit que cest un truc de fou@

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

# define SUCCESS 1
# define FAILURE -1

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define MIN_DIST 0.1
# define MMAP_L 10
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

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_color	c_floor;
	t_color	c_ceiling;
} t_mlx;

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
	int		minimap_bpp;
	int		minimap_endian;
	int		minimap_line_len;
	int		*minimap_addr;
	double	minimap_scale;
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
	double	perpWallDist;
	double	stepX;
	double	stepY;
	double	hit;
	double	side;
	double	sideHit;
} t_dda;

typedef struct	s_sprite
{
	char	*path;
	void	*img;
	int		*addr;
	int		bpp;
	int		width;
	int		height;
	int		endian;
}				t_sprite;

typedef struct	s_texture
{
	t_sprite	north;
	t_sprite	south;
	t_sprite	west;
	t_sprite	east;
	int			x;
	int			y;
	int			direction;
	int			color;
	double		step;
	double		tex_pos;
}				t_texture;

//singleton

t_mlx		*_mlx(void);
t_map		*_map(void);
t_player	*_player(void);
t_dda		*_dda(void);
t_ray		*_ray(void);
t_texture	*_texture(void);

//tools

void	ft_print_map(void);
int		get_height(int fd);
void	wall_height(void);
void	draw_wall(int x, int start, int end);
void	refresh_image(void);
int		calculate_rgb(t_color color);
int 	calculate_trgb(int t, int r, int g, int b);
void	calculate_y_texture(void);
void	match_color_tex(void);
void	draw_square(int x, int y, int color);

//map

void	get_map(char **av);

//free

void	free_array(char **array);
void	hasta_la_vista(void);
void	handling_error(char *error_msg);

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

//minimap

void	draw_minimap(void);
void	highlight_block_border(void);

#endif
