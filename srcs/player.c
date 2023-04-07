/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:31:26 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 19:22:12 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	get_player_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'S')
		return (3 * M_PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (M_PI);
	return (0);
}

static void	setPlayer(double x, double y, double angle)
{
	t_player	*player;

	player = _player();
	player->x = x;
	player->y = y;
	player->dir_x = cos(angle);
	player->dir_y = sin(angle);
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->angle = angle;
	player->fov = M_PI / 3;
	player->speed = 0.1;
	player->rot_speed = M_PI / 80;
}

void	get_player_data(void)
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
				setPlayer(j + 0.5, i + 0.5, get_player_angle(map->map[i][j]));
				return ;
			}
			j++;
		}
		i++;
	}
}
