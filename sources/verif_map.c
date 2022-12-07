/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:31:50 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/07 21:54:42 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_diagonal(char **map, int x, int y)
{
	if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ' 
		|| map[y + 1][x] == ' ' || map[y - 1][x] == ' ')
		return (1);
	return (0);	
}

static int	check_direction(char **map, int x, int y)
{
	if (map[y + 1][x + 1] == ' ' || map[y - 1][x + 1] == ' ' 
		|| map[y + 1][x - 1] == ' ' || map[y - 1][x - 1] == ' ')
		return (1);
	return (0);	
}

static int	check_tile(t_general *general, char **map, int x, int y)
{
	char	tile;

	tile = map[y][x];
	if (tile == '0' || is_direction(tile))
	{
		if ((x == 0 || x == general->map_column - 1)
			|| (y == 0 || y == general->map_line - 1))
			return (1);
		if (check_diagonal(map, x, y) || check_direction(map, x, y))
			return (1);
	}
	return (0);
}

static int check_map(t_general *general)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = general->map->matrice;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (check_tile(general, map, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	verif_map(t_general *general)
{
	if (check_map(general))
	{
		ft_putstr_fd("Error\nCub3D : Map not close\n", 2);
		return (1);
	}
	return (0);
}
