/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:51 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 21:13:509 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_power_of_two(int nb)
{
	if (nb <= 0)
		return (FALSE);
	while (nb != 1)
	{
		if (nb % 2 != 0)
			return (FALSE);
		nb = nb / 2;
	}
	return (TRUE);
}

static void	check_texture(int width, int height)
{
	if (width != height)
		handling_error("invalid texture format: width and height must be equal",
			NULL);
	if (is_power_of_two(width) == FALSE)
		handling_error("invalid texture format: size must be a power of two",
			NULL);
}

void	load_sprites(void)
{
	t_tex	*tex;
	int		i;

	tex = _tex();
	i = 0;
	while (i < 4)
	{
		tex->sprite[i].img = mlx_xpm_file_to_image(_mlx()->mlx, tex->sprite[i].path,
			&tex->sprite[i].width, &tex->sprite[i].height);
		if (!tex->sprite[i].img)
			handling_error("a memory allocation failed", NULL);
		check_texture(tex->sprite[i].width, tex->sprite[i].height);
		tex->sprite[i].addr = (int *)mlx_get_data_addr(tex->sprite[i].img,
			&tex->sprite[i].bpp, &tex->sprite[i].width, &tex->sprite[i].endian);
		if (!tex->sprite[i].addr)
			handling_error("a memory allocation failed", NULL);
		i++;
	}
}

void	calculate_wall_x(void)
{
	t_ray		*ray;
	t_player	*player;
	t_dda		*dda;

	ray = _ray();
	dda = _dda();
	player = _player();
	if (dda->side == NORTH_SOUTH)
		ray->wallX = player->y + (ray->wallDist * ray->ray_dir_y);
	else
		ray->wallX = player->x + (ray->wallDist * ray->ray_dir_x);
	ray->wallX -= floor(ray->wallX);
}

void	step_texture(void)
{
	t_ray	*ray;
	t_tex	*tex;

	ray = _ray();
	tex = _tex();
	tex->step = 1.0
		* tex->sprite[(int)_dda()->sideHit].width / ray->wall.height;
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
	tex->x = (int)(_ray()->wallX * (double)tex->sprite[(int)dda->sideHit].width);
	if (dda->side == NORTH_SOUTH && _ray()->ray_dir_x > 0)
		tex->x = tex->sprite[(int)dda->sideHit].width - tex->x - 1;
	if (dda->side == WEST_EAST && _ray()->ray_dir_y < 0)
		tex->x = tex->sprite[(int)dda->sideHit].width - tex->x - 1;
	tex->x /= 4;
}

void	calculate_sprite(void)
{
	_tex()->sideHit = _dda()->sideHit;
	calculate_wall_x();
	calculate_tex_x();
	step_texture();
}
