/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:13:08 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/01 18:34:31 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_enemy_direction(void)
{
	t_enemy		*enemy;
	t_player	*player;
	double		dx;
	double		dy;

	enemy = _enemy();
	player = _player();
	dx = player->x - enemy->x;
	dy = player->y - enemy->y;
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			enemy->direction = ENEMY_EAST;
		else
			enemy->direction = ENEMY_WEST;
	}
	else
	{
		if (dy > 0)
			enemy->direction = ENEMY_SOUTH;
		else
			enemy->direction = ENEMY_NORTH;
	}
}

void	update_enemy_animation(void)
{
	t_enemy *enemy;

	enemy = _enemy();
	enemy->animation_timer += enemy->animation_speed;
	if (enemy->animation_timer >= 1.0)
	{
		enemy->animation_frame++;

		if (enemy->animation_state == ENEMY_IDLE)
		{
			if (enemy->animation_frame >= NUM_IDLE_FRAMES)
			{
				enemy->animation_frame = 0;
			}
		}
		else if (enemy->animation_state == ENEMY_WALK)
		{
			if (enemy->animation_frame >= NUM_WALK_FRAMES)
			{
				enemy->animation_frame = 0;
			}
		}
		// else if (enemy->animation_state == ENEMY_ATTACK)
		// {
		// 	if (enemy->animation_frame >= NUM_ATTACKING_FRAMES)
		// 	{
		// 		enemy->animation_frame = 0;
		// 	}
		// }
		enemy->animation_timer -= 1.0;
	}
}

void	move_enemy_towards_player(void)
{
	t_enemy		*enemy;
	t_player	*player;
	double		distance;
	double		new_x, new_y;

	distance = 0;
	enemy = _enemy();
	player = _player();

	if (enemy->animation_state == ENEMY_WALK)
	{
		distance = sqrt(pow((player->x - enemy->x), 2) + pow((player->y - enemy->y), 2));
		new_x = enemy->x + ((player->x - enemy->x) / distance) * ENEMY_SPEED;
		new_y = enemy->y + ((player->y - enemy->y) / distance) * ENEMY_SPEED;
		if (!check_wall(new_x, enemy->y))
			enemy->x = new_x;
		if (!check_wall(enemy->x, new_y))
			enemy->y = new_y;
	}
}

void	find_valid_spawn_position(t_map *map, t_enemy *enemy, double x, double y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return;
	if (map->map[(int)y][(int)x] != '1')
	{
		enemy->x = x;
		enemy->y = y;
		return;
	}
	find_valid_spawn_position(map, enemy, x - 1, y);
	find_valid_spawn_position(map, enemy, x + 1, y);
	find_valid_spawn_position(map, enemy, x, y - 1);
	find_valid_spawn_position(map, enemy, x, y + 1);
}

void	spawn_enemy_opposite_player(void)
{
	t_map		*map;
	t_enemy		*enemy;
	t_player	*player;

	map = _map();
	enemy = _enemy();
	player = _player();
	enemy->x = map->width - 1 - player->x;
	enemy->y = map->height - 1 - player->y;
	if (enemy->x >= map->width)
		enemy->x = map->width - 1;
	if (enemy->y >= map->height)
		enemy->y = map->height - 1;
	find_valid_spawn_position(map, enemy, enemy->x, enemy->y);
}

void	load_walk(void)
{
	t_enemy	*enemy;
	t_mlx	*mlx;
	int		i;
	int		j;

	i = 1;
	enemy = _enemy();
	mlx = _mlx();
	if (i == 1)
	{
		j = 0;
		while (j < 4)
		{
			// Generate the file path
			// file_path = ft_strcpy(file_path, "texture_XPM/walk/");
			// file_path = ft_strcat(file_path, walk_dirs[i]);
			// file_path = ft_strcat(file_path, "/");
			// file_path = ft_strcat(file_path, ft_itoa(j));
			// file_path = ft_strcat(file_path, ".xpm");
			enemy->walking[i][j].path = ft_strjoin("texture_XPM/walk/", ft_itoa(i));
			enemy->walking[i][j].path = ft_strjoin(enemy->walking[i][j].path, "/");
			enemy->walking[i][j].path = ft_strjoin(enemy->walking[i][j].path, ft_itoa(j));
			enemy->walking[i][j].path = ft_strjoin(enemy->walking[i][j].path, ".xpm");
			enemy->walking[i][j].img = mlx_xpm_file_to_image(mlx->mlx, enemy->walking[i][j].path,
					&enemy->walking[i][j].width, &enemy->walking[i][j].height);
			if (!enemy->walking[i][j].img)
			{
				printf("Error loading walking sprite: %s\n", enemy->walking[i][j].path);
				hasta_la_vista();
			}
			enemy->walking[i][j].addr = mlx_get_data_addr(enemy->walking[i][j].img,
					&enemy->walking[i][j].bpp, &enemy->walking[i][j].line_len,
					&enemy->walking[i][j].endian);
			j++;
		}
		// i++;
	}
}

void	draw_enemy_sprite(void)
{
	t_enemy *enemy = _enemy();
	t_player *player = _player();
	t_mlx *mlx = _mlx();
	int screen_x;
	int screen_y;
	int sprite_height;
	int sprite_width;
	int draw_start_x;
	int draw_start_y;
	int draw_end_x;
	int draw_end_y;
	int tex_x;
	int tex_y;

	double dx = enemy->x - player->x;
	double dy = enemy->y - player->y;
	double angle_to_enemy = atan2(dy, dx) - player->angle;
	if (angle_to_enemy < -M_PI) angle_to_enemy += 2 * M_PI;
	if (angle_to_enemy > M_PI) angle_to_enemy -= 2 * M_PI;

	int dir_index = 1;
	// if (angle_to_enemy > -M_PI_4 && angle_to_enemy <= M_PI_4)
	// 	dir_index = 2; // East
	// else if (angle_to_enemy > M_PI_4 && angle_to_enemy <= 3 * M_PI_4)
	// 	dir_index = 0; // North
	if (angle_to_enemy > -3 * M_PI_4 && angle_to_enemy <= -M_PI_4)
		dir_index = 1; // South
	// else
	// 	dir_index = 3; // West

	double perp_distance = sqrt(dx * dx + dy * dy) * cos(angle_to_enemy);
	sprite_height = (int)(WIN_HEIGHT / 1.5) / perp_distance;
	sprite_width = sprite_height;

	screen_x = (int)(((dx / dy) / tan(player->fov / 2.0) + 1) * (WIN_WIDTH / 2.0));
	screen_y = (WIN_HEIGHT - sprite_height) / 2;

	draw_start_x = screen_x - sprite_width / 2;
	draw_end_x = screen_x + sprite_width / 2;
	draw_start_y = screen_y;
	draw_end_y = screen_y + sprite_height;

	for (int x = draw_start_x; x < draw_end_x; x++)
	{
		tex_x = (int)((double)(x - draw_start_x) / sprite_width * enemy->walking[dir_index][enemy->animation_frame].width);
		for (int y = draw_start_y; y < draw_end_y; y++)
		{
			tex_y = (int)((double)(y - draw_start_y) / sprite_height * enemy->walking[dir_index][enemy->animation_frame].height);
			int color = enemy->walking[dir_index][enemy->animation_frame].addr[tex_y * enemy->walking[dir_index][enemy->animation_frame].width + tex_x];
			if (color != 0)
				mlx->addr[y * mlx->line_len / 4 + x] = color;
		}
	}
}
