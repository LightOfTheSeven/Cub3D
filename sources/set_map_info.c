/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:42:47 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 13:11:57 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	fill_color(int *color, char **colors)
{
	if (only_int(colors[0]) || only_int(colors[1]) || only_int(colors[2]))
		return (1);
	color[0] = ft_atoi(colors[0]);
	color[1] = ft_atoi(colors[1]);
	color[2] = ft_atoi(colors[2]);
	if ((color[0] < 0 || color[0] > 255) || (color[1] < 0 || color[1] > 255)
		|| (color[2] < 0 || color[2] > 255))
		return (1);
	return (0);
}

static int	set_color(char *line, int *color)
{
	char	**colors;
	int		err;

	err = 0;
	if (color[0] != -1)
	{
		ft_putstr_fd("Error\nCub3D : This color is already set\n", 2);
		return (1);
	}
	colors = ft_split(line, ',');
	if (count_tab(colors) == 3)
		err = fill_color(color, colors);
	else
		err = 1;
	if (err)
		ft_putstr_fd("Error\nCub3D : Bad Format Colors\n", 2);
	free_tab(colors);
	return (err);
}

static int	check_color(t_general *general, int id, char **path)
{
	int	err;

	err = 0;
	if (id == -1)
		err = set_color(path[1], general->ceil_color);
	else
		err = set_color(path[1], general->floor_color);
	return (err);
}

static int	take_info(t_general *general, char **path, int id)
{
	int	err;

	err = 0;
	if (count_tab(path) != 2)
	{
		ft_putstr_fd("Error\nCub3D : Bad syntax in file\n", 2);
		return (1);
	}
	if (id > -1)
	{
		if (general->spts[id].path == NULL)
		{
			general->spts[id].path = ft_strdup(path[1]);
			if (!general->spts[id].path)
				return (1);
		}
		else
		{
			ft_putstr_fd("Error\nCub3D : This Path is already set\n", 2);
			err = 1;
		}
	}
	else
		err = check_color(general, id, path);
	return (err);
}

int	fill_infos(t_general *general, char **line_split)
{
	if (!line_split)
		return (1);
	if (!ft_strncmp(line_split[0], "NO", 2))
		return (take_info(general, line_split, nord));
	if (!ft_strncmp(line_split[0], "SO", 2))
		return (take_info(general, line_split, south));
	if (!ft_strncmp(line_split[0], "WE", 2))
		return (take_info(general, line_split, west));
	if (!ft_strncmp(line_split[0], "EA", 2))
		return (take_info(general, line_split, east));
	if (!ft_strncmp(line_split[0], "C", 1))
		return (take_info(general, line_split, -1));
	if (!ft_strncmp(line_split[0], "F", 1))
		return (take_info(general, line_split, -2));
	ft_putstr_fd("Error\nCub3D : Bad syntax in file\n", 2);
	return (1);
}
