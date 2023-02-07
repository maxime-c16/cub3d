/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:51 by mcauchy           #+#    #+#             */
/*   Updated: 2023/01/27 13:35:07 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_sprites(void)
{
	t_texture	*texture;

	texture = _texture();
	texture->north.img = mlx_xpm_file_to_image(_mlx()->mlx, texture->north.path, &texture->north.width, &texture->north.height);
	texture->south.img = mlx_xpm_file_to_image(_mlx()->mlx, texture->south.path, &texture->south.width, &texture->south.height);
	texture->east.img = mlx_xpm_file_to_image(_mlx()->mlx, texture->east.path, &texture->east.width, &texture->east.height);
	texture->west.img = mlx_xpm_file_to_image(_mlx()->mlx, texture->west.path, &texture->west.width, &texture->west.height);
	if (!texture->north.img || !texture->south.img || !texture->east.img || !texture->west.img)
		hasta_la_vista();
	texture->north.addr = (int *)mlx_get_data_addr(texture->north.img, &texture->north.bpp, &texture->north.width, &texture->north.endian);
	texture->south.addr = (int *)mlx_get_data_addr(texture->south.img, &texture->south.bpp, &texture->south.width, &texture->south.endian);
	texture->east.addr = (int *)mlx_get_data_addr(texture->east.img, &texture->east.bpp, &texture->east.width, &texture->east.endian);
	texture->west.addr = (int *)mlx_get_data_addr(texture->west.img, &texture->west.bpp, &texture->west.width, &texture->west.endian);
	if (!texture->north.addr || !texture->south.addr || !texture->east.addr || !texture->west.addr)
		hasta_la_vista();
}

static void	calculate_new_wall_x(t_dda *dda)
{
	t_ray		*ray;
	t_player	*player;

	ray = _ray();
	player = _player();
	if (dda->sideHit == NORTH_SOUTH)
		ray->wallX = player->y + (ray->wallDist * ray->ray_dir_y);
	else
		ray->wallX = player->x + (ray->wallDist * ray->ray_dir_x);
}

void	step_wall(void)
{
	t_ray		*ray;
	t_texture	*texture;

	ray = _ray();
	texture = _texture();
	if (_dda()->sideHit == NORTH)
		texture->step = 1.0 * texture->north.height / ray->wall.height;
	else if (_dda()->sideHit == SOUTH)
		texture->step = 1.0 * texture->south.height / ray->wall.height;
	else if (_dda()->sideHit == EAST)
		texture->step = 1.0 * texture->east.height / ray->wall.height;
	else
		texture->step = 1.0 * texture->west.height / ray->wall.height;
}

void	calculate_texture_x(t_texture *texture, t_dda *dda)
{
	if (texture->direction == NORTH_SOUTH)
	{
		if (dda->sideHit == NORTH)
			texture->x = (int)(_ray()->wallX * (double)texture->north.width);
		else
			texture->x = (int)(_ray()->wallX * (double)texture->south.width);
	}
	else
	{
		if (dda->sideHit == EAST)
			texture->x = (int)(_ray()->wallX * (double)texture->east.width);
		else
			texture->x = (int)(_ray()->wallX * (double)texture->west.width);
	}
	if (texture->direction == NORTH_SOUTH && _ray()->ray_dir_x > 0)
		texture->x = texture->north.width - texture->x - 1;
	else if (texture->direction == WEST_EAST && _ray()->ray_dir_y < 0)
		texture->x = texture->east.width - texture->x - 1;
	texture->x /= 4;
}

void	calculate_sprite(void)
{
	t_texture	*texture;
	t_dda		*dda;

	texture = _texture();
	dda = _dda();
	texture->direction = dda->sideHit;
	calculate_new_wall_x(dda);
	calculate_texture_x(texture, dda);
	step_wall();
	texture->tex_pos = texture->step * (_ray()->wall.start - WIN_HEIGHT / 2 + _ray()->wall.height / 2);
}
