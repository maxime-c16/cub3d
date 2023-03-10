/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/26 12:50:41 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_tex	*_tex(void)
{
	static t_tex	tex;
	static int			init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&tex, sizeof(t_tex));
		tex.east.path = "./texture_XPM/eagle.xpm";
		tex.west.path = "./texture_XPM/brick.xpm";
		tex.north.path = "./texture_XPM/blueWall.xpm";
		tex.south.path = "./texture_XPM/brick.xpm";
	}
	return (&tex);
}
