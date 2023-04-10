/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:38:18 by lbisson           #+#    #+#             */
/*   Updated: 2023/04/08 18:30:16 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	error_on_color(char *color, char **split)
{
	if (color)
		free(color);
	free_array(split);
	handling_error("invalid color format", NULL);
}

static void	check_invalid_color(char **split)
{
	int		i;
	int		j;
	char	*color;

	i = 0;
	while (split[i])
	{
		j = 0;
		color = ft_strtrim(split[i], " \n", 0);
		if (ft_strlen(color) > 11 || !*color
			|| ft_atoi(color) > 255 || ft_atoi(color) < 0)
			error_on_color(color, split);
		while (color[j])
		{
			if (ft_isdigit(color[j]) == FALSE)
				error_on_color(color, split);
			j++;
		}
		free(color);
		i++;
	}
}

void	parse_color(char *line, t_color	*color)
{
	int		loop;
	char	**split;

	loop = 0;
	split = ft_split(line, ',');
	if (!split)
		handling_error("a memory allocation failed", NULL);
	check_invalid_color(split);
	while (split[loop])
	{
		if (loop == 0)
			color->r = ft_atoi(split[loop]);
		if (loop == 1)
			color->g = ft_atoi(split[loop]);
		if (loop == 2)
			color->b = ft_atoi(split[loop]);
		loop++;
	}
	color->filled = TRUE;
	free_array(split);
}
