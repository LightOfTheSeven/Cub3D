/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:43:15 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/10 15:06:43 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	end_gnl(int fd)
{
	char	*line;
	int		err;
	
	err = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_space(line))
			err = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (err);
}

int	is_direction(char c)
{
	if (c == 'N' || c == 'O' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

int	count_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	is_space(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	only_int(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}
