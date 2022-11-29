/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 08:27:04 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/29 14:44:59 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_vertical_wall(double pos_x, double pos_y, double angle, t_map *map)
{
	if (angle > 90 && angle < 270)
		pos_x--;
	if (map->matrice[(int)floor(pos_y)][(int)floor(pos_x)] == '1')
		return (1);
	return (0);
}

int	check_horizontal_wall(double pos_x, double pos_y, double angle, t_map *map)
{
	if (angle < 180 && angle > 0)
		pos_y--;
	if (map->matrice[(int)floor(pos_y)][(int)floor(pos_x)] == '1')
		return (1);
	return (0);
}

int	is_wall(double pos_x, double pos_y, double angle, t_general *general)
{
	t_map	*map;

	map = general->map;
	if ((pos_x - floor(pos_x)) > 0)
		return (check_horizontal_wall(pos_x, pos_y, angle, map));
	else
		return (check_vertical_wall(pos_x, pos_y, angle, map));
	return (0);
}
