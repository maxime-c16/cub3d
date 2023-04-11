/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:37:09 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 21:50:005 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int calculate_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

void	calculate_y_tex(void)
{
	t_tex	*tex;

	tex = _tex();
	tex->y = (int)tex->tex_pos & (tex->sprite[(int)_dda()->sideHit].height - 1);
}

int	match_color_tex(void)
{
	t_dda		*dda;
	t_tex	*tex;

	dda = _dda();
	tex = _tex();
	tex->color = tex->sprite[(int)dda->sideHit].addr[
		tex->y * (tex->sprite[(int)dda->sideHit].width / 4) + tex->x];
	// if (dda->side == 1)
	// 	tex->color = (tex->color >> 1) & 8355711;
	return (tex->color);
}

int lerp(int a, int b, float t)
{
	int	r;
	int	g;
	int	c;

	r = ((a >> 16) & 0xFF) + (((b >> 16) & 0xFF) - ((a >> 16) & 0xFF)) * t;
	g = ((a >> 8) & 0xFF) + (((b >> 8) & 0xFF) - ((a >> 8) & 0xFF)) * t;
	c = (a & 0xFF) + ((b & 0xFF) - (a & 0xFF)) * t;
	return ((r << 16) | (g << 8) | c);
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
