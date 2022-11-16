/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:52:48 by gbertin           #+#    #+#             */
/*   Updated: 2022/11/16 14:28:37 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

float conversion_radian(float f)
{
    f = f * (3.1415 / 180);
    return (f);
}

double get_ray_min(double angle)
{
	int half_fov;
	
	half_fov = FOV / 2;
	return (angle - half_fov);
}

double get_ray_max(double angle)
{
	int half_fov;
	
	half_fov = FOV / 2;
	return (angle + half_fov);
}

static void	print_raycasting(double origin_x, double origin_y, double v_angle[2], t_general *general)
{
	double	v_dir[2];
	int		i;
	double	x;
	double	y;

	while (v_angle[ANGLE_MIN] <= v_angle[ANGLE_MAX])
	{
		//printf("OK");
		i = 0;
		x = origin_x;
		y = origin_y;
		v_dir[V_X] = cos(conversion_radian(v_angle[ANGLE_MIN]));
		v_dir[V_Y] = sin(conversion_radian(v_angle[ANGLE_MIN] * -1));
		while (i < general->map->ray_length)
		{
			mlx_pixel_put(general->mlx.ptr, general->mlx.win, (int)x, (int)y, 0x00FF00);
			x += v_dir[V_X];
			y += v_dir[V_Y];
			i++;
		}
		v_angle[ANGLE_MIN] += 1;
	}
}


void	init_raycasting(t_general *general)
{

	double	v_angle[2];
	double	x;
	double	y;
	double tmp;
	
	// init position x et y
	x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE + 4;
	y += (general->map->pos_y - floor(general->map->pos_y)) * WIDTH_TILE + 4;
	// init angle min et angle max du FOV
	v_angle[ANGLE_MIN] = get_ray_min(general->map->angle_cam);
	v_angle[ANGLE_MAX] = get_ray_max(general->map->angle_cam);
	// SI angle_cam + 45 est superieur a 360 alors ANGLE MAX devient plus petit que ANGLE MIN
	// OU SI angle_cam - 45 est inferieur a 0 alors ANGLE MIN devient plus grand que ANGLE MIN
	if (v_angle[ANGLE_MIN] > v_angle[ANGLE_MAX])
	{
		tmp = v_angle[ANGLE_MIN];
		v_angle[ANGLE_MIN] = v_angle[ANGLE_MAX];
		v_angle[ANGLE_MAX] = tmp;
	}
	//printf("ANGLE : %f %f\n", v_angle[ANGLE_MIN], v_angle[ANGLE_MAX]);
	print_raycasting(x, y, v_angle, general);
}