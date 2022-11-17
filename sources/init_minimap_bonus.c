/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:57 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/17 13:29:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	change_tile_minimap(int y, int x, t_map *map)
{
	int y_map;
	int x_map;
	int y_mid_mini;
	int x_mid_mini;

	y_mid_mini = HEIGHT_MINIMAP / 2 + 1; // = 3
	x_mid_mini = WIDTH_MINIMAP / 2 + 1; // = 5
	if (y <= y_mid_mini)
		y_map = ceil(map->pos_y) - (y_mid_mini - y); // check si hors de la map
	else 
		y_map = ceil(map->pos_y) + (y - y_mid_mini);

		
	if (x <= x_mid_mini) // WIDTH_MINIMAP / 2 + 1 = milieu de la map en y
		x_map = ceil(map->pos_x) - (x_mid_mini - x); // check si hors de la map
	else 
		x_map = ceil(map->pos_x) + (x - x_mid_mini);
	if (y_map < 0 || y_map > (HEIGHT_MINIMAP - 1) || x_map < 0 || x_map > WIDTH_MINIMAP - 1)
		map->minimap[y][x] = '3';
	else
		map->minimap[y][x] = map->matrice[y_map][x_map];
	printf("x = %d y = %d//position minimap\nx_map %d y_map %d//calcul\n\n\n", x, y, x_map, y_map);
}

void	change_minimap(t_map *map)
{
	int	x;
	int y;

	y = 0;
	while (y < HEIGHT_MINIMAP)
	{
		x = 0;
		while (x < WIDTH_MINIMAP)
		{
			change_tile_minimap(y, x, map);
			x++;
		}
		print_matrice(map);
		y++;
	}
}

int init_minimap(t_map *map)
{
	int		i;
	int		y;

	i = 0;
	map->minimap = malloc(sizeof(char *) * (HEIGHT_MINIMAP + 1));
	if (!map->minimap)
		return (1);
	while (i < HEIGHT_MINIMAP)
	{
		y = 0;
		map->minimap[i] = malloc(sizeof(char) * (WIDTH_MINIMAP + 1));
		if (!map->minimap[i])
			return (1);
		while (y < WIDTH_MINIMAP)
		{
			map->minimap[i][y] = '0';
			y++;
		}
		map->minimap[WIDTH_MINIMAP] = NULL;
		i++;
	}
	map->minimap[HEIGHT_MINIMAP] = NULL;
	change_minimap(map);
	return (0);
}