/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 17:28:27 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:01 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	calculate_y_tex(void)
{
	t_tex	*tex;

	tex = _tex();
	tex->y = (int)tex->tex_pos
		& (tex->sprite[(int)_dda()->side_hit].height - 1);
}

int	match_color_tex(void)
{
	t_dda	*dda;
	t_tex	*tex;

	dda = _dda();
	tex = _tex();
	tex->color = tex->sprite[(int)dda->side_hit].addr[
		tex->y * (tex->sprite[(int)dda->side_hit].width / 4) + tex->x];
	return (tex->color);
}
