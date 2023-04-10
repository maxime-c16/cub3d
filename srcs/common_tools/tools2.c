/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:37:09 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 19:01:43 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calculate_color(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	return ((r << 16) | (g << 8) | b);
}

int calculate_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

void	calculate_y_tex(void)
{
	t_tex	*tex;

	tex = _tex();
	tex->y = (int)tex->tex_pos & (tex->sprite[(int)_dda()->sideHit].height - 1);
	tex->tex_pos += tex->step;
}

// void	match_color_tex(int y)
// {
// 	t_dda		*dda;
// 	t_tex	*tex;

// 	dda = _dda();
// 	tex = _tex();
// 	tex->color = tex->sprite[(int)dda->sideHit].pixels[y][tex->x];
// 	if (dda->side == 1)
// 		tex->color = (tex->color >> 1) & 8355711;
// }

void	match_color_tex(void)
{
	t_dda		*dda;
	t_tex	*tex;

	dda = _dda();
	tex = _tex();
	tex->color = tex->sprite[(int)dda->sideHit].addr[tex->y * tex->sprite[(int)dda->sideHit].width / 4 + tex->x];
	if (dda->side == 1)
		tex->color = (tex->color >> 1) & 8355711;
}

void	sprite_put_pixel(int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = (char *)_mlx()->addr + (y * _mlx()->line_len + x * (_mlx()->bpp / 8));
	*(unsigned int *)dst = color;
}

int	**pick_sprite(void)
{
	t_dda	*dda;
	t_ray	*ray;

	dda = _dda();
	ray = _ray();
	if (dda->side && ray->ray_dir_y > 0)
		return (_tex()->sprite[NORTH].pixels);
	else if (dda->side && ray->ray_dir_y < 0)
		return (_tex()->sprite[SOUTH].pixels);
	else if (!dda->side && ray->ray_dir_x > 0)
		return (_tex()->sprite[WEST].pixels);
	else
		return (_tex()->sprite[EAST].pixels);
}

int lerp(int a, int b, float t)
{
	int	r;
	int	g;
	int	c;

	r = ((a >> 16) & 0xFF) + (((b >> 16) & 0xFF) - ((a >> 16) & 0xFF)) * t;
	g = ((a >> 8) & 0xFF) + (((b >> 8) & 0xFF) - ((a >> 8) & 0xFF)) * t;
	c = (a & 0xFF) + ((b & 0xFF) - (a & 0xFF)) * t;
	return ((r << 16) | (g << 8) | c);
}

void	get_color(double y, int x, int y_tex)
{
	t_ray	*ray;
	t_dda	*dda;
	int		color;
	int		border_distance;

	ray = _ray();
	dda = _dda();
	border_distance = -1;
	_map()->border_size = 3;
	_tex()->x = (int)(ray->wallX * (double)_tex()->sprite[(int)dda->sideHit].width);
	if ((dda->side == NORTH_SOUTH && ray->ray_dir_x > 0) || (dda->side == WEST_EAST && ray->ray_dir_y < 0))
		_tex()->x = _tex()->sprite[(int)dda->sideHit].width - _tex()->x - 1;
	color = pick_sprite()[(int)y][_tex()->x];
	if ((int)y < _map()->border_size)
		border_distance = (int)y;
	else if ((int)y >= _tex()->sprite[(int)dda->sideHit].height - _map()->border_size)
		border_distance = _tex()->sprite[(int)dda->sideHit].height - (int)y - 1;
	if (_tex()->x < _map()->border_size)
	{
		if (_tex()->x < border_distance || border_distance == -1)
			border_distance = _tex()->x;
	}
	else if (_tex()->x >= _tex()->sprite[(int)dda->sideHit].width - _map()->border_size)
	{
		if (_tex()->sprite[(int)dda->sideHit].width - _tex()->x - 1 < border_distance || border_distance == -1)
			border_distance = _tex()->sprite[(int)dda->sideHit].width - _tex()->x - 1;
	}
	// if (border_distance != -1 && _map()->hit_wall_x == dda->mapX && _map()->hit_wall_y == dda->mapY)
	// {
	// 	color = lerp(color,  calculate_rgb(255, 255, 255),
	// 		(float)(_map()->border_size - border_distance) / _map()->border_size);
	// }
	sprite_put_pixel(x, y_tex, color);
}

void	draw_square(int x, int y, int color)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = _map();
	while (j < MMAP_L)
	{
		i = 0;
		while (i < MMAP_L)
		{
			map->minimap_addr[(y + j) * map->minimap_line_len / 4 + (x + i)] = color;
			i++;
		}
		j++;
	}
}
