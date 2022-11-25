/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:09:07 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/25 19:22:37 by gbertin          ###   ########.fr       */
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

int	control_parsing(t_general *general)
{
	int i;

	i = 1;
	//printf("on entre dans control\n");
	while (i < 5)
	{
		if (general->spts[i].path == NULL)
			return (0);
		i++;
	}
	if (general->ceil_color[0] == -1 || general->floor_color[0] == -1)
		return (0);
	//printf("retour 1\n");
	return (1);
}

static void	end_gnl(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	check_namefile(char *name)
{
	int		i;
	char	*cub;

	i = 0;
	cub = ".cub";
	while (name[i])
		i++;
	while (name[i] != '.' && i > 0)
		i--;
	if (ft_strncmp(&name[i], cub, 4))
		return (0);
	if (name[i + 4] != '\0')
		return (1);
	return (0);
}

//retourne le numéro de ligne de la dernière information trouvé
static int	 found_sprites_colors(t_general *general, char *file_name)
{
	int fd;
	char *line;
	char **line_split;
	int nb_line;
	//int	 end_info;

	//end_info = 0;
	nb_line = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		strerror(errno);
		free_general(general);
		return (1);
	}
	line = NULL;
	line = get_next_line(fd);
	while (line && !control_parsing(general))
	{
		nb_line++;
		if (!is_space(line))
		{
			line_split = ft_split(line, ' ');
			if (!line_split)
				return (1);
			if (fill_infos(general, line_split))
			{
				//printf("N %sS %sW %sE %s\n", general->spts[NORD].path, general->spts[SUD].path, general->spts[WEST].path, general->spts[EAST].path);
				//printf("F %d %d %d C %d %d %d\n", general->floor_color[0], general->floor_color[1], general->floor_color[2], general->ceil_color[0], general->ceil_color[1], general->ceil_color[2]);
				free_tab(line_split);
				free(line);
				end_gnl(fd);
				free_general(general);
				return (1);
			}
			free_tab(line_split);
		}
		//printf("line = %s", line);
		free(line);
		if (!control_parsing(general))
			line = get_next_line(fd);
		else
			line = NULL;
	}
	if (line)
		free(line);
	end_gnl(fd);
	return (nb_line);
}

int	detect_map(t_general *general, int nb_line, char *file_name)
{
	int fd;
	char *line;
	int i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		strerror(errno);
		free_general(general);
		return (-1);
	}
	line = NULL;
	line = get_next_line(fd);
	while(line && (i < nb_line || is_space(line)))
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (!line)
		return (-1);
	nb_line = i;
	while(line)
	{
		//printf("i = %d line = >%s>", i, line);
		if ((int)ft_strlen(line) - 1 > general->map_column)
			general->map_column = ft_strlen(line) - 1;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	general->map_line = i - nb_line;
	printf("map column = %d, map line = %d, index = %d, i = %d\n", general->map_column, general->map_line, nb_line, i);
	return (nb_line);

}

//pas oublier de mettre un NULL à la derniere colonne de map->matrice
int	init_map(t_general *general, char *file_name)
{
	int			nb_line;
	t_map	  	*map;
	//int			start_map;
	if (check_namefile(file_name))
		return (1);
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (1);
	ft_memset(map, 0, sizeof(t_map));
	general->map = map;
	nb_line = found_sprites_colors(general, file_name);
	if (nb_line == 1)
		return (1);
	if (!control_parsing(general))
		{
			ft_putstr_fd("Error\n", 2);
			free_general(general);
			return (1);
		}
	nb_line = detect_map(general, nb_line, file_name);
	if (nb_line == -1)
		return (1);
	//nb_line = index de la map
	printf(" N %s S %s W %s E %s\n", general->spts[NORD].path, general->spts[SUD].path, general->spts[WEST].path, general->spts[EAST].path);
	printf(" F %d %d %d C %d %d %d\n", general->floor_color[0], general->floor_color[1], general->floor_color[2], general->ceil_color[0], general->ceil_color[1], general->ceil_color[2]);
	return (0);
}