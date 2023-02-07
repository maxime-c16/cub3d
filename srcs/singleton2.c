/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/01/23 17:44:33 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*_texture(void)
{
	static t_texture	texture;
	static int			init = 0;

	if (!init)
	{
		init++;
		ft_bzero(&texture, sizeof(t_texture));
		texture.east.path = "./texture_XPM/eagle.xpm";
		texture.west.path = "./texture_XPM/brick.xpm";
		texture.north.path = "./texture_XPM/blueWall.xpm";
		texture.south.path = "./texture_XPM/brick.xpm";
	}
	return (&texture);
}
