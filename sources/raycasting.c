/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertin <gbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:52:48 by gbertin           #+#    #+#             */
/*   Updated: 2022/12/09 14:53:32 by gbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static	int	get_wall(t_general *general, t_hitpoint hitpoint)
{
	if (hitpoint.x - floor(hitpoint.x) == 0)
	{
		if (hitpoint.x > general->map->pos_x)
			return (east);
		else
			return (west);
	}
	else
	{
		if (hitpoint.y > general->map->pos_y)
			return (south);
		else
			return (nord);
	}
}

double	fisheye(double distance, double angle, double angle_cam)
{
	return (distance * cos(conversion_radian(angle - angle_cam)));
}

t_hitpoint	print_collision(t_general *g, double x, double y, double angle)
{
	t_dir		horiz;
	t_dir		verti;
	t_hitpoint	hitpoint;
	int			remember;

	remember = 0;
	hitpoint.dist = 0;
	verti = first_vertical_wall(x, y, angle);
	horiz = first_horizon_wall(x, y, angle);
	while (remember == 0 || !is_wall(x, y, angle, g))
	{
		if (horiz.hypo < verti.hypo)
		{
			hitpoint.dist += horiz_bigger(&remember, &x, &y, horiz);
			verti = first_vertical_wall(x, y, angle);
			horiz = next_horizon_wall(x, y, angle);
		}
		else
		{
			hitpoint.dist += verti_bigger(&remember, &x, &y, verti);
			horiz = first_horizon_wall(x, y, angle);
			verti = next_vertical_wall(x, y, angle);
		}
	}
	hitpoint.x = x;
	hitpoint.y = y;
	return (hitpoint);
}

void	print_raycasting(double x, double y, double a[2], t_general *g)
{
	int			num_ray;
	t_hitpoint	hitpoint;
	double		angle;

	angle = 0;
	num_ray = 0;
	while (a[ANGLE_MIN] < a[ANGLE_MAX])
	{
		if (a[ANGLE_MAX] < 0.0)
			angle = a[ANGLE_MAX] + 360.0;
		else if (a[ANGLE_MAX] > 360.0)
			angle = a[ANGLE_MAX] - 360.0;
		else
			angle = a[ANGLE_MAX];
		num_ray++;
		if (num_ray == XPIXEL)
			break ;
		hitpoint = print_collision(g, x, y, angle);
		hitpoint.angle = angle;
		hitpoint.dist = fisheye(hitpoint.dist, angle, g->map->angle_cam);
		hitpoint.dir = get_wall(g, hitpoint);
		print_a_column(g, hitpoint, num_ray);
		a[ANGLE_MAX] -= FOV / XPIXEL;
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
