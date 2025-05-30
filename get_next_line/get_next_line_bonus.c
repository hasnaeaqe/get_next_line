/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    get_next_line_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haqajjef <haqajjef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:50:39 by haqajjef          #+#    #+#             */
/*   Updated: 2024/12/09 11:18:59 by haqajjef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(int fd, char *stock)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free(stock), stock = NULL, NULL);
	bytes_read = 1;
	while (bytes_read && !ft_strchr(stock, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stock), NULL);
		buffer[bytes_read] = '\0';
		tmp = stock;
		stock = ft_strjoin(stock, buffer);
		if (!stock)
			return (free(buffer), free(tmp), NULL);
		free(tmp);
	}
	free (buffer);
	return (stock);
}

static char	*fix_stock(char *stock)
{
	int		i;
	char	*line;

	i = 0;
	if (!stock || !*stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	line = ft_substr(stock, 0, i + 1);
	if (!line)
		return (free(stock), NULL);
	return (line);
}

static char	*update(char *stock)
{
	int		i;
	int		start;
	char	*upd;

	i = 0;
	if (stock == NULL || !*stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (free(stock), stock = NULL, NULL);
	start = i + 1;
	upd = ft_strdup(stock + start);
	if (upd == NULL)
		return (free(stock), stock = NULL, NULL);
	free (stock);
	return (upd);
}

char	*get_next_line(int fd)
{
	static char	*stock[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd > OPEN_MAX)
		return (NULL);
	stock[fd] = get_line(fd, stock[fd]);
	if (stock[fd] == NULL)
		return (NULL);
	line = fix_stock(stock[fd]);
	if (line == NULL)
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	stock[fd] = update(stock[fd]);
	return (line);
}
