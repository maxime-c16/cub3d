/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbisson <lbisson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:07:04 by mcauchy           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:00 by lbisson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handling_error(char *error_msg, char *arg)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(error_msg, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	hasta_la_vista(EXIT_FAILURE);
}
