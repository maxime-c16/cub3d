/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:42:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/10 20:36:45 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(void)
{
	t_player	*ptr;

	ptr = _player();
	if (!check_wall(ptr->x + ptr->dir_x * ptr->speed, ptr->y + ptr->dir_y * ptr->speed))
	{
		ptr->y += ptr->dir_y * ptr->speed;
		ptr->x += ptr->dir_x * ptr->speed;
	}
}

void	move_backward(void)
{
	t_player	*ptr;

	ptr = _player();
	if (!check_wall(ptr->x - ptr->dir_x * ptr->speed, ptr->y - ptr->dir_y * ptr->speed))
	{
		ptr->y -= ptr->dir_y * ptr->speed;
		ptr->x -= ptr->dir_x * ptr->speed;
	}
}

void	move_left(void)
{
	t_player	*ptr;

	ptr = _player();
	if (!check_wall(ptr->x + ptr->dir_y * ptr->speed, ptr->y - ptr->dir_x * ptr->speed))
	{
		ptr->y -= ptr->plane_x * ptr->speed;
		ptr->x -= ptr->plane_y * ptr->speed;
	}
}

void	move_right(void)
{
	t_player	*ptr;

	ptr = _player();
	if (!check_wall(ptr->x - ptr->dir_y * ptr->speed, ptr->y + ptr->dir_x * ptr->speed))
	{
		ptr->y += ptr->plane_x * ptr->speed;
		ptr->x += ptr->plane_y * ptr->speed;
	}
}
