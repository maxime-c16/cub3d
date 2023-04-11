/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:01:25 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/11 18:50:53 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	check_param_filled(void)
{
	t_mlx	*mlx;
	t_tex	*tex;

	mlx = _mlx();
	tex = _tex();
	if (!tex->sprite[NORTH].path || !tex->sprite[SOUTH].path
		|| !tex->sprite[WEST].path || !tex->sprite[EAST].path)
		return (FALSE);
	if (mlx->c_ceiling.filled == FALSE || mlx->c_floor.filled == FALSE)
		return (FALSE);
	return (TRUE);
}

void	check_invalid_char(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line && line[i])
	{
		c = line[i];
		if (line[i] != ' '
			&& line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			handling_error("invalid char detected in map: ", &c);
		i++;
	}
}

static int	is_valid_zero(int i, int j)
{
	char	**map;

	map = _map()->map;
	if (i == 0 || j == 0
		|| i == _map()->height || j == _map()->width
		|| j + 2 > ft_strlen(map[i - 1]) || j + 2 > ft_strlen(map[i + 1]))
		return (FALSE);
	if (!ft_strchr("01NSEW", map[i][j - 1])
		|| !ft_strchr("01NSEW", map[i][j + 1])
		|| !ft_strchr("01NSEW", map[i - 1][j])
		|| !ft_strchr("01NSEW", map[i - 1][j - 1])
		|| !ft_strchr("01NSEW", map[i - 1][j + 1])
		|| !ft_strchr("01NSEW", map[i + 1][j])
		|| !ft_strchr("01NSEW", map[i + 1][j - 1])
		|| !ft_strchr("01NSEW", map[i + 1][j + 1]))
		return (FALSE);
	return (TRUE);
}

void	check_map_closed(void)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = _map();
	while (i < map->height)
	{
		j = skip_space(map->map[i]);
		map->width = ft_strlen(map->map[i]);
		while (j < map->width)
		{
			if (i != 0 || i != map->height)
				if (ft_strchr("0NSEW", map->map[i][j]) && !is_valid_zero(i, j))
					handling_error("map not closed: ", map->map[i]);
			j++;
		}
		i++;
	}
}

void	check_nb_player(void)
{
	int		i;
	int		j;
	int		nb_player;
	t_map	*map;

	i = 0;
	nb_player = 0;
	map = _map();
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
				nb_player++;
			j++;
		}
		i++;
	}
	if (nb_player != 1)
		handling_error("invalid number of player", NULL);
}
