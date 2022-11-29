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
	//printf("calcul horizon x = %f, y = %f\n, hypo = %f\n", horiz.x, horiz.y, horiz.hypo);
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
	//printf("calcul vertical x = %f, y = %f, hypo = %f\n", verti.x, verti.y, verti.hypo);
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
	while (!is_wall(pos_x, pos_y, angle, general))
	{
		if (horiz.hypo < verti.hypo)
		{
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
	}
	return (distance);
}

float	fisheye(float distance, float angle, float angle_cam)
{
	return (distance * cos(conversion_radian(angle - angle_cam)));
}

static void	print_raycasting(float origin_x, float origin_y, double v_angle[2], t_general *general)
{
	//float	v_dir[2];
	int		i;
	float distance;

	int angle = 0;
	i = 0;
	while (v_angle[ANGLE_MIN] < v_angle[ANGLE_MAX])
	{
		if (v_angle[ANGLE_MIN] < 0)
			angle = v_angle[ANGLE_MIN] + 360;
		else if (v_angle[ANGLE_MIN] > 360)
			angle = v_angle[ANGLE_MIN] - 360;
		else
			angle = v_angle[ANGLE_MIN];
		//printf("\nv_angle = %d\n", angle);
		i++;
		printf("i = %d\n", i);
		//v_dir[V_X] = cos(conversion_radian(angle));
		//v_dir[V_Y] = sin(conversion_radian(angle * -1));
		distance = print_collision(general, origin_x, origin_y, angle);
		print_a_column(general, fisheye(distance, angle, general->map->angle_cam), i);
		v_angle[ANGLE_MIN] += FOV / XPIXEL;
	}
	mlx_put_image_to_window(general->mlx.ptr, general->mlx.win, general->mlx.img, 0, 0);
}


void	init_raycasting(t_general *general)
{

	double	v_angle[2];

	v_angle[ANGLE_MIN] = general->map->angle_cam - FOV/2;
	v_angle[ANGLE_MAX] = general->map->angle_cam + FOV/2;
	//printf("ANGLE : min:%f max:%f\n", v_angle[ANGLE_MIN], v_angle[ANGLE_MAX]);
	init_image(general);
	print_raycasting(general->map->pos_x, general->map->pos_y, v_angle, general);
}