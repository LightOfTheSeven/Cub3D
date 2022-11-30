/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:52:48 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/20 08:25:31 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float	print_collision(t_general *g, float pos_x, float pos_y, float angle)
{
	t_dir	horiz;
	t_dir	verti;
	float	distance;
	int		remember;

	distance = 0;
	remember = 0;
	verti = first_vertical_wall(pos_x, pos_y, angle);
	horiz = first_horizon_wall(pos_x, pos_y, angle);
	while (remember == 0 || !is_wall(pos_x, pos_y, angle, g))
	{
		if (horiz.hypo < verti.hypo)
		{
			distance += horiz_bigger(&remember, &pos_x, &pos_y, horiz);
			verti = first_vertical_wall(pos_x, pos_y, angle);
			horiz = next_horizon_wall(pos_x, pos_y, angle);
		}
		else
		{
			distance += verti_bigger(&remember, &pos_x, &pos_y, verti);
			horiz = first_horizon_wall(pos_x, pos_y, angle);
			verti = next_vertical_wall(pos_x, pos_y, angle);
		}
	}
	return (distance);
}

void	print_raycasting(float orig_x, float orig_y, float a[2], t_general *g)
{
	float	v_dir[2];
	int		i;
	float	x;
	float	y;
	float	distance;
	int		angle;

	angle = 0;
	while (a[ANGLE_MIN] < a[ANGLE_MAX])
	{
		if (a[ANGLE_MIN] < 0)
			angle = a[ANGLE_MIN] + 360;
		else if (a[ANGLE_MIN] > 360)
			angle = a[ANGLE_MIN] - 360;
		else
			angle = a[ANGLE_MIN];
		i = 0;
		x = orig_x * 64;
		y = orig_y * 64;
		v_dir[V_X] = cos(conversion_radian(angle));
		v_dir[V_Y] = sin(conversion_radian(angle * -1));
		distance = print_collision(g, orig_x, orig_y, angle);
		while (i < distance * 64)
		{
			mlx_pixel_put(g->mlx.ptr, g->mlx.win, (int)x, (int)y, 0x00FF00);
			x += v_dir[V_X];
			y += v_dir[V_Y];
			i++;
		}
		a[ANGLE_MIN] += 1;
	}
}

void	init_raycasting(t_general *g)
{
	float	v_angle[2];

	v_angle[ANGLE_MIN] = g->map->angle_cam - FOV / 2;
	v_angle[ANGLE_MAX] = g->map->angle_cam + FOV / 2;
	print_raycasting(g->map->pos_x, g->map->pos_y, v_angle, g);
}
