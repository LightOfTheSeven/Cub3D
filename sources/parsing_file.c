/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:09:07 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/07 21:55:04 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	control_parsing(t_general *general)
{
	int	i;

	i = 0;
	while (i < NB_SPRITE)
	{
		if (general->spts[i].path == NULL)
			return (0);
		i++;
	}
	if (general->ceil_color[0] == -1 || general->floor_color[0] == -1)
		return (0);
	return (1);
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
static int	found_sprites_colors(t_general *general)
{
	int		fd;
	char	*line;
	char	**line_split;
	int		nb_line;

	nb_line = 0;
	fd = open(general->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		strerror(errno);
		close(fd);
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
				free_tab(line_split);
				free(line);
				end_gnl(fd);
				close(fd);
				return (1);
			}
			free_tab(line_split);
		}
		free(line);
		if (!control_parsing(general))
			line = get_next_line(fd);
		else
			line = NULL;
	}
	if (line)
		free(line);
	end_gnl(fd);
	close(fd);
	return (nb_line);
}

//pas oublier de mettre un NULL à la derniere colonne de map->matrice
int	init_map(t_general *general)
{
	int		nb_line;
	t_map	*map;

	if (check_namefile(general->filename))
		return (1);
	map = (t_map *) malloc(sizeof(t_map));
	if (!map)
		return (1);
	ft_memset(map, 0, sizeof(t_map));
	general->map = map;
	nb_line = found_sprites_colors(general);
	if (nb_line == 1)
		return (1);
	if (!control_parsing(general))
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	if (detect_map(general, nb_line))
		return (1);
	return (0);
}
