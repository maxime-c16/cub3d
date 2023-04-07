/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:28:51 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/01 17:34:32 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_pixel(int i, t_sprite *sprite)
{
	int		x;
	int		y;
	int		z;
	int		color;

	y = 0;
	z = 0;
	sprite[i].pixels = (int **)malloc(sizeof(int *) * sprite[i].height);
	if (!sprite[i].pixels)
		hasta_la_vista();
	while (y < sprite[i].height)
	{
		x = 0;
		sprite[i].pixels[y] = (int *)malloc(sizeof(int) * sprite[i].width);
		if (!sprite[i].pixels[y])
			hasta_la_vista();
		while (x < sprite[i].width)
		{
			color = calculate_rgb((unsigned char)sprite[i].addr[z + 2],
				(unsigned char)sprite[i].addr[z + 1], (unsigned char)sprite[i].addr[z]);
			if (color != 0)
				sprite[i].pixels[y][x] = color;
			x++;
			z += 4;
		}
		y++;
	}
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
			hasta_la_vista();
		tex->sprite[i].addr = mlx_get_data_addr(tex->sprite[i].img,
			&tex->sprite[i].bpp, &tex->sprite[i].line_len, &tex->sprite[i].endian);
		fill_pixel(i, tex->sprite);
		if (!tex->sprite[i].addr)
			hasta_la_vista();
		i++;
	}
	load_walk();
}

static void	calculate_wall_x(t_dda *dda)
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
	t_ray	*ray;
	t_tex	*tex;

	ray = _ray();
	tex = _tex();
	tex->step = 1.0 * tex->sprite[(int)_dda()->sideHit].width / ray->wall.height;
}

void calculate_texture_X(t_tex *tex, t_dda *dda)
{
	tex->x = (int)(_ray()->wallX * (double)tex->sprite[(int)dda->sideHit].width);
	if ((dda->sideHit == NORTH_SOUTH && _ray()->ray_dir_x > 0) ||
		(dda->sideHit == WEST_EAST && _ray()->ray_dir_y < 0))
		tex->x = tex->sprite[(int)dda->sideHit].width - tex->x - 1;
}

void	calculate_sprite(void)
{
	t_tex	*tex;
	t_dda	*dda;

	tex = _tex();
	dda = _dda();
	tex->sideHit = dda->sideHit;
	calculate_wall_x(dda);
	calculate_texture_X(tex, dda);
	step_wall();
	tex->tex_pos = (_ray()->wall.start - WIN_HEIGHT / 2 + _ray()->wall.height / 2) * tex->step;
}
