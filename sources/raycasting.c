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

double	fisheye(double distance, double angle, double angle_cam)
{
	return (distance * cos(conversion_radian(angle - angle_cam)));
}

double	print_collision(t_general *g, double pos_x, double pos_y, double angle)
{
	t_dir	horiz;
	t_dir	verti;
	double	distance;
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

void	print_raycasting(double orig_x, double orig_y, double a[2], t_general *g)
{
	int		i;
	double	distance;
	double	angle;

	angle = 0;
	i = 0;
	while (a[ANGLE_MIN] < a[ANGLE_MAX])
	{
		if (a[ANGLE_MIN] < 0.0)
			angle = a[ANGLE_MIN] + 360.0;
		else if (a[ANGLE_MIN] > 360.0)
			angle = a[ANGLE_MIN] - 360.0;
		else
			angle = a[ANGLE_MIN];
		printf("angle = %f\n", angle);
		i++;
		printf("i = %d\n", i);
		distance = print_collision(g, orig_x, orig_y, angle);
		print_a_column(g, fisheye(distance, angle, g->map->angle_cam), i);
		a[ANGLE_MIN] += FOV / XPIXEL;
	}
	mlx_put_image_to_window(g->mlx.ptr, g->mlx.win, g->mlx.img, 0, 0);
}

void	init_raycasting(t_general *g)
{
	double	v_angle[2];

	v_angle[ANGLE_MIN] = g->map->angle_cam - FOV / 2;
	v_angle[ANGLE_MAX] = g->map->angle_cam + FOV / 2;
	init_image(g);
	print_raycasting(g->map->pos_x, g->map->pos_y, v_angle, g);
}
