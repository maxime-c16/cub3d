/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:31:26 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:08 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_angle(double dir_x, double dir_y, double p_x, double p_y)
{
	t_player	*player;

	player = _player();
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	player->plane_x = p_x;
	player->plane_y = p_y;
}

static void	get_player_angle(char c)
{
	if (c == 'N')
		set_player_angle(0, -1, 0.66, 0);
	else if (c == 'S')
		set_player_angle(0, 1, -0.66, 0);
	else if (c == 'E')
		set_player_angle(1, 0, 0, 0.66);
	else if (c == 'W')
		set_player_angle(-1, 0, 0, -0.66);
}

static void	set_player(double x, double y)
{
	t_player	*player;

	player = _player();
	player->x = x;
	player->y = y;
	player->fov = M_PI / 3;
	player->speed = 0.07;
	player->rot_speed = -M_PI / 80;
}

void	init_player(void)
{
	t_map		*map;
	int			i;
	int			j;

	i = 0;
	map = _map();
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				get_player_angle(map->map[i][j]);
				set_player(j + 0.5, i + 0.5);
				map->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
