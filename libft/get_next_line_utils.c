/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:57:18 by mcauchy           #+#    #+#             */
/*   Updated: 2023/01/19 17:57:24 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*output;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	output = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2)+ 1));
	if (output == NULL)
		return (NULL);
	while (s1[i])
		output[j++] = s1[i++];
	i = 0;
	while (s2[i])
		output[j++] = s2[i++];
	output[j] = '\0';
	free(s1);
	return (output);
}

char	*ft_strndup_gnl(const char *s, int n)
{
	int		i;
	int		len;
	char	*copy;

	i = 0;
	len = ft_strlen(s);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
