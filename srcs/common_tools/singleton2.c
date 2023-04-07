/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/07 18:58:19 by lbisson          ###   ########.fr       */
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
