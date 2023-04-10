/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:51:42 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 19:06:50 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int render_rays(void)
{
	t_dda *dda;
	int x;

	refresh_image();
	dda = _dda();
	x = 0;
	draw_minimap();
	while (x < WIN_WIDTH)
	{
		init_dda(x);
		dda_loop(dda);
		wall_height();
		if (x == WIN_WIDTH / 2)
		{
			_map()->hit_wall_x = dda->mapX;
			_map()->hit_wall_y = dda->mapY;
		}
		draw_wall(x, _ray()->wall.start, _ray()->wall.end);
		x++;
	}
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->win, _mlx()->img, 0, 0);
	return (0);
}


int	key_down(int keycode)
{
	if (keycode == KEY_ESC)
		close_window();
	if (keycode == KEY_W)
		move_forward();
	if (keycode == KEY_S)
		move_backward();
	if (keycode == KEY_A)
		move_left();
	if (keycode == KEY_D)
		move_right();
	if (keycode == KEY_LEFT)
		rotate_left();
	if (keycode == KEY_RIGHT)
		rotate_right();
	return (0);
}

void	hook(void)
{
	t_mlx *ptr;

	ptr = _mlx();
	mlx_hook(ptr->win, ON_KEYDOWN, 1L << 0, key_down, NULL);
	mlx_hook(ptr->win, ON_DESTROY, 0, close_window, NULL);
	mlx_loop_hook(ptr->mlx, render_rays, NULL);
}
