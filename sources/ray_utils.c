/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:17:19 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/08 12:19:48 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	conversion_radian(double f)
{
	f = f * (3.1415926535 / 180.0);
	return (f);
}

double	get_ray_min(double angle)
{
	int	half_fov;

	half_fov = FOV / 2;
	return (angle - half_fov);
}

double	get_ray_max(double angle)
{
	int	half_fov;

	half_fov = FOV / 2;
	return (angle + half_fov);
}

double	horiz_bigger(int *remember, double *pos_x, double *pos_y, t_dir horiz)
{
	if (*remember == 1)
	{
		*pos_x = *pos_x + (-horiz.y * horiz.x);
		*pos_y = *pos_y + horiz.y;
	}
	else
	{
		*pos_x = *pos_x - horiz.x;
		*pos_y = *pos_y + horiz.y;
	}
	*remember = 1;
	return (horiz.hypo);
}

double	verti_bigger(int *remember, double *pos_x, double *pos_y, t_dir verti)
{
	if (*remember == 2)
	{
		*pos_y = *pos_y - (verti.x * verti.y);
		*pos_x = *pos_x + verti.x;
	}
	else
	{
		*pos_x = *pos_x + verti.x;
		*pos_y = *pos_y - verti.y;
	}
	*remember = 2;
	return (verti.hypo);
}
