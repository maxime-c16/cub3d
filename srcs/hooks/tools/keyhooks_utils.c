/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:47:32 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:19:33 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	rotate_left(void)
{
	t_player	*ptr;
	double		old_dir_x;
	double		old_plane_x;

	ptr = _player();
	old_dir_x = ptr->dir_x;
	old_plane_x = ptr->plane_x;
	ptr->dir_x = (ptr->dir_x * cos(ptr->rot_speed))
		- (ptr->dir_y * sin(ptr->rot_speed));
	ptr->dir_y = (old_dir_x * sin(ptr->rot_speed))
		+ (ptr->dir_y * cos(ptr->rot_speed));
	ptr->plane_x = (ptr->plane_x * cos(ptr->rot_speed))
		- (ptr->plane_y * sin(ptr->rot_speed));
	ptr->plane_y = (old_plane_x * sin(ptr->rot_speed))
		+ (ptr->plane_y * cos(ptr->rot_speed));
}

void	rotate_right(void)
{
	t_player	*ptr;
	double		old_dir_x;
	double		old_plane_x;

	ptr = _player();
	old_dir_x = ptr->dir_x;
	old_plane_x = ptr->plane_x;
	ptr->dir_x = ptr->dir_x * cos(-ptr->rot_speed)
		- ptr->dir_y * sin(-ptr->rot_speed);
	ptr->dir_y = (old_dir_x * sin(-ptr->rot_speed))
		+ (ptr->dir_y * cos(-ptr->rot_speed));
	ptr->plane_x = ptr->plane_x * cos(-ptr->rot_speed)
		- ptr->plane_y * sin(-ptr->rot_speed);
	ptr->plane_y = (old_plane_x * sin(-ptr->rot_speed))
		+ (ptr->plane_y * cos(-ptr->rot_speed));
}

int	check_wall(double x, double y)
{
	double	half_width;
	double	half_height;

	half_width = 0.1;
	half_height = 0.1;
	if (_map()->map[(int)y][(int)x] == WALL)
		return (FAILURE);
	else if (_map()->map[(int)(y + half_height)][(int)(x + half_width)] == WALL)
		return (FAILURE);
	else if (_map()->map[(int)(y - half_height)][(int)(x - half_width)] == WALL)
		return (FAILURE);
	return (SUCCESS);
}
