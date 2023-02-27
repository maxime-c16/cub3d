/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:33:47 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/26 14:16:31 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	trgb(int t, int r, int g, int b)
{
	return (((t & 0xff) << 24) + ((r & 0xff) << 16)
		+ ((g & 0xff) << 8) + (b & 0xff));
}

void	draw_line(int x, int y, int x2, int y2)
{
	int	delta_x;
	int	delta_y;
	int	sign_x;
	int	sign_y;
	int	error;

	delta_x = abs(x2 - x);
	delta_y = abs(y2 - y);
	if (x < x2)
		sign_x = 1;
	else
		sign_x = -1;
	if (y < y2)
		sign_y = 1;
	else
		sign_y = -1;
	error = delta_x - delta_y;
	_mlx()->addr[x + y * _mlx()->line_len / 4] = 0xFFFFFF;
	while (x != x2 || y != y2)
	{
		_mlx()->addr[x + y * _mlx()->line_len / 4] = 0xFFFFFF;
		if (error * 2 > -delta_y)
		{
			error -= delta_y;
			x += sign_x;
		}
		if (error * 2 < delta_x)
		{
			error += delta_x;
			y += sign_y;
		}
	}
}

void	draw_fov(int x, int y)
{
	int		j;
	int		i;
	t_map	*map;

	map = _map();
	j = 0;
	i = 0;
	x += MMAP_L / 2;
	y += MMAP_L / 2;
	map->fov.prev_dir_x = _player()->dir_x;
	map->fov.prev_dir_y = _player()->dir_y;
	while (j < MINI_FOV)
	{
		i = 0;
		while (i < MINI_FOV - j)
		{
			map->fov.rotation = atan2(_player()->dir_y - map->fov.prev_dir_y, _player()->dir_x - map->fov.prev_dir_x);
			map->fov.new_x = x + i*cos(map->fov.rotation) - j*sin(map->fov.rotation);
			map->fov.new_y = y + i*sin(map->fov.rotation) + j*cos(map->fov.rotation);
			map->minimap_addr[map->fov.new_y * map->minimap_line_len / 4 + map->fov.new_x] = rgb(255, 0, 0);
			i++;
		}
		j++;
	}
}

void	draw_circle(int x, int y)
{
	int i;
	int j;
	int	color;

	i = 0;
	j = 0;
	color = rgb(255, 0, 0);
	while (j < MMAP_L)
	{
		i = 0;
		while (i < MMAP_L)
		{
			if (sqrt(pow(i - MMAP_L / 2, 2) + pow(j - MMAP_L / 2, 2)) < MMAP_L / 2)
				_map()->minimap_addr[(y + j) * _map()->minimap_line_len
					/ 4 + x + i] = color;
			else
				_map()->minimap_addr[(y + j) * _map()->minimap_line_len
					/ 4 + x + i] = calculate_rgb(_mlx()->c_floor);
			i++;
		}
		j++;
	}
}

void	highlight_block_border(void)
{
	int	x;
	int	y;
	int	x2;
	int	y2;

	x = (int)(_player()->x + _player()->dir_x);
	y = (int)(_player()->y + _player()->dir_y);
	x2 = x + 1;
	y2 = y;
	draw_line(x, y, x2, y2);
	x2 = x;
	y2 = y + 1;
	draw_line(x, y, x2, y2);
	x2 = x;
	y2 = y + 1;
	draw_line(x, y, x2, y2);
	x2 = x + 1;
	y2 = y;
	draw_line(x, y, x2, y2);
}

void	draw_minimap(void)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	j = 0;
	map = _map();
	while (j < map->height)
	{
		i = 0;
		while (i < ft_strlen(map->map[j]))
		{
			if (i == (int)_player()->x && j == (int)_player()->y)
				draw_circle(i * MMAP_L, j * MMAP_L);
			else if (map->map[j][i] == '1')
				draw_square(i * MMAP_L, j * MMAP_L, rgb(200, 0, 200));
			else if (map->map[j][i] != ' ')
				draw_square(i * MMAP_L,
					j * MMAP_L, calculate_rgb(_mlx()->c_floor));
			i++;
		}
		j++;
	}
	draw_fov((int)_player()->x * MMAP_L, (int)_player()->y * MMAP_L);
}
