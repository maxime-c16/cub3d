/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:38:15 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:00 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	parse_settings(char *line)
{
	if (*line && ft_strnstr(line, "NO", 2))
		parse_tex_north(line + 2);
	else if (*line && ft_strnstr(line, "SO", 2))
		parse_tex_south(line + 2);
	else if (*line && ft_strnstr(line, "WE", 2))
		parse_tex_west(line + 2);
	else if (*line && ft_strnstr(line, "EA", 2))
		parse_tex_east(line + 2);
	else if (*line && ft_strnstr(line, "F", 1))
		parse_color(line + 1, &_mlx()->c_floor);
	else if (*line && ft_strnstr(line, "C", 1))
		parse_color(line + 1, &_mlx()->c_ceiling);
	else
		handling_error("invalid game parameter", NULL);
}

void	parsing(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		handling_error("wrong number of arguments", NULL);
	map = _map();
	parse_file(av);
	open_file(av);
	map->line = get_next_line(map->fd);
	if (!map->line)
		handling_error("a memory allocation failed", NULL);
	while (map->line && check_param_filled() == FALSE)
	{
		if (ft_strcmp(map->line, "\n") != 0)
			parse_settings(map->line + skip_space(map->line));
		free(map->line);
		map->line = get_next_line(map->fd);
	}
	free(map->line);
	parse_map(av);
}
