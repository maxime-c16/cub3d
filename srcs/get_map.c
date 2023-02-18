/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:52:44 by mcauchy           #+#    #+#             */
/*   Updated: 2023/02/10 18:38:31 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	add_map_line(char *line)
{
	t_map		*map;
	char		*tmp;
	static int	i = 0;

	map = _map();
	tmp = ft_strdup(line);
	map->map[i] = ft_strtrim(tmp, "\n");
	free(tmp);
	i++;
}

static void	check_map_name(void)
{
	int		i;
	t_map	*map;

	i = 0;
	map = _map();
	while (map->path[i] && map->path[i] != '.')
		i++;
	if (!map->path[i] || ft_strcmp(map->path + i, ".cub") != 0)
	{
		ft_putendl_fd("error: given file is not a '.cub'", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	check_file_exist(void)
{
	t_map	*map;

	map = _map();
	map->fd = open(map->path, O_RDONLY);
	if (map->fd < 0)
	{
		strerror(errno);
		perror(map->path);
		exit(EXIT_FAILURE);
	}
}

static void check_file_not_empty(void)
{
	t_map	*map;

	map = _map();
	map->height = get_height(map->fd);
	if (!map->height)
	{
		ft_putendl_fd("error: given file is empty", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	check_invalid_color(int i)
{
	if (i != 3)
	{
		ft_putendl_fd("error: no valid color", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	check_invalid_char(char c)
{
	if (c != '1' || c != '0'
		|| c != 'N' || c != 'S' || c != 'E' || c != 'W')
	{
		ft_putstr_fd("error: not a valid char: ", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		hasta_la_vista();
	}
}

static void	check_map_borders(void)
{
	t_map	*map;
	int		i;
	int		j;

	i = 0;
	map = _map();
	while (i < map->height)
	{
		j = 0;
		map->width = ft_strlen(map->map[i]);
		while (j < map->width)
		{
			if (i == 0 || j == 0 || i == map->height - 1 || j == map->width - 1)
				if (map->map[i][j] != WALL)
				{
					ft_putendl_fd("error: map not closed", STDERR_FILENO);
					hasta_la_vista();
				}
			j++;
		}
		i++;
	}
}

static int	get_color(t_mlx *mlx, char flag, char *str)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
		i++;
	check_invalid_color(i);
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
		}
		i++;
	}
	free_array(split);
	return (1);
}

// static int	parse_map(int fd)
// {
// 	char	*line;
// 	int		i;
// 	int		j;
// 	int		map_start;

// 	i = 0;
// 	map_start = 0;
// 	close(fd);
// 	line = get_next_line(open(_map()->path, O_RDONLY));
// 	while (line)
// 	{
// 		j = 0;
// 		while (line[j] && !map_start)
// 		{
// 			if (line[j] == 'F' || line[j] == 'C')
// 			{
// 				if (get_color(_mlx(), line[j], line + j + 2) == -1)
// 					return (1);
// 			}
// 			if (line[j] == '1')
// 				map_start = 1;
// 			j++;
// 		}
// 		if (map_start && ft_strcmp(line, "\n") != 0)
// 		{
// 			//check_invalid_char(line[j], line);
// 			add_map_line(line);
// 		}	
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	check_map_borders();
// 	return (1);
// }

static void	split_file(int fd)
{
	int		i;
	char	*line;
	t_map	*map;

	i = 0;
	map = _map();
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	map->split = malloc(sizeof(char *) * (i + 1));
	if (!map->split)
		hasta_la_vista();
	map->split[i] = NULL;
	while (i--)
		map->split[i] = get_next_line(fd);
	close(fd);
}

static void	parse_map(int fd)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = _map();
	split_file(fd);
	while (map->split[i])
	{
		while (map->split[i] && map->split[i][j])
		{
			j = 0;
			while (map->split[i][j] == ' ' ||
				(map->split[i][j] >= '\t' && map->split[i][j] <= '\r'))
				j++;
			if (map->split[i][j] == '1')
			{
				check_invalid_char(map->split[i][j]);
				add_map_line(map->split[i]);
			}
			else if (map->split[i][j] == 'F' || map->split[i][j] == 'C')
				get_color(_mlx(), map->split[i][j], map->split[i]);
			j++;
		}
		i++;
	}
	check_map_borders();
}

void	get_map(char **av)
{
	t_map	*map;

	map = _map();
	map->path = ft_strdup(av[1]);
	check_map_name();
	check_file_exist();
	check_file_not_empty();
	map->map = ft_calloc(map->height, sizeof(char *));
	parse_map(map->fd);
}