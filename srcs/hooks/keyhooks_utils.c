/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:47:32 by mcauchy           #+#    #+#             */
/*   Updated: 2023/01/28 13:58:33 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate_left(void)
{
	t_player	*ptr;
	double	old_dir_x;
	double	old_plane_x;

	ptr = _player();
	old_dir_x = ptr->dir_x;
	old_plane_x = ptr->plane_x;
	ptr->dir_x = (ptr->dir_x * cos(ptr->rot_speed)) - (ptr->dir_y * sin(ptr->rot_speed));
	ptr->dir_y = (old_dir_x * sin(ptr->rot_speed)) + (ptr->dir_y * cos(ptr->rot_speed));
	ptr->plane_x = (ptr->plane_x * cos(ptr->rot_speed)) - (ptr->plane_y * sin(ptr->rot_speed));
	ptr->plane_y = (old_plane_x * sin(ptr->rot_speed)) + (ptr->plane_y * cos(ptr->rot_speed));
}

void	rotate_right(void)
{
	t_player	*ptr;
	double	old_dir_x;
	double	old_plane_x;

	ptr = _player();
	old_dir_x = ptr->dir_x;
	old_plane_x = ptr->plane_x;
	ptr->dir_x = ptr->dir_x * cos(-ptr->rot_speed) - ptr->dir_y * sin(-ptr->rot_speed);
	ptr->dir_y = (old_dir_x * sin(-ptr->rot_speed)) + (ptr->dir_y * cos(-ptr->rot_speed));
	ptr->plane_x = ptr->plane_x * cos(-ptr->rot_speed) - ptr->plane_y * sin(-ptr->rot_speed);
	ptr->plane_y = (old_plane_x * sin(-ptr->rot_speed)) + (ptr->plane_y * cos(-ptr->rot_speed));
}

int	check_wall(double x, double y)
{
	if (_map()->map[(int)y][(int)x] == '1')
		return (1);
	else if (_map()->map[(int)(y + 0.1)][(int)(x + 0.1)] == '1')
		return (1);
	else if (_map()->map[(int)(y - 0.1)][(int)(x - 0.1)] == '1')
		return (1);
	else if (_map()->map[(int)(y + 0.1)][(int)(x - 0.1)] == '1')
		return (1);
	else if (_map()->map[(int)(y - 0.1)][(int)(x + 0.1)] == '1')
		return (1);
	return (0);
}
