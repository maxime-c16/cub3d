/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:06:50 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/07 18:57:39 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_tex_north(char *line)
{
	t_tex	*tex;

	tex = _tex();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->sprite[NORTH].path)
		handling_error("duplicate texture detected: ", tex->sprite[NORTH].path);
	tex->sprite[NORTH].path = ft_strdup(line + skip_space(line));
	tex->sprite[NORTH].path = ft_strtrim(tex->sprite[NORTH].path, "\n", 1);
	if (!tex->sprite[NORTH].path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_tex_south(char *line)
{
	t_tex	*tex;

	tex = _tex();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->sprite[SOUTH].path)
		handling_error("duplicate texture detected: ", tex->sprite[SOUTH].path);
	tex->sprite[SOUTH].path = ft_strdup(line + skip_space(line));
	tex->sprite[SOUTH].path = ft_strtrim(tex->sprite[SOUTH].path, "\n", 1);
	if (!tex->sprite[SOUTH].path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_tex_west(char *line)
{
	t_tex	*tex;

	tex = _tex();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->sprite[WEST].path)
		handling_error("duplicate texture detected: ", tex->sprite[WEST].path);
	tex->sprite[WEST].path = ft_strdup(line + skip_space(line));
	tex->sprite[WEST].path = ft_strtrim(tex->sprite[WEST].path, "\n", 1);
	if (!tex->sprite[WEST].path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_tex_east(char *line)
{
	t_tex	*tex;

	tex = _tex();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->sprite[EAST].path)
		handling_error("duplicate texture detected: ", tex->sprite[EAST].path);
	tex->sprite[EAST].path = ft_strdup(line + skip_space(line));
	tex->sprite[EAST].path = ft_strtrim(tex->sprite[EAST].path, "\n", 1);
	if (!tex->sprite[EAST].path)
		handling_error("a memory allocation failed", NULL);
}
