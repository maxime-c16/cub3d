/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:35:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/08 19:08:31 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_mlx *ptr = _mlx();

	if (argc != 2)
		handling_error("wrong number of arguments", NULL);
	parsing(argv);
	get_player_data();
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIN_WIDTH, WIN_HEIGHT);
	_map()->minimap_img = mlx_new_image(_mlx()->mlx, _map()->width * MMAP_L,
		_map()->height * MMAP_L);
	ptr->addr = (int *)mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->line_len, &ptr->endian);
	load_sprites();
	_map()->minimap_addr = (int *)mlx_get_data_addr(_map()->minimap_img, &_map()->minimap_bpp,
		&_map()->minimap_line_len, &_map()->minimap_endian);
	hook();
	mlx_loop(ptr->mlx);
	return (0);
}
