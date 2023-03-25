/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:14 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 13:02:20 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_dda_side(void)
{
	t_dda	*dda;

	dda = _dda();
	if (dda->hit == 0)
		return ;
	if (dda->side == 0)
	{
		if (_ray()->ray_dir_x > 0)
			dda->sideHit = NORTH;
		else
			dda->sideHit = SOUTH;
	}
	else
	{
		if (_ray()->ray_dir_y > 0)
			dda->sideHit = WEST;
		else
			dda->sideHit = EAST;
	}
}
