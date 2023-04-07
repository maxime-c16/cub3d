/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:31:23 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/31 17:06:13 by mcauchy          ###   ########.fr       */
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
	char	*line;
	int		height;
	int		i;

	height = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '1'))
		{
			if (line[i] == '1')
			{
				height++;
				break ;
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

void wall_height(void)
{
	t_ray *ray;
	t_dda *dda;

	ray = _ray();
	dda = _dda();

	// Calculate the correct perpendicular wall distance
	if (dda->side == NORTH_SOUTH)
		dda->perpWallDist = dda->sideDistX - dda->deltaDistX;
	else
		dda->perpWallDist = dda->sideDistY - dda->deltaDistY;

	// Calculate the correct wall height
	ray->wall.height = (int)(WIN_HEIGHT / 1.5) / dda->perpWallDist;

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

void draw_wall(int x, int start, int end)
{
	t_mlx	*mlx;
	double	j;
	int		y;

	y = 0;
	mlx = _mlx();
	_tex()->step = 1.0 * _tex()->sprite[(int)_dda()->sideHit].width / _ray()->wall.height;
	j = (_tex()->step * (start - (WIN_HEIGHT / 2) + (_ray()->wall.height / 2)));
	while (y < WIN_HEIGHT)
	{
		if (y < start)
		{
			if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
				mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
			else
				mlx->addr[y * mlx->line_len / 4 + x] = calculate_color(mlx->c_ceiling);
		}
		else if (y >= start && y < end)
		{
			if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
				mlx->addr[y * mlx->line_len / 4 + x] = (int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x];
			else
				mlx->addr[y * mlx->line_len / 4 + x] = get_color(j);
			j += _tex()->step;
		}
		else
			mlx->addr[y * mlx->line_len / 4 + x] = calculate_color(mlx->c_floor);
		y++;
	}
}


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
