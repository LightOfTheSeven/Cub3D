/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:09:07 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/24 18:42:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*static int	count_line(char *filename)
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
}*/

/*static int	fill_matrice(int nb_line, t_map *map, int fd)
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
}*/

/*static int fill_map(int nb_line, t_map *map, char *filename)
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
}*/


//retourne le numéro de ligne de la dernière information trouvé
static int	 found_sprites_colors(t_general *general, char *file_name)
{
	int fd;
	char *line;
	//int	 end_info;

	//end_info = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		strerror(errno);
		return (1);
	}
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (fill_infos(general, line))
		{
			free(line);
			close(fd);
			free_general(general);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
//pas oublier de mettre un NULL à la derniere colonne de map->matrice
int	init_map(t_general *general, char *file_name)
{
	//int			nb_line;
	t_map	  	*map;
	//int			start_map;
	
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (1);
	ft_memset(map, 0, sizeof(t_map));
	general->map = map;
	if (found_sprites_colors(general, file_name))
		return (1);
	printf("N %sS %sW %sE %s\n", general->spts[NORD].path, general->spts[SUD].path, general->spts[WEST].path, general->spts[EAST].path);
	printf("F %d %d %d C %d %d %d\n", general->floor_color[0], general->floor_color[1], general->floor_color[2], general->ceil_color[0], general->ceil_color[1], general->ceil_color[2]);
	/*nb_line = count_line(file_name);
	if (nb_line == -1)
		return (1);
	if (fill_map(nb_line, map, file_name))
		return (1);
	//init_minimap(map);*/
	return (0);
}