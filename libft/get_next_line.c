/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:55:59 by mecauchy          #+#    #+#             */
/*   Updated: 2023/01/19 17:56:41 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*fill_stock(char *stock, char *buffer, int fd)
{
	int	read_output;

	read_output = 1;
	while (read_output && !(ft_strchr(stock, '\n')))
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		buffer[read_output] = '\0';
		if (read_output == 0)
			break ;
		if (read_output < 0)
		{
			free(stock);
			return (NULL);
		}
		stock = ft_strjoin_free_s1(stock, buffer);
	}
	if (stock[0] == 0 && read_output == 0)
		return (free(stock), NULL);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "";
	int			i;
	int			j;
	char		*output;
	char		*stock;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (buffer[0] != '\0')
		stock = ft_strndup_gnl(buffer, ft_strlen(buffer));
	else
		stock = ft_strndup_gnl("", 1);
	stock = fill_stock(stock, buffer, fd);
	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	output = ft_strndup_gnl(stock, i + (stock[i] != '\0'));
	j = 0;
	i += (stock[i] != '\0');
	while (stock[i])
		buffer[j++] = stock[i++];
	buffer[j] = '\0';
	return (free(stock), output);
}
