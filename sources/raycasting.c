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

t_dir	first_horizon_wall(float pos_x, float pos_y, double angle)
{
	t_dir horiz;
	float A;
	float B;

	if (angle < 180)
		horiz.y = floor(pos_y) - pos_y;
	else
		horiz.y = ceil(pos_y) - pos_y;
	horiz.x = (horiz.y)/tan(conversion_radian(angle));
	A = pos_x - (pos_x - horiz.x);
	B = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(A*A + B*B);
	printf("calcul horizon x = %f, y = %f\n, hypo = %f\n", horiz.x, horiz.y, horiz.hypo);
	return (horiz);
}

t_dir	first_vertical_wall(float pos_x, float pos_y, double angle)
{
	t_dir verti;
	float A;
	float B;

	if (angle > 90 && angle < 270)
		verti.x = floor(pos_x) - pos_x;
	else
		verti.x = ceil(pos_x) - pos_x;
	verti.y = (verti.x) * tan(conversion_radian(angle));
	A = pos_x - (pos_x + verti.x);
	B = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(A*A + B*B);
	printf("calcul vertical x = %f, y = %f, hypo = %f\n", verti.x, verti.y, verti.hypo);
	return (verti);
}

t_dir	next_horizon_wall(float pos_x, float pos_y, double angle)
{
	t_dir horiz;
	float A;
	float B;

	if (angle < 180)
		horiz.y = -1;
	else
		horiz.y = 1;
	horiz.x = 1/tan(conversion_radian(angle));
	A = pos_x - (pos_x - horiz.x);
	B = pos_y - (pos_y + horiz.y);
	horiz.hypo = sqrt(A*A + B*B);
	//printf("calcul horizon x = %f, y = %f, hypo = %f\n", horiz.x, horiz.y, horiz.hypo);
	return (horiz);
}

t_dir	next_vertical_wall(float pos_x, float pos_y, double angle)
{
	t_dir verti;
	float A;
	float B;

	if (angle > 90 && angle < 270)
		verti.x = -1;
	else
		verti.x = 1;
	verti.y = tan(conversion_radian(angle));
	A = pos_x - (pos_x + verti.x);
	B = pos_y - (pos_y - verti.y);
	verti.hypo = sqrt(A*A + B*B);
	//printf("calcul vertical x = %f, y = %f, hypo = %f\n", verti.x, verti.y, verti.hypo);
	return (verti);
}

static float print_collision(t_general *general, float pos_x, float pos_y, float angle)
{
	t_dir horiz;
	t_dir verti;
	int remember; //1 = horiz, 2 = verti;
	float distance = 0;

	verti = first_vertical_wall(pos_x, pos_y, angle);
	horiz = first_horizon_wall(pos_x, pos_y, angle);
	if (horiz.hypo < verti.hypo)
	{
		remember = 1;
		distance += horiz.hypo;
		pos_x = pos_x - horiz.x;
		pos_y = pos_y + horiz.y;
		verti = first_vertical_wall(pos_x, pos_y, angle);
		horiz = next_horizon_wall(pos_x, pos_y, angle);
	}
	else
	{
		remember = 2;
		distance += verti.hypo;
		pos_x = pos_x + verti.x;
		pos_y = pos_y - verti.y;
		horiz = first_horizon_wall(pos_x, pos_y, angle);
		verti = next_vertical_wall(pos_x, pos_y, angle);
	}
	//printf("new pos x = %f, new pos y = %f\n", pos_x, pos_y);
	while (!is_wall(pos_x, pos_y, angle, general))
	{
		/*mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, \
		general->spts[PLAYER].ptr, pos_x * 64, pos_y * 64);*/
		if (horiz.hypo < verti.hypo)
		{
			//printf("COUCOU\n");
			distance += horiz.hypo;
			if (remember == 1)
			{
				pos_x = pos_x + (-horiz.y * horiz.x);
				pos_y = pos_y + horiz.y;
			}
			else
			{
				pos_x = pos_x - horiz.x;
				pos_y = pos_y + horiz.y;
			}
			remember = 1;
			verti = first_vertical_wall(pos_x, pos_y, angle);
			horiz = next_horizon_wall(pos_x, pos_y, angle);
		}
		else
		{
			//printf("LALALLALA\n");
			distance += verti.hypo;
			if (remember == 2)
			{
				pos_y = pos_y - (verti.x * verti.y);
				pos_x = pos_x + verti.x;
			}
			else 
			{
				pos_x = pos_x + verti.x;
				pos_y = pos_y - verti.y;
			}
			remember = 2;
			horiz = first_horizon_wall(pos_x, pos_y, angle);
			verti = next_vertical_wall(pos_x, pos_y, angle);
		}
		//printf("new pos x = %f, new pos y = %f\n", pos_x, pos_y);
		//printf("hypo horiz = %f, hypo verti = %f\n", horiz.hypo, verti.hypo);
		//printf("WHILE X = %d , Y = %d\n", (int)floor(pos_y), (int)floor(pos_x)-1);
	}
	return (distance);
}

static void	print_raycasting(float origin_x, float origin_y, float v_angle[2], t_general *general)
{
	float	v_dir[2];
	int		i;
	float	x;
	float	y;
	float distance;

	int angle = 0;

	while (v_angle[ANGLE_MIN] < v_angle[ANGLE_MAX])
	{
		if (v_angle[ANGLE_MIN] < 0)
			angle = v_angle[ANGLE_MIN] + 360;
		else
			angle = v_angle[ANGLE_MIN];
		printf("\nv_angle = %d\n", angle);
		i = 0;
		x = origin_x * 64;
		y = origin_y * 64;
		v_dir[V_X] = cos(conversion_radian(angle));
		v_dir[V_Y] = sin(conversion_radian(angle * -1));
		distance = print_collision(general, origin_x, origin_y, angle);
		while (i < distance * 64)
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
	//float	x;
	//float	y;
	//float 	tmp;
	
	// init position x et y
	/*x = floor(general->map->pos_x) * HEIGHT_TILE;
	y = floor(general->map->pos_y) * WIDTH_TILE;
	x += (general->map->pos_x - floor(general->map->pos_x)) * HEIGHT_TILE + 4;
	y += (general->map->pos_y - floor(general->map->pos_y)) * WIDTH_TILE + 4;*/
	// init angle min et angle max du FOV
	//v_angle[ANGLE_MIN] = get_ray_min(general->map->angle_cam);
	//v_angle[ANGLE_MAX] = get_ray_max(general->map->angle_cam);
	// SI angle_cam + 45 est superieur a 360 alors ANGLE MAX devient plus petit que ANGLE MIN
	// OU SI angle_cam - 45 est inferieur a 0 alors ANGLE MIN devient plus grand que ANGLE MIN
	v_angle[ANGLE_MIN] = general->map->angle_cam - 45;
	v_angle[ANGLE_MAX] = general->map->angle_cam + 45;
	/*if (v_angle[ANGLE_MAX] < 0)
		v_angle[ANGLE_MAX] += 360;
	if (v_angle[ANGLE_MIN] < 0)
		v_angle[ANGLE_MIN] += 360;*/
	/*if (v_angle[ANGLE_MIN] > v_angle[ANGLE_MAX])
	{
		tmp = v_angle[ANGLE_MIN];
		v_angle[ANGLE_MIN] = v_angle[ANGLE_MAX];
		v_angle[ANGLE_MAX] = tmp;
	}*/
	printf("ANGLE : min:%f max:%f\n", v_angle[ANGLE_MIN], v_angle[ANGLE_MAX]);
	print_raycasting(general->map->pos_x, general->map->pos_y, v_angle, general);
}