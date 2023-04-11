/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:48:56 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:01 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_mlx	*_mlx(void)
{
	static t_mlx	mlx;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&mlx, sizeof(t_mlx));
		ft_bzero(&mlx.c_ceiling, sizeof(t_color));
		ft_bzero(&mlx.c_floor, sizeof(t_color));
	}
	return (&mlx);
}

t_map	*_map(void)
{
	static t_map	map;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&map, sizeof(t_map));
	}
	return (&map);
}

t_player	*_player(void)
{
	static t_player	player;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&player, sizeof(t_player));
	}
	return (&player);
}

t_dda	*_dda(void)
{
	static t_dda	dda;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&dda, sizeof(t_dda));
	}
	return (&dda);
}

t_ray	*_ray(void)
{
	static t_ray	ray;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&ray, sizeof(t_ray));
	}
	return (&ray);
}
