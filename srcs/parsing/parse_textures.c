/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:06:50 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/05 20:09:43 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture_north(char *line)
{
	t_texture	*tex;

	tex = _texture();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->north.path)
		handling_error("duplicate texture detected: ", tex->north.path);
	tex->north.path = ft_strdup(line + skip_space(line));
	if (!tex->north.path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_texture_south(char *line)
{
	t_texture	*tex;

	tex = _texture();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->south.path)
		handling_error("duplicate texture detected: ", tex->south.path);
	tex->south.path = ft_strdup(line + skip_space(line));
	if (!tex->south.path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_texture_west(char *line)
{
	t_texture	*tex;

	tex = _texture();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->west.path)
		handling_error("duplicate texture detected: ", tex->west.path);
	tex->west.path = ft_strdup(line + skip_space(line));
	if (!tex->west.path)
		handling_error("a memory allocation failed", NULL);
}

void	parse_texture_east(char *line)
{
	t_texture	*tex;

	tex = _texture();
	if (*line != ' ')
		handling_error("invalid texture format: ", line);
	if (tex->east.path)
		handling_error("duplicate texture detected: ", tex->east.path);
	tex->east.path = ft_strdup(line + skip_space(line));
	if (!tex->east.path)
		handling_error("a memory allocation failed", NULL);
}
