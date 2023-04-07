/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/05 16:25:43 by lbisson          ###   ########.fr       */
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
	}
	return (&texture);
}
