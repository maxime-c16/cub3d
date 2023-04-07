/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/01 16:00:21 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_tex	*_tex(void)
{
	static t_tex	tex;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&tex, sizeof(t_tex));
		tex.sprite[NORTH].path = "./texture_XPM/half_wall.xpm";
		tex.sprite[WEST].path = "./texture_XPM/brick.xpm";
		tex.sprite[EAST].path = "./texture_XPM/eagle.xpm";
		tex.sprite[SOUTH].path = "./texture_XPM/backroom_wall.xpm";
	}
	return (&tex);
}

t_enemy	*_enemy(void)
{
	static t_enemy	enemy;
	static int		init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&enemy, sizeof(t_enemy));
		enemy.animation_frame = 0;
		enemy.animation_state = ENEMY_WALK;
		enemy.animation_speed = 0.1;
		enemy.animation_timer = 0;
	}
	return (&enemy);
}
