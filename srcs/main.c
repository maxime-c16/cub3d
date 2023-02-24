/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:35:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/24 18:25:12 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	// Initialize variables and create window
	t_mlx *ptr = _mlx();
	// t_map *map = _map();

	if (argc != 2)
	{
		dprintf(2, "Error\nWrong number of arguments\n");
		exit(1);
	}
	printf("1\n");
	get_map(argv);
	printf("2\n");
	// map->path = ft_strdup(argv[1]);
	// map->fd = open(map->path, O_RDONLY);
	// map->height = get_height(map->fd);
	// map->map = ft_calloc(map->height, sizeof(char *));
	// parse_map(map->fd);
	printf("3\n");
	get_player_data();
	printf("4\n");
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIN_WIDTH, WIN_HEIGHT);
	printf("5\n");
	_map()->minimap_img = mlx_new_image(_mlx()->mlx, _map()->width * MMAP_L,
		_map()->height * MMAP_L);
	printf("6\n");
	ptr->addr = (int *)mlx_get_data_addr(ptr->img, &ptr->bpp, &ptr->line_len, &ptr->endian);
	printf("7\n");
	load_sprites();
	printf("8\n");
	_map()->minimap_addr = (int *)mlx_get_data_addr(_map()->minimap_img, &_map()->minimap_bpp,
		&_map()->minimap_line_len, &_map()->minimap_endian);
	printf("9\n");
	// Hook close event and start main loop
	hook();
	printf("10\n");
	mlx_loop(ptr->mlx);
	printf("11\n");
	return (0);
}
