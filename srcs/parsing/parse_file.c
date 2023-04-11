/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:35:51 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/11 20:18:33 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	check_file_exist(char **av)
{
	t_map	*map;

	map = _map();
	map->path = ft_strdup(av[1]);
	map->fd = open(av[1], O_RDONLY);
	if (map->fd < 0)
		handling_error("cannot open: ", map->path);
}

static void	check_file_name(void)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	while (map->path[i] && map->path[i] != '.')
		i++;
	if (!map->path[i] || ft_strcmp(map->path + i, ".cub") != 0)
		handling_error("given file is not a '.cub': ", map->path);
}

static void	check_file_not_empty(void)
{
	t_map	*map;

	map = _map();
	map->height = get_height(map->fd);
	if (!map->height)
		handling_error("given file is empty: ", map->path);
	close(map->fd);
}

void	parse_file(char **av)
{
	check_file_exist(av);
	check_file_name();
	check_file_not_empty();
}
