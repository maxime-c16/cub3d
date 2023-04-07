/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:32:42 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/31 18:57:11 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int	close_window(void)
{
	hasta_la_vista();
	return (0);
}

void create_wall(void)
{
	int	new_x;
	int	new_y;
	t_map *map;

	map = _map();
	new_x = _player()->x + _player()->dir_x;
	new_y = _player()->y + _player()->dir_y;
	if(map->map[new_y][new_x] != '1')
	{
		map->map[new_y][new_x] = '1';
	}
}

void delete_wall(void)
{
	int		new_x;
	int		new_y;
	t_map	*map;

	map = _map();
	new_x = map->hit_wall_x;
	new_y = map->hit_wall_y;

	if (new_x < map->height && new_y > 0 && new_y < map->width && new_x > 0)
	{
		if (new_y < map->height && new_x < ft_strlen(map->map[new_y]))
		{
			if (map->map[new_y][new_x] == '1')
			{
				map->map[new_y][new_x] = '0';
			}
		}
	}
}
