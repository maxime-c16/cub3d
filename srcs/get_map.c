/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:52:44 by mcauchy           #+#    #+#             */
/*   Updated: 2023/03/21 14:33:17 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	add_map_line(char *line)
{
	t_map		*map;
	static int	i = 0;

	map = _map();
	map->map[i] = ft_strdup(line);
	map->map[i] = ft_strtrim(map->map[i], "\n");
	i++;
}

int	check_map_borders(void)
{
	t_map	*map;
	int		i;
	int		j;

	map = _map();
	i = 0;
	map->width = ft_strlen(map->map[0]);
	while (i < map->height)
	{
		j = 0;
		if (map->width < ft_strlen(map->map[i]))
			map->width = ft_strlen(map->map[i]);
		while (j < ft_strlen(map->map[i]))
		{
			if (i == 0 || j == 0 || i == map->height - 1 || j == ft_strlen(map->map[i]) - 1)
			{
				if (map->map[i][j] != WALL)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	get_color(t_mlx *mlx, char flag, char *str)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
		i++;
	if (i != 3)
		return (-1);
	i = 0;
	while (split[i])
	{
		if (flag == 'F')
		{
			if (i == 0)
				mlx->c_floor.r = ft_atoi(split[i]);
			else if (i == 1)
				mlx->c_floor.g = ft_atoi(split[i]);
			else if (i == 2)
				mlx->c_floor.b = ft_atoi(split[i]);
		}
		else if (flag == 'C')
		{
			if (i == 0)
				mlx->c_ceiling.r = ft_atoi(split[i]);
			else if (i == 1)
				mlx->c_ceiling.g = ft_atoi(split[i]);
			else if (i == 2)
				mlx->c_ceiling.b = ft_atoi(split[i]);
			mlx->flag = 1;
		}
		i++;
	}
	return (1);
}

int	check_first_map_line(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	if (tmp[0] != '1')
		return (free(tmp), 0);
	free(tmp);
	return (1);
}

int	parse_map(int fd)
{
	char	*line;
	int		i;
	int		j;
	int		map_start;

	i = 0;
	map_start = 0;
	close(fd);
	line = get_next_line(open(_map()->path, O_RDONLY));
	while (line)
	{
		j = 0;
		while (line[j] && !map_start)
		{
			// if (line[j] != ' ' && line[j] != '1' && line[j] != 'N'
			// 	&& line[j] != 'S' && line[j] != 'E' && line[j] != 'W')
			// 	return (1);
			if (line[j] == 'F' || line[j] == 'C')
			{
				if (get_color(_mlx(), line[j], line + j + 1) == -1)
					return (1);
			}
			if (check_first_map_line(line) == 1)
				map_start = 1;
			j++;
		}
		if (map_start && ft_strcmp(line, "\n") != 0)
			add_map_line(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	check_map_borders();
	return (1);
}
