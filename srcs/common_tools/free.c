/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:34:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/07 19:10:59 by lbisson          ###   ########.fr       */
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

void	destroy_sprites(void *mlx)
{
	t_tex	*tex;

	tex = _tex();
	if (tex->sprite[NORTH].img)
	{
		free(tex->sprite[NORTH].addr);
		mlx_destroy_image(mlx, tex->sprite[NORTH].img);
	}
	if (tex->sprite[SOUTH].img)
	{
		free(tex->sprite[SOUTH].addr);
		mlx_destroy_image(mlx, tex->sprite[SOUTH].img);
	}
	if (tex->sprite[WEST].img)
	{
		free(tex->sprite[WEST].addr);
		mlx_destroy_image(mlx, tex->sprite[WEST].img);
	}
	if (tex->sprite[EAST].img)
	{
		mlx_destroy_image(mlx, tex->sprite[EAST].img);
	}
}

void	destroy_minimap(void *mlx)
{
	t_map	*map;

	map = _map();
	if (map->minimap_img)
	{
		free(map->minimap_addr);
		mlx_destroy_image(mlx, map->minimap_img);
	}
}

void	free_texs(void)
{
	t_tex	*tex;

	tex = _tex();
	free(tex->sprite[NORTH].path);
	free(tex->sprite[NORTH].addr);
	free(tex->sprite[SOUTH].path);
	free(tex->sprite[SOUTH].addr);
	free(tex->sprite[WEST].path);
	free(tex->sprite[WEST].addr);
	free(tex->sprite[EAST].path);
	free(tex->sprite[EAST].addr);
}

void	hasta_la_vista(int status)
{
	t_map	*map;
	t_mlx	*mlx;

	map = _map();
	mlx = _mlx();
	free(map->line);
	free(map->path);
	free_texs();
	if (map->map)
		free_array(map->map);
	if (map->fd)
		close(map->fd);
	if (mlx->mlx)
	{
		destroy_sprites(mlx->mlx);
		if (map->minimap_img)
			destroy_minimap(mlx->mlx);
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	exit(status);
}
