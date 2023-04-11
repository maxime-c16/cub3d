/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:32:42 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:19:04 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	close_window(void)
{
	hasta_la_vista(EXIT_SUCCESS);
	return (0);
}

void	create_wall(void)
{
	int		new_x;
	int		new_y;
	t_map	*map;

	map = _map();
	new_x = _player()->x + _player()->dir_x;
	new_y = _player()->y + _player()->dir_y;
	if (map->map[new_y][new_x] != '1')
		map->map[new_y][new_x] = '1';
}

void	delete_wall(void)
{
	int		new_x;
	int		new_y;
	t_map	*map;

	map = _map();
	new_x = map->hit_wall_x;
	new_y = map->hit_wall_y;
	if (new_x < map->height && new_y > 0 && new_y < map->width && new_x > 0)
		if (new_y < map->height && new_x < ft_strlen(map->map[new_y]))
			if (map->map[new_y][new_x] == '1')
				map->map[new_y][new_x] = '0';
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
	map->minimap_addr
		= (int *)mlx_get_data_addr(map->minimap_img, &map->minimap_bpp,
			&map->minimap_line_len, &map->minimap_endian);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	wall_height(void)
{
	t_ray	*ray;
	t_dda	*dda;

	ray = _ray();
	dda = _dda();
	if (dda->side == NORTH_SOUTH)
		ray->wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		ray->wall_dist = dda->side_dist_y - dda->delta_dist_y;
	ray->wall.height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->wall.start = -ray->wall.height / 2 + WIN_HEIGHT / 2;
	if (ray->wall.start < 0)
		ray->wall.start = 0;
	ray->wall.end = ray->wall.height / 2 + WIN_HEIGHT / 2;
	if (ray->wall.end >= WIN_HEIGHT)
		ray->wall.end = WIN_HEIGHT - 1;
}
