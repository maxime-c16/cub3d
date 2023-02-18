/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:34:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/10 17:58:44 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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
		free_array(map->split);
		// free_array(map->map);
		free(map->path);
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
	exit(EXIT_SUCCESS);
}
