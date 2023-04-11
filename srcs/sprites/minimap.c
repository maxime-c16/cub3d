/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:33:47 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:08 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	trgb(int t, int r, int g, int b)
{
	return (((t & 0xff) << 24) + ((r & 0xff) << 16)
		+ ((g & 0xff) << 8) + (b & 0xff));
}

void	draw_fov(int x, int y)
{
	int		i;
	t_map	*map;

	map = _map();
	i = 0;
	x += MMAP_L / 2;
	y += MMAP_L / 2;
	map->fov.prev_dir_x = _player()->dir_x;
	map->fov.prev_dir_y = _player()->dir_y;
	while (i < MINI_FOV)
	{
		map->fov.rotation = atan2(_player()->dir_y - map->fov.prev_dir_y,
				_player()->dir_x - map->fov.prev_dir_x);
		map->fov.new_x = x + i * cos(map->fov.rotation);
		map->fov.new_y = y + i * sin(map->fov.rotation);
		map->minimap_addr[map->fov.new_y * map->minimap_line_len / 4
			+ map->fov.new_x] = rgb(255, 0, 0);
		i++;
	}
}

void	draw_circle(int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = rgb(255, 0, 0);
	while (j < MMAP_L)
	{
		i = 0;
		while (i < MMAP_L)
		{
			if (sqrt(pow(i - MMAP_L / 2, 2)
					+ pow(j - MMAP_L / 2, 2)) < MMAP_L / 2)
				_map()->minimap_addr[(y + j) * _map()->minimap_line_len
				/ 4 + x + i] = color;
			else
				_map()->minimap_addr[(y + j) * _map()->minimap_line_len
				/ 4 + x + i] = calculate_color(_mlx()->c_floor);
			i++;
		}
		j++;
	}
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
			if (map->map[j][i] == '1')
				draw_square(i * MMAP_L, j * MMAP_L, rgb(55, 57, 59));
			else if (map->map[j][i] != ' ')
				draw_square(i * MMAP_L,
					j * MMAP_L, calculate_color(_mlx()->c_floor));
			i++;
		}
		j++;
	}
	draw_circle((int)_player()->x * MMAP_L, (int)_player()->y * MMAP_L);
}
