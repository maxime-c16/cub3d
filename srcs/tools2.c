/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:37:09 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/26 13:19:24 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calculate_rgb(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = color.r;
	g = color.g;
	b = color.b;
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int calculate_trgb(int t, int r, int g, int b)
{
	return (((t & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	calculate_y_tex(void)
{
	t_tex	*tex;
	t_dda		*dda;

	tex = _tex();
	dda = _dda();
	if (dda->sideHit == NORTH)
		tex->y = (int)tex->tex_pos & (tex->north.height - 1);
	else if (dda->sideHit == SOUTH)
		tex->y = (int)tex->tex_pos & (tex->south.height - 1);
	else if (dda->sideHit == WEST)
		tex->y = (int)tex->tex_pos & (tex->west.height - 1);
	else if (dda->sideHit == EAST)
		tex->y = (int)tex->tex_pos & (tex->east.height - 1);
	tex->tex_pos += tex->step;
}

void	match_color_tex(void)
{
	t_dda		*dda;
	t_tex	*tex;

	dda = _dda();
	tex = _tex();
	if (dda->sideHit == NORTH)
		tex->color = tex->north.addr[tex->y * tex->north.height / 4 + tex->x];
	else if (dda->sideHit == SOUTH)
		tex->color = tex->south.addr[tex->y * tex->south.height / 4 + tex->x];
	else if (dda->sideHit == WEST)
		tex->color = tex->west.addr[tex->y * tex->west.height / 4 + tex->x];
	else if (dda->sideHit == EAST)
		tex->color = tex->east.addr[tex->y * tex->east.height / 4 + tex->x];
}

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
			map->minimap_addr[(y + j) * map->minimap_line_len / 4 + (x + i)] = color;
			i++;
		}
		j++;
	}
}
