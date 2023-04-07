/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:32:42 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 19:42:48 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

int	close_window(void)
{
	hasta_la_vista(EXIT_SUCCESS);
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

void	delete_wall(void)
{
	int	new_x;
	int	new_y;
	t_map *map;

	map = _map();
	new_x = _player()->x + _player()->dir_x;
	new_y = _player()->y + _player()->dir_y;
	if (new_x < map->height && new_y > 0 && new_y < ft_strlen(map->map[new_x]) && new_x > 0)
	{
		if(map->map[new_y][new_x] == '1')
		{
			map->map[new_y][new_x] = '0';
		}
	}
}
