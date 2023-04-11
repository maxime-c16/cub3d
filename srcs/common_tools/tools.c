/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:39:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:51 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_height(int fd)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	skip_to_map(fd);
	while (map->line)
	{
		i = 0;
		while (map->line[i] && (map->line[i] == '\t' || map->line[i] == VOID
				|| map->line[i] == WALL || map->line[i] == '0'))
		{
			if (map->line[i] == '1')
			{
				map->height++;
				break ;
			}
			i++;
		}
		free(map->line);
		map->line = get_next_line(fd);
	}
	close(fd);
	return (map->height);
}

int	calculate_color(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	return ((r << 16) | (g << 8) | b);
}

int	lerp(int a, int b, float t)
{
	int	r;
	int	g;
	int	c;

	r = ((a >> 16) & 0xFF) + (((b >> 16) & 0xFF) - ((a >> 16) & 0xFF)) * t;
	g = ((a >> 8) & 0xFF) + (((b >> 8) & 0xFF) - ((a >> 8) & 0xFF)) * t;
	c = (a & 0xFF) + ((b & 0xFF) - (a & 0xFF)) * t;
	return ((r << 16) | (g << 8) | c);
}
