/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:34:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/01/21 16:05:53 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hasta_la_vista(void)
{
	t_map	*map;
	t_mlx	*mlx;

	map = _map();
	if (map->map)
	{
		while (map->height--)
			free(map->map[map->height]);
		free(map->map);
	}
	if (map->fd)
		close(map->fd);
	mlx = _mlx();
	if (mlx->mlx)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		free(mlx->mlx);
	}
	exit(0);
}
