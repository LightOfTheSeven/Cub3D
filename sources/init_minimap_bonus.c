/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:57 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/17 08:54:47 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	change_tile_minimap(int y, int x, t_map *map)
{
	int y_map;
	int x_map;

	if (y <= (HEIGHT_MINIMAP / 2 + 1)) // HEIGHT_MINIMAP / 2 + 1 = milieu de la map en y
		y_map = map->pos_y - ((HEIGHT_MINIMAP / 2 + 1) - y); // check si hors de la map
	else 
		y_map = map->pos_y + ((HEIGHT_MINIMAP / 2 + 1) - y);
	if (x <= (HEIGHT_MINIMAP / 2 + 1)) // HEIGHT_MINIMAP / 2 + 1 = milieu de la map en y
		x_map = map->pos_x - ((WIDTH_MINIMAP / 2 + 1) - x - 1); // check si hors de la map
	else 
		x_map = map->pos_x + ((WIDTH_MINIMAP / 2 + 1) - x -1);
	map->minimap[y][x] = map->matrice[(int)map->pos_y - y_map][(int)map->pos_x - x_map];
	printf("pos x = %d pos y = %d\n", (int)map->pos_x - x_map, (int)map->pos_y - y_map);
}

void	change_minimap(t_map *map)
{
	int	i;
	int y;

	i = 0;
	while (i < HEIGHT_MINIMAP)
	{
		y = 0;
		while (y < WIDTH_MINIMAP)
		{
			change_tile_minimap(i, y, map);
			y++;
		}
		print_matrice(map);
		i++;
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