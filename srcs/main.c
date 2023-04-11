/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:35:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 19:36:10 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

static void	init_mlx(void)
{
	t_mlx	*ptr;

	ptr = _mlx();
	ptr->mlx = mlx_init();
	if (ptr->mlx == NULL)
		handling_error("mlx init", NULL);
	ptr->win = mlx_new_window(ptr->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIN_WIDTH, WIN_HEIGHT);
	ptr->addr = (int *)mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->line_len,
			&ptr->endian);
}

static void	init_minimap(void)
{
	t_map	*map;

	map = _map();
	map->minimap_img = mlx_new_image(_mlx()->mlx, map->width * MMAP_L,
			map->height * MMAP_L);
	map->minimap_addr = (int *)mlx_get_data_addr(map->minimap_img,
			&map->minimap_bpp, &map->minimap_line_len, &map->minimap_endian);
}

int	main(int ac, char **av)
{
	parsing(ac, av);
	init_player();
	init_mlx();
	init_minimap();
	init_sprites();
	hook();
	mlx_loop(_mlx()->mlx);
	return (0);
}
