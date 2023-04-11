/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:36:25 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:53 by lbisson          ###   ########.fr       */
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

void	init_sprites(void)
{
	t_tex	*tex;
	int		i;

	tex = _tex();
	i = 0;
	while (i < 4)
	{
		tex->sprite[i].img = mlx_xpm_file_to_image(_mlx()->mlx,
				tex->sprite[i].path, &tex->sprite[i].width,
				&tex->sprite[i].height);
		if (!tex->sprite[i].img)
			handling_error("a memory allocation failed", NULL);
		check_texture(tex->sprite[i].width, tex->sprite[i].height);
		tex->sprite[i].addr = (int *)mlx_get_data_addr(tex->sprite[i].img,
				&tex->sprite[i].bpp, &tex->sprite[i].width,
				&tex->sprite[i].endian);
		if (!tex->sprite[i].addr)
			handling_error("a memory allocation failed", NULL);
		i++;
	}
}
