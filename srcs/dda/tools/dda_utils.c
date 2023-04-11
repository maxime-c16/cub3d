/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:14 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:13:22 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	set_dda_side(void)
{
	t_dda	*dda;

	dda = _dda();
	if (dda->hit != TRUE)
		return ;
	if (dda->side == WEST_EAST)
	{
		if (_ray()->ray_dir_y > 0)
			dda->side_hit = NORTH;
		else
			dda->side_hit = SOUTH;
	}
	else
	{
		if (_ray()->ray_dir_x > 0)
			dda->side_hit = WEST;
		else
			dda->side_hit = EAST;
	}
}
