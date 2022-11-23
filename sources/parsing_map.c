/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:09:07 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/23 11:59:14 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	count_line(char *filename)
{
	int	nb_line;
	char *line;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (-1);
	}
	nb_line = 0;
	line = NULL;
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

static int	fill_matrice(int nb_line, t_map *map, int fd)
{
	int i;

	i = 0;
	while (i < nb_line)
	{
		map->matrice[i] = get_next_line(fd);
		if (!map->matrice[i])
			return (1);
		i++;
	}
	return (0);
}

static int fill_map(int nb_line, t_map *map, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (-1);
	}
	map->matrice = (char **) malloc(sizeof(char *) * (nb_line + 1));
	if (!map->matrice || fill_matrice(nb_line, map, fd))
		return (1);
	//A MODIFIER AVEC LE RAYCASTING 3D
	if ((size_t)nb_line > ft_strlen(map->matrice[0]))
		map->ray_length = nb_line * WIDTH_TILE;
	else
		map->ray_length = ft_strlen(map->matrice[0]) * WIDTH_TILE;
	//
	map->matrice[nb_line] = NULL;
	close(fd);
	return (0);
}

static int take_info(t_general *general, char *line, int id)
{
	char	**path;

	path = ft_split(line, ' ');
	if (!path)
		return (1);
	if (id != -1)
	{
		if (general->spts[id].path == NULL)
		{
			if (path[0] && path[1])
				general->spts[id].path = path[1];
			//free tab
		}
		else
			return (1);
	}
	return (0);
}

static int	fill_infos(t_general *general, char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, "NO", 2))
		return(take_info(general, line, NORD));
	if (!ft_strncmp(line, "SO", 2))
		return(take_info(general, line, SUD));
	if (!ft_strncmp(line, "WE", 2))
		return(take_info(general, line, WEST));
	if (!ft_strncmp(line, "EA", 2))
		return (take_info(general, line, EAST));
	return (0);
}
//retourne le numéro de ligne de la dernière information trouvé
static int	 found_sprites_colors(t_general *general, char *file_name)
{
	int fd;
	char *line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (-1);
	}
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		fill_infos(general, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

int	init_map(t_general *general, char *file_name)
{
	int			nb_line;
	t_map	  	*map;
	//int			start_map;
	
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (1);
	ft_memset(map, 0, sizeof(t_map));
	found_sprites_colors(general, file_name);
	printf("N %sS %sW %sE %s\n", general->spts[NORD].path, general->spts[SUD].path, general->spts[WEST].path, general->spts[EAST].path);
	nb_line = count_line(file_name);
	if (nb_line == -1)
		return (1);
	if (fill_map(nb_line, map, file_name))
		return (1);
	//init_minimap(map);
	general->map = map;
	return (0);
}