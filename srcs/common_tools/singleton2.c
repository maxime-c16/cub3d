/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:58:06 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:50 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
