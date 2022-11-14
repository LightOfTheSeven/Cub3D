/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:09:07 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/14 10:33:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	count_line(char *file_name)
{
	int	nb_line;
	int fd;
	char *line;

	nb_line = 0;
	fd = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		nb_line++;
	}
	free(line);
	close(fd);
	return (nb_line);
}

static int fill_map(char *file_name, int nb_line, t_map *map)
{
	int	fd;
	int	i;

	i = 0;
	map->matrice = (char **) malloc(sizeof(char *) * (nb_line + 1));
	if (!map->matrice)
		return (1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (1);
	}
	while (i < nb_line)
	{
		map->matrice[i] = get_next_line(fd);
		if (!map->matrice[i])
			return (1);
		i++;
	}
	map->matrice[nb_line] = NULL;
	return (0);
}

int	init_map(t_general *general, char *file_name)
{
	int		nb_line;
	t_map	  *map;
	
	printf("init map\n");
	map = (t_map *) malloc(sizeof(t_map));
	ft_memset(map, 0, sizeof(t_map));
	nb_line = count_line(file_name);
	if (nb_line == -1)
		return (1);
	if (fill_map(file_name, nb_line, map))
		return (1);
	general->map = map;
	return (0);
}