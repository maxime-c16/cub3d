/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:29:01 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 12:15:45 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_dda_1(double posX, double posY, double rayDirX, double rayDirY)
{
	t_dda	*dda;

	dda = _dda();
	dda->mapX = (int)posX;
	dda->mapY = (int)posY;
	if (rayDirX == 0)
		dda->deltaDistX = 1e30;
	else
		dda->deltaDistX = fabs(1 / rayDirX);
	if (rayDirY == 0)
		dda->deltaDistY = 1e30;
	else
		dda->deltaDistY = fabs(1 / rayDirY);
	dda->hit = 0;
}

static void	init_dda_x(double posX, double rayDirX)
{
	t_dda	*dda;

	dda = _dda();
	if (rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (posX - dda->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (dda->mapX + 1.0 - posX) * dda->deltaDistX;
	}
}

static void	init_dda_y(double posY, double rayDirY)
{
	t_dda	*dda;

	dda = _dda();
	if (rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (posY - dda->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (dda->mapY + 1.0 - posY) * dda->deltaDistY;
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
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = NORTH_SOUTH;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = WEST_EAST;
		}
		if (dda->mapX < 0 || dda->mapY < 0 || dda->mapX >= _map()->width
			|| dda->mapY >= _map()->height)
			dda->hit = 1;
		else if (_map()->map[(int)dda->mapY][(int)dda->mapX] == '1')
			dda->hit = 1;
	}
	set_dda_side();
}
