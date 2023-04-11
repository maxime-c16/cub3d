/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:31:23 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 21:37:209 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_print_map(void)
{
	t_map	*map;
	int		i;

	map = _map();
	i = 0;
	dprintf(1, "printing map\n");
	while (i < map->height)
	{
		dprintf(1, "%d\t%s\n", i, map->map[i]);
		i++;
	}
}

int	get_height(int fd)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	skip_to_map(fd);
	while (map->line)
	{
		i = 0;
		while (map->line[i] && (map->line[i] == '\t' || map->line[i] == VOID
				|| map->line[i] == WALL || map->line[i] == '0'))
		{
			if (map->line[i] == '1')
			{
				map->height++;
				break ;
			}
			i++;
		}
		free(map->line);
		map->line = get_next_line(fd);
	}
	close(fd);
	return (map->height);
}

void	wall_height(void)
{
	t_ray	*ray;
	t_dda	*dda;

	ray = _ray();
	dda = _dda();
	if (dda->side == NORTH_SOUTH)
		ray->wallDist = dda->sideDistX - dda->deltaDistX;
	else
		ray->wallDist = dda->sideDistY - dda->deltaDistY;
	ray->wall.height = (int)(WIN_HEIGHT / ray->wallDist);
	ray->wall.start = -ray->wall.height / 2 + WIN_HEIGHT / 2;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + WIN_HEIGHT / 2;
	if (ray->wall.end >= WIN_HEIGHT)
		ray->wall.end = WIN_HEIGHT - 1;
}


void draw_minimap_on_top(int x)
{
	t_mlx	*mlx;
	int		y;

	mlx = _mlx();

	for (y = 0; y < _map()->height * MMAP_L; y++)
	{
		if (x < _map()->width * MMAP_L)
			mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
	}
}

static void	draw_no_pixel_put(int x, int y, int color)
{
	t_mlx	*mlx;

	mlx = _mlx();
	mlx->addr[y * mlx->line_len / 4 + x] = color;
}

void draw_wall(int x, int start, int end)
{
	t_mlx	*mlx;
	int		y;

	y = 0;
	mlx = _mlx();
	while (y < WIN_HEIGHT)
	{
		if (y < start)
		{
			if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
				draw_no_pixel_put(x, y,
					(int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x]);
			else
				draw_no_pixel_put(x, y, calculate_color(mlx->c_ceiling));
		}
		else if (y >= start && y < end)
		{
			if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
				draw_no_pixel_put(x, y,
					(int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x]);
			else
			{
				calculate_y_tex();
				draw_no_pixel_put(x, y, match_color_tex());
			}
			_tex()->tex_pos += _tex()->step;
		}
		else
			draw_no_pixel_put(x, y, calculate_color(mlx->c_floor));
		y++;
	}
}

// void	draw_wall(int x, int start, int end)
// {
// 	t_mlx	*mlx;
// 	int		y;

// 	y = 0;
// 	mlx = _mlx();
// 	while (y < start)
// 	{
// 		if (y < _map()->height * MMAP_L
// 			&& x < _map()->width * MMAP_L)
// 			mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
// 		else
// 			mlx->addr[y * mlx->line_len / 4 + x] = calculate_color(mlx->c_ceiling);
// 		y++;
// 	}
// 	while (y < end)
// 	{
// 		calculate_y_tex();
// 		match_color_tex();
// 		if (y < _map()->height * MMAP_L
// 			&& x < _map()->width * MMAP_L)
// 			mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
// 		else
// 			mlx->addr[y * mlx->line_len / 4 + x] = _tex()->color;
// 		y++;
// 	}
// 	while (y < WIN_HEIGHT)
// 	{
// 		if (y < _map()->height * MMAP_L
// 			&& x < _map()->width * MMAP_L)
// 			mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
// 		else
// 			mlx->addr[y * mlx->line_len / 4 + x] = calculate_color(mlx->c_floor);
// 		y++;
// 	}
// }

void	refresh_image(void)
{
	t_mlx	*mlx;
	t_map	*map;

	mlx = _mlx();
	map = _map();
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, map->minimap_img);
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	map->minimap_img = mlx_new_image(mlx->mlx, map->width * MMAP_L,
		map->height * MMAP_L);
	mlx->addr = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
	map->minimap_addr = (int *)mlx_get_data_addr(map->minimap_img, &map->minimap_bpp,
			&map->minimap_line_len, &map->minimap_endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
