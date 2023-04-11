/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:27:11 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:08 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	draw_no_pixel_put(int x, int y, int color)
{
	t_mlx	*mlx;

	mlx = _mlx();
	mlx->addr[y * mlx->line_len / 4 + x] = color;
}

static void	draw_wall_ceil_floor(int x, int y)
{
	t_mlx	*mlx;

	mlx = _mlx();
	if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
		draw_no_pixel_put(x, y,
			(int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x]);
	else
		draw_no_pixel_put(x, y, calculate_color(mlx->c_ceiling));
}

static void	draw_wall_textured(int x, int y)
{
	if (y < _map()->height * MMAP_L && x < _map()->width * MMAP_L)
		draw_no_pixel_put(x, y,
			(int)_map()->minimap_addr[y * _map()->minimap_line_len / 4 + x]);
	else
	{
		calculate_y_tex();
		draw_no_pixel_put(x, y, match_color_tex());
	}
	_tex()->tex_pos += _tex()->step;
}

void	draw_wall(int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < start)
			draw_wall_ceil_floor(x, y);
		else if (y >= start && y < end)
			draw_wall_textured(x, y);
		else
			draw_wall_ceil_floor(x, y);
		y++;
	}
}
