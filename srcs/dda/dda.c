/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:01 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/12 18:07:05 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_dda_1(double posX, double posY, double rayDirX, double rayDirY)
{
	t_dda	*dda;

	dda = _dda();
	dda->map_x = (int)posX;
	dda->map_y = (int)posY;
	if (rayDirX == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / rayDirX);
	if (rayDirY == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / rayDirY);
	dda->hit = 0;
}

static void	init_dda_x(double posX, double rayDirX)
{
	t_dda	*dda;

	dda = _dda();
	if (rayDirX < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (posX - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - posX)
			* dda->delta_dist_x;
	}
}

static void	init_dda_y(double posY, double rayDirY)
{
	t_dda	*dda;

	dda = _dda();
	if (rayDirY < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (posY - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - posY)
			* dda->delta_dist_y;
	}
}

void	init_dda(int w)
{
	t_ray		*ray;
	t_player	*player;

	ray = _ray();
	player = _player();
	init_ray(ray, w);
	init_dda_1(player->x, player->y, ray->ray_dir_x, ray->ray_dir_y);
	init_dda_x(player->x, ray->ray_dir_x);
	init_dda_y(player->y, ray->ray_dir_y);
}

void	dda_loop(t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side = NORTH_SOUTH;
			dda->map_x += dda->step_x;
			dda->side_dist_x += dda->delta_dist_x;
		}
		else
		{
			dda->side = WEST_EAST;
			dda->map_y += dda->step_y;
			dda->side_dist_y += dda->delta_dist_y;
		}
		if (_map()->map[(int)dda->map_y][(int)dda->map_x] == '1')
			dda->hit = 1;
	}
	set_dda_side();
}
