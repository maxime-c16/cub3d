/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:51 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/26 14:18:53 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_sprites(void)
{
	t_tex	*tex;

	tex = _tex();
	tex->north.img = mlx_xpm_file_to_image(_mlx()->mlx, tex->north.path, &tex->north.width, &tex->north.height);
	tex->south.img = mlx_xpm_file_to_image(_mlx()->mlx, tex->south.path, &tex->south.width, &tex->south.height);
	tex->east.img = mlx_xpm_file_to_image(_mlx()->mlx, tex->east.path, &tex->east.width, &tex->east.height);
	tex->west.img = mlx_xpm_file_to_image(_mlx()->mlx, tex->west.path, &tex->west.width, &tex->west.height);
	if (!tex->north.img || !tex->south.img || !tex->east.img || !tex->west.img)
		hasta_la_vista();
	tex->north.addr = (int *)mlx_get_data_addr(tex->north.img, &tex->north.bpp, &tex->north.width, &tex->north.endian);
	tex->south.addr = (int *)mlx_get_data_addr(tex->south.img, &tex->south.bpp, &tex->south.width, &tex->south.endian);
	tex->east.addr = (int *)mlx_get_data_addr(tex->east.img, &tex->east.bpp, &tex->east.width, &tex->east.endian);
	tex->west.addr = (int *)mlx_get_data_addr(tex->west.img, &tex->west.bpp, &tex->west.width, &tex->west.endian);
	if (!tex->north.addr || !tex->south.addr || !tex->east.addr || !tex->west.addr)
		hasta_la_vista();
}

static void	calculate_new_wall_x(t_dda *dda)
{
	t_ray		*ray;
	t_player	*player;

	ray = _ray();
	player = _player();
	if (dda->sideHit == NORTH_SOUTH)
		ray->wallX = player->y + (dda->perpWallDist * ray->ray_dir_y);
	else
		ray->wallX = player->x + (dda->perpWallDist * ray->ray_dir_x);
	ray->wallX -= floor(ray->wallX);
}

void	step_wall(void)
{
	t_ray		*ray;
	t_tex	*tex;

	ray = _ray();
	tex = _tex();
	if (_dda()->sideHit == NORTH)
		tex->step = 1.0 * tex->north.height / ray->wall.height;
	else if (_dda()->sideHit == SOUTH)
		tex->step = 1.0 * tex->south.height / ray->wall.height;
	else if (_dda()->sideHit == EAST)
		tex->step = 1.0 * tex->east.height / ray->wall.height;
	else
		tex->step = 1.0 * tex->west.height / ray->wall.height;
	tex->step /= 4;
}

void	calculate_texture_X(t_tex *tex, t_dda *dda)
{
	if (tex->direction == NORTH_SOUTH)
	{
		if (dda->sideHit == NORTH)
			tex->x = (int)(_ray()->wallX * (double)tex->north.width);
		else
			tex->x = (int)(_ray()->wallX * (double)tex->south.width);
	}
	else
	{
		if (dda->sideHit == EAST)
			tex->x = (int)(_ray()->wallX * (double)tex->east.width);
		else
			tex->x = (int)(_ray()->wallX * (double)tex->west.width);
	}
	if (dda->sideHit == NORTH_SOUTH && _ray()->ray_dir_x > 0)
	{
		if (dda->sideHit == NORTH_SOUTH)
			tex->x = tex->north.width - tex->x - 1;
		else
			tex->x = tex->south.width - tex->x - 1;
	}
	else if (dda->sideHit == WEST_EAST && _ray()->ray_dir_y < 0)
	{
		if (dda->sideHit == EAST)
			tex->x = tex->east.width - tex->x - 1;
		else
			tex->x = tex->west.width - tex->x - 1;
	}
	tex->x /= 4;
}

void	calculate_sprite(void)
{
	t_tex	*tex;
	t_dda		*dda;

	tex = _tex();
	dda = _dda();
	tex->direction = dda->sideHit;
	calculate_new_wall_x(dda);
	calculate_texture_X(tex, dda);
	step_wall();
	tex->tex_pos = tex->step * (_ray()->wall.start - WIN_HEIGHT / 2 + _ray()->wall.height / 2);
}
