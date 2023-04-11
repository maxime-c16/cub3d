/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:14 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 14:27:21 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_dda_side(void)
{
	t_dda	*dda;

	dda = _dda();
	if (dda->hit != TRUE)
		return ;
	if (dda->side == WEST_EAST)
	{
		if (_ray()->ray_dir_y > 0)
			dda->sideHit = NORTH;
		else
			dda->sideHit = SOUTH;
	}
	else
	{
		if (_ray()->ray_dir_x > 0)
			dda->sideHit = WEST;
		else
			dda->sideHit = EAST;
	}
}
