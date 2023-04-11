/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:42:20 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:09 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(void)
{
	t_player	*ptr;
	double		futur_posx;
	double		futur_posy;

	ptr = _player();
	futur_posx = ptr->x + ptr->dir_x * ptr->speed;
	futur_posy = ptr->y + ptr->dir_y * ptr->speed;
	if (check_wall(futur_posx, futur_posy) == FAILURE)
		return ;
	ptr->x = futur_posx;
	ptr->y = futur_posy;
}

void	move_backward(void)
{
	t_player	*ptr;
	double		futur_posx;
	double		futur_posy;

	ptr = _player();
	futur_posx = ptr->x - ptr->dir_x * ptr->speed;
	futur_posy = ptr->y - ptr->dir_y * ptr->speed;
	if (check_wall(futur_posx, futur_posy) == FAILURE)
		return ;
	ptr->x = futur_posx;
	ptr->y = futur_posy;
}

void	move_left(void)
{
	t_player	*ptr;
	double		futur_posx;
	double		futur_posy;

	ptr = _player();
	futur_posx = ptr->x + ptr->dir_y * ptr->speed;
	futur_posy = ptr->y - ptr->dir_x * ptr->speed;
	if (check_wall(futur_posx, futur_posy) == FAILURE)
		return ;
	ptr->x = futur_posx;
	ptr->y = futur_posy;
}

void	move_right(void)
{
	t_player	*ptr;
	double		futur_posx;
	double		futur_posy;

	ptr = _player();
	futur_posx = ptr->x - ptr->dir_y * ptr->speed;
	futur_posy = ptr->y + ptr->dir_x * ptr->speed;
	if (check_wall(futur_posx, futur_posy) == FAILURE)
		return ;
	ptr->x = futur_posx;
	ptr->y = futur_posy;
}
