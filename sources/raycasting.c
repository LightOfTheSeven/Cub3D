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

t_dir	first_horizon_wall(float pos_y, double angle)
{
	t_dir horiz;

	if (angle < 180)
		horiz.y = floor(pos_y) - pos_y;
	else
		horiz.y = ceil(pos_y) - pos_y;
	horiz.x = (horiz.y)/tan(conversion_radian(angle));
	printf("calcul horizon x = %f, y = %f\n", horiz.x, horiz.y);
	return (horiz);
}

t_dir	first_vertical_wall(float pos_x, double angle)
{
	t_dir verti;

	if (angle > 90 && angle < 270)
		verti.x = floor(pos_x) - pos_x;
	else
		verti.x = ceil(pos_x) - pos_x;
	verti.y = (verti.x) * tan(conversion_radian(angle));
	printf("calcul vertical x = %f, y = %f\n", verti.x, verti.y);
	return (verti);
}

t_dir calcul_first_collision(float pos_x, float pos_y, float angle)
{
	t_dir horiz;
	t_dir verti;
	float A;
	float B;

	printf("position de base x = %f et y = %f\n", pos_x, pos_y);
	horiz = first_horizon_wall(pos_y, angle);
	verti = first_vertical_wall(pos_x, angle);
	A = pos_x - (pos_x - horiz.x);
	B = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(A*A + B*B);
	A = pos_x - (pos_x + verti.x);
	B = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(A*A + B*B);
	printf("hypo horiz = %f, hypo verti = %f\n", horiz.hypo, verti.hypo);
	if (horiz.hypo < verti.hypo)
	{
		horiz.x = pos_x - horiz.x;
		horiz.y = pos_y + horiz.y;
		return (horiz);
	}
	else
	{
		verti.x = pos_x + verti.x;
		verti.y = pos_y - verti.y;
		return (verti);
	}
}

t_dir	next_horizon_wall(float pos_y, double angle)
{
	t_dir horiz;
	(void)pos_y;

	if (angle < 180)
		horiz.y = -1;
	else
		horiz.y = 1;
	horiz.x = 1/tan(conversion_radian(angle));
	printf("calcul horizon x = %f, y = %f\n", horiz.x, horiz.y);
	return (horiz);
}

t_dir	next_vertical_wall(float pos_x, double angle)
{
	t_dir verti;
	(void)pos_x;

	if (angle > 90 && angle < 270)
		verti.x = -1;
	else
		verti.x = 1;
	verti.y = tan(conversion_radian(angle));
	printf("calcul vertical x = %f, y = %f\n", verti.x, verti.y);
	return (verti);
}

t_dir calcul_next_collision(float pos_x, float pos_y, float angle)
{
	t_dir horiz;
	t_dir verti;
	float A;
	float B;

	horiz = next_horizon_wall(pos_y, angle);
	verti = next_vertical_wall(pos_x, angle);
	A = pos_x - (pos_x - horiz.x);
	B = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(A*A + B*B);
	A = pos_x - (pos_x + verti.x);
	B = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(A*A + B*B);
	printf("hypo horiz = %f, hypo verti = %f\n", horiz.hypo, verti.hypo);
	if (horiz.hypo < verti.hypo)
	{
		horiz.x = pos_x + (-horiz.y * horiz.x);
		horiz.y = pos_y + horiz.y;
		return (horiz);
	}
	else
	{
		verti.y = pos_y - (verti.x * verti.y);
		verti.x = pos_x + verti.x;
		return (verti);
	}
}

static void print_collision(t_general *general, float pos_x, float pos_y, float angle)
{
	t_dir pos;

	pos = calcul_first_collision(pos_x, pos_y, angle);
	pos_x = pos.x;
	pos_y = pos.y;
	mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
		general->spts[PLAYER].ptr, pos_x * 64, pos_y * 64);
	while (general->map->matrice[(int)floor(pos_y)][(int)floor(pos_x)-1] != '1')
	{
		printf("pos x = %f, new pos y = %f\n", pos_x, pos_y);
		pos = calcul_next_collision(pos_x, pos_y, angle);
		pos_x = pos.x;
		pos_y = pos.y;
		mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
		general->spts[PLAYER].ptr, pos_x * 64, pos_y * 64);
	}
}

static void	print_raycasting(float origin_x, float origin_y, float v_angle[2], t_general *general)
{
	float	v_dir[2];
	int		i;
	float	x;
	float	y;

	while (v_angle[ANGLE_MIN] <= v_angle[ANGLE_MAX])
	{
		//printf("OK");
		i = 0;
		x = origin_x * 64;
		y = origin_y * 64;
		v_dir[V_X] = cos(conversion_radian(v_angle[ANGLE_MIN]));
		v_dir[V_Y] = sin(conversion_radian(v_angle[ANGLE_MIN] * -1));
		print_collision(general, origin_x, origin_y, v_angle[ANGLE_MIN]);
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

	float	v_angle[2];
	float	x;
	float	y;
	float 	tmp;
	
	// init position x et y
	x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE + 4;
	y += (general->map->pos_y - floor(general->map->pos_y)) * WIDTH_TILE + 4;
	// init angle min et angle max du FOV
	//v_angle[ANGLE_MIN] = get_ray_min(general->map->angle_cam);
	//v_angle[ANGLE_MAX] = get_ray_max(general->map->angle_cam);
	// SI angle_cam + 45 est superieur a 360 alors ANGLE MAX devient plus petit que ANGLE MIN
	// OU SI angle_cam - 45 est inferieur a 0 alors ANGLE MIN devient plus grand que ANGLE MIN
	v_angle[ANGLE_MIN] = general->map->angle_cam;
	v_angle[ANGLE_MAX] = general->map->angle_cam;
	if (v_angle[ANGLE_MIN] > v_angle[ANGLE_MAX])
	{
		tmp = v_angle[ANGLE_MIN];
		v_angle[ANGLE_MIN] = v_angle[ANGLE_MAX];
		v_angle[ANGLE_MAX] = tmp;
	}
	//printf("ANGLE : %f %f\n", v_angle[ANGLE_MIN], v_angle[ANGLE_MAX]);
	print_raycasting(general->map->pos_x, general->map->pos_y, v_angle, general);
}