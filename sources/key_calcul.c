/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_calcul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:04:18 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/08 12:11:29 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	calcul_x(double angle, t_general *g, int neg)
{
	double	x;
	double	new_x;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	x = cos(conversion_radian(angle)) * 0.06;
	if (neg)
		new_x = g->map->pos_x - x;
	else
		new_x = g->map->pos_x + x;
	if (g->map->matrice[(int)floor(g->map->pos_y)][(int)floor(new_x)] == '1')
		return (0);
	if (new_x <= 1 || new_x >= g->map_column - 1)
		return (0);
	return (x);
}

double	calcul_y(double angle, t_general *g, int neg)
{
	double	y;
	double	new_y;

	if (angle > 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	y = sin(conversion_radian(angle * -1)) * 0.06;
	if (neg)
		new_y = g->map->pos_y - y;
	else
		new_y = g->map->pos_y + y;
	if (g->map->matrice[(int)floor(new_y)][(int)floor(g->map->pos_x)] == '1')
		return (0);
	if (new_y <= 1 || new_y >= g->map_line - 1)
		return (0);
	return (y);
}
