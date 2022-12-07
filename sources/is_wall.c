/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 08:27:04 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/06 14:28:13 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	check_vertical_wall(double x, double y, double angle, t_general *g)
{
	if (angle > 90 && angle < 270)
		x--;
	if ((x <= 0 || x > g->map_column) || (y <= 0 || y > g->map_line - 1))
		return (1);
	if (g->map->matrice[(int)floor(y)][(int)floor(x)] == '1')
		return (1);
	return (0);
}

static int	check_horizontal_wall(double x, double y, double a, t_general *g)
{
	if (a < 180 && a > 0)
		y--;
	if ((x <= 0 || x > g->map_column) || (y <= 0 || y > g->map_line - 1))
		return (1);
	if (g->map->matrice[(int)floor(y)][(int)floor(x)] == '1')
		return (1);
	return (0);
}

int	is_wall(double x, double y, double angle, t_general *g)
{
	if ((x <= 0 || x > g->map_column) || (y <= 0 || y > g->map_line))
		return (1);
	if ((x - floor(x)) > 0)
		return (check_horizontal_wall(x, y, angle, g));
	else
		return (check_vertical_wall(x, y, angle, g));
	return (0);
}
