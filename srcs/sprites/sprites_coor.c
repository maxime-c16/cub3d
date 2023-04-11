/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_coor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:51 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:13:22 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_wall_x(void)
{
	t_ray		*ray;
	t_player	*player;
	t_dda		*dda;

	ray = _ray();
	dda = _dda();
	player = _player();
	if (dda->side == NORTH_SOUTH)
		ray->wall_x = player->y + (ray->wall_dist * ray->ray_dir_y);
	else
		ray->wall_x = player->x + (ray->wall_dist * ray->ray_dir_x);
	ray->wall_x -= floor(ray->wall_x);
}

void	step_texture(void)
{
	t_ray	*ray;
	t_tex	*tex;

	ray = _ray();
	tex = _tex();
	tex->step = 1.0
		* tex->sprite[(int)_dda()->side_hit].width / ray->wall.height;
	tex->step /= 4;
	tex->tex_pos = tex->step * (ray->wall.start - WIN_HEIGHT / 2
			+ ray->wall.height / 2);
}

void	calculate_tex_x(void)
{
	t_tex	*tex;
	t_dda	*dda;

	tex = _tex();
	dda = _dda();
	tex->x = (int)(_ray()->wall_x
			* (double)tex->sprite[(int)dda->side_hit].width);
	if (dda->side == NORTH_SOUTH && _ray()->ray_dir_x > 0)
		tex->x = tex->sprite[(int)dda->side_hit].width - tex->x - 1;
	if (dda->side == WEST_EAST && _ray()->ray_dir_y < 0)
		tex->x = tex->sprite[(int)dda->side_hit].width - tex->x - 1;
	tex->x /= 4;
}

void	calculate_sprite(void)
{
	_tex()->side_hit = _dda()->side_hit;
	calculate_wall_x();
	calculate_tex_x();
	step_texture();
}
