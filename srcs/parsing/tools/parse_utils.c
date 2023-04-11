/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:02:46 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/11 20:07:03 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	open_file(char **av)
{
	t_map	*map;

	map = _map();
	if (map->fd)
		close(map->fd);
	map->fd = open(av[1], O_RDONLY);
	if (map->fd < 0)
	{
		strerror(errno);
		handling_error(map->path, NULL);
	}
}

void	skip_to_map(int fd)
{
	t_map	*map;

	map = _map();
	map->line = get_next_line(fd);
	while (map->line && (is_empty_line(map->line) == TRUE
			|| is_game_param(map->line + skip_space(map->line)) == TRUE))
	{
		free(map->line);
		map->line = get_next_line(fd);
	}
}

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	is_game_param(char *line)
{
	if (*line && ft_strnstr(line, "NO", 2))
		return (TRUE);
	else if (*line && ft_strnstr(line, "SO", 2))
		return (TRUE);
	else if (*line && ft_strnstr(line, "WE", 2))
		return (TRUE);
	else if (*line && ft_strnstr(line, "EA", 2))
		return (TRUE);
	else if (*line && ft_strnstr(line, "F", 1))
		return (TRUE);
	else if (*line && ft_strnstr(line, "C", 1))
		return (TRUE);
	else
		return (FALSE);
}

int	is_empty_line(char *line)
{
	if (ft_strcmp(line, "\n") == 0 || ft_strlen(line + skip_space(line)) == 0)
		return (TRUE);
	return (FALSE);
}
