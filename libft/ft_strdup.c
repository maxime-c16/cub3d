/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 22:28:35 by maximecauch       #+#    #+#             */
/*   Updated: 2022/09/28 19:04:14 by yschecro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + 1));
	if (!s1 || !cpy)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = (char)s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
