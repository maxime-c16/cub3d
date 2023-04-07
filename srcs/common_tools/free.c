/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:34:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 22:36:38 by lbisson          ###   ########.fr       */
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
	t_texture	*tex;

	tex = _texture();
	if (tex->north.img)
	{
		free(tex->north.addr);
		mlx_destroy_image(mlx, tex->north.img);
	}
	if (tex->south.img)
	{
		free(tex->south.addr);
		mlx_destroy_image(mlx, tex->south.img);
	}
	if (tex->west.img)
	{
		free(tex->west.addr);
		mlx_destroy_image(mlx, tex->west.img);
	}
	if (tex->east.img)
	{
		mlx_destroy_image(mlx, tex->east.img);
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

void	free_textures(void)
{
	t_texture	*tex;

	tex = _texture();
	free(tex->north.path);
	free(tex->north.addr);
	free(tex->south.path);
	free(tex->south.addr);
	free(tex->west.path);
	free(tex->west.addr);
	free(tex->east.path);
	free(tex->east.addr);
}

void	hasta_la_vista(int status)
{
	t_map	*map;
	t_mlx	*mlx;

	map = _map();
	mlx = _mlx();
	free(map->line);
	free(map->path);
	free_textures();
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
