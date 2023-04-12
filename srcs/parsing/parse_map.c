/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:48:21 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/12 18:16:23 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_map(void)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	if (map->height < 3)
		handling_error("map to small", NULL);
	while (i < map->height)
	{
		check_invalid_char(map->map[i]);
		i++;
	}
	check_nb_player();
	check_map_closed();
}

void	parse_map(char **av)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	open_file(av);
	skip_to_map(map->fd);
	map->map = ft_calloc(map->height * 2, sizeof(char *));
	if (!map->map)
		handling_error("a memory allocation failed", NULL);
	while (map->line)
	{
		map->map[i] = ft_strdup(map->line);
		map->map[i] = ft_strtrim(map->map[i], "\n", 1);
		if (!map->map[i] || is_empty_line(map->map[i]))
			handling_error("empty lines not allowed in map or at EOF", NULL);
		free(map->line);
		map->line = get_next_line(map->fd);
		i++;
	}
	check_map();
}
