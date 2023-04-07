/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:34:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/07 20:12:14 by lbisson          ###   ########.fr       */
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

void	free_pixels(int size, int **pixels)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(pixels[i]);
		i++;
	}
	free(pixels);
}

void	destroy_minimap(void *mlx)
{
	t_map	*map;

	map = _map();
	if (map->minimap_img)
		mlx_destroy_image(mlx, map->minimap_img);
}

void	free_texs(void)
{
	int		i;
	t_tex	*tex;
	t_mlx	*mlx;

	i = 0;
	tex = _tex();
	mlx = _mlx();
	while (i < 4)
	{	
		free(tex->sprite[i].path);
		free_pixels(tex->sprite[i].height, tex->sprite[i].pixels);
		if (mlx->mlx && tex->sprite[i].img)
			mlx_destroy_image(mlx->mlx, tex->sprite[i].img);
		i++;
	}
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
		if (map->minimap_img)
			destroy_minimap(mlx->mlx);
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	exit(status);
}
