/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:53:41 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:00 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	draw_square(int x, int y, int color)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = _map();
	while (j < MMAP_L)
	{
		i = 0;
		while (i < MMAP_L)
		{
			map->minimap_addr[(y + j)
				* map->minimap_line_len / 4 + (x + i)] = color;
			i++;
		}
		j++;
	}
}
